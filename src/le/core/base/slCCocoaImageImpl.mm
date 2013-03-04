#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif
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
		virtual void loadFromStream(std::istream& stream);
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

#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
		inline void loadFromUIImage(UIImage* image);
#else
		inline void loadFromNSBitmapImageRep(NSBitmapImageRep* rep);
		inline NSBitmapImageRep* bitmapFromData(NSData* data, BOOL isGif);
#endif
};

LE_IMPLEMENT_RUNTIME_CLASS(CCocoaImageImpl);

void CCocoaImageImpl::loadFromStream(std::istream& stream)
{
	stream.seekg(0, std::ios_base::end);
	UInt32 fileSize = stream.tellg();
	stream.seekg(0, std::ios_base::beg);

	UInt16 fileSignature;
	stream.read((char*)&fileSignature, sizeof(fileSignature));
	BOOL isGif = CNumber::littleEndianToHost(fileSignature) == 18759;  // 'GI'

	stream.seekg(0, std::ios_base::beg);

	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	NSMutableData* imageData = [[NSMutableData alloc] initWithCapacity: fileSize];
	if (imageData)
	{
		[imageData setLength: fileSize];
		stream.read((char*)[imageData mutableBytes], fileSize);
#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
		UIImage* image = [UIImage imageWithData: imageData];
#else
		NSBitmapImageRep* image = bitmapFromData(imageData, isGif);
#endif

		[imageData release];

		if (image)
		{
#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
			loadFromUIImage(image);
#else
			loadFromNSBitmapImageRep(image);
#endif
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

#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
inline void CCocoaImageImpl::loadFromUIImage(UIImage* image)
{
	NSArray* frames = nil;

	if ([image respondsToSelector(@selector(images))])
	{
		frames = [image images];
	}

	if (frames)
	{
		for (UIImage* frame in frames)
		{
			
		}
	}
	else
	{
		
	}
}
#else
inline void CCocoaImageImpl::loadFromNSBitmapImageRep(NSBitmapImageRep* image)
{
	NSUInteger frameCount = [[image valueForProperty: NSImageFrameCount] unsignedIntegerValue];
	if (frameCount)
	{
		for (NSUInteger i = 0; i < frameCount; ++i)
		{
			[image setProperty: NSImageCurrentFrame withValue: [NSNumber numberWithUnsignedInteger: i]];
			loadFrame(image);
		}
	}
	else
	{
		loadFrame(image);
	}
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

#endif

		
inline void CCocoaImageImpl::loadFrame(NSBitmapImageRep* bitmap)
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
