#import <AppKit/AppKit.h>
#import <le/core/slCDictionary.h>
#import "slCImageImpl.hp"
#import "slCImageFrameImpl.hp"

namespace sokira
{
	namespace le
	{

class CCocoaImageImpl : public CImageImpl
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CCocoaImageImpl)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		virtual void loadFromFile(FILE* file);
		static Float32 priorityForParameters(const CDictionary& parameters)
		{
			NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
			CString fileType = parameters.valueAsStringForKey(LESTR("fileExtension"));
			NSArray* supportedTypes = [NSImage imageFileTypes];
			Float32 result = -1;
			for (NSString* type in supportedTypes)
			{
				if (fileType == [type UTF8String])
				{
					result = 150;
					break;
				}
			}

			[pool drain];
			return result;
		}

	private:
		inline void loadFrame(NSBitmapImageRep* bitmap);
		inline NSBitmapImageRep* bitmapFromData(NSData* data, BOOL isGif);
};

LE_IMPLEMENT_RUNTIME_CLASS(CCocoaImageImpl);

void CCocoaImageImpl::loadFromFile(FILE* file)
{
	fseek(file, 0, SEEK_END);
	UInt32 fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	UInt16 fileSignature;
	fread(&fileSignature, sizeof(fileSignature), 1, file);
	BOOL isGif = CNumber::littleEndianToHost(fileSignature) == 18759;  // 'GI'

	fseek(file, 0, SEEK_SET);

	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	NSMutableData* imageData = [[NSMutableData alloc] initWithCapacity: fileSize];
	if (imageData)
	{
		[imageData setLength: fileSize];
		fread([imageData mutableBytes], fileSize, 1, file);
		NSBitmapImageRep* bitmap = bitmapFromData(imageData, isGif);
		[imageData release];
		if (bitmap)
		{
			NSUInteger frameCount = [[bitmap valueForProperty: NSImageFrameCount] unsignedIntegerValue];
			if (frameCount)
			{
				for (NSUInteger i = 0; i < frameCount; ++i)
				{
					[bitmap setProperty: NSImageCurrentFrame withValue: [NSNumber numberWithUnsignedInteger: i]];
					loadFrame(bitmap);
				}
			}
			else
			{
				loadFrame(bitmap);
			}
		}
		else
		{
			NSLog(@"CCocoaImageImpl: Could not load bitmap");
		}
	}
	else
	{
		LE_ASSERT(false);
	}
	[pool drain];
}

inline NSBitmapImageRep* CCocoaImageImpl::bitmapFromData(NSData* data, BOOL isGif)
{
	NSBitmapImageRep* result = nil;
	if (isGif)
	{
		result = [[[NSBitmapImageRep alloc] initWithData: data] autorelease];
	}
	else
	{
		NSImage* image = [[NSImage alloc] initWithData: data];
		if (image)
		{
			result = [[[NSBitmapImageRep alloc] initWithData: [image TIFFRepresentation]] autorelease];
			[image release];
		}
	}
	return result;
}

void CCocoaImageImpl::loadFrame(NSBitmapImageRep* bitmap)
{
	NSInteger samplesPerPixel = [bitmap samplesPerPixel];
	if(![bitmap isPlanar] && (samplesPerPixel == 4 || samplesPerPixel == 3))
	{
		EPixelFormat format = samplesPerPixel == 4 ? ePixelFormatRGBA : ePixelFormatRGB;

		UInt32 height = [bitmap pixelsHigh];
		UInt32 width = [bitmap pixelsWide];
		
		UInt32 bytesPerRowSrc = [bitmap bytesPerRow];
		UInt32 bytesPerRowDest = width * samplesPerPixel;

		UInt8* pixelData = new UInt8[height * bytesPerRowDest];

		UInt8* bitmapData = [bitmap bitmapData];
		
		for (UInt32 i = 0; i < height; ++i)
		{
			memcpy(pixelData + bytesPerRowDest * i, bitmapData + bytesPerRowSrc * i, bytesPerRowDest);
		}

		UInt32 duration = [[bitmap valueForProperty: NSImageCurrentFrameDuration] unsignedLongValue];

		insertFrame(0, CImageFrame(new CImageFrameImpl(CSize2D(width, height), format, pixelData, duration)));
	}
	else
	{
		NSLog(@"-textureFromView: Unsupported bitmap data format: isPlanar:%d, samplesPerPixel:%d, bitsPerPixel:%d, bytesPerRow:%d, bytesPerPlane:%d",
			  (int)[bitmap isPlanar],
			  (int)[bitmap samplesPerPixel],
			  (int)[bitmap bitsPerPixel],
			  (int)[bitmap bytesPerRow],
			  (int)[bitmap bytesPerPlane]);
	}
}

	} // namespace le
} // namespace sokira
