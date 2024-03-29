#include <iostream>
#include <string.h> // For memcpy
#include <le/core/slCNumber.h>
#include <le/core/slCDictionary.h>
#include "slCImageImpl.hp"

//#include <le/core/slCImage.h>
#include "slCImageFrameImpl.hp"

namespace sokira
{
	namespace le
	{

class CBitmapImageImpl : public CImageImpl
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CBitmapImageImpl)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END
	
	public:
		virtual CResult loadFromStream(std::istream& stream);
		static Float32 priorityForParameters(const CDictionary& parameters)
		{
			UInt16 fileSignature = parameters.valueAsUInt16ForKey("fileSignature");
			if (fileSignature == 19778) // 'BM' - Windows BMP image
			{
				return 200;
			}
			return -1;
		}
};

LE_IMPLEMENT_RUNTIME_CLASS(CBitmapImageImpl);


#define LE_BMP_BITS_PER_PIXEL 32

typedef UInt16 WORD;
typedef UInt32 DWORD;
typedef SInt32 LONG;
typedef UInt8 BYTE;


//File information header
//provides general information about the file
typedef struct tagBITMAPFILEHEADER {
//  WORD    bfType; // this field should already have been read by CImage container
  DWORD   bfSize;
  WORD    bfReserved1;
  WORD    bfReserved2;
  DWORD   bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

//Bitmap information header
//provides information specific to the image data
typedef struct tagBITMAPINFOHEADER{
  DWORD  biSize;
  LONG   biWidth;
  LONG   biHeight;
  WORD   biPlanes;
  WORD   biBitCount;
  DWORD  biCompression;
  DWORD  biSizeImage;
  LONG   biXPelsPerMeter;
  LONG   biYPelsPerMeter;
  DWORD  biClrUsed;
  DWORD  biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

//Colour palette
typedef struct tagRGBQUAD {
  BYTE    rgbBlue;
  BYTE    rgbGreen;
  BYTE    rgbRed;
  BYTE    rgbReserved;
} RGBQUAD;

CResult CBitmapImageImpl::loadFromStream(std::istream& stream)
{
//	std::cout << "loading bitmap" << std::endl;
	BITMAPFILEHEADER bmfh;
	stream.read((char*)&bmfh, sizeof(bmfh));

	BITMAPINFOHEADER bmih;
	stream.read((char*)&bmih, sizeof(bmih));

	bmih.biWidth = CNumber::littleEndianToHost(bmih.biWidth);
	bmih.biHeight = CNumber::littleEndianToHost(bmih.biHeight);
	bmih.biBitCount = CNumber::littleEndianToHost(bmih.biBitCount);

	CSize2D size = CSize2D(bmih.biWidth, std::abs(bmih.biHeight));
	UInt32 destBytesPerPixel = LE_BMP_BITS_PER_PIXEL / 8;

	RGBQUAD* palette = NULL;

	//load the palette for 8 bits per pixel
	if (bmih.biBitCount == 8)
	{
		//set the number of colours
		UInt32 numColours = 1 << bmih.biBitCount;
		palette = new RGBQUAD[numColours];
		stream.read((char*)palette, sizeof(RGBQUAD) * numColours);
	}
	delete [] palette; // TODO handle this!

	UInt8* pixelData = new UInt8[(UInt32)size.area() * destBytesPerPixel];

	SInt32 scanStep = 1;
	SInt32 i = 0;
	SInt32 last = size.height();

	if (bmih.biHeight > 0)
	{
		i = last - 1; // -1 ???
		last = -1;
		scanStep = -1;
	}

	UInt32 bytesPerPixel = bmih.biBitCount / 8;
	UInt32 padWidth = bmih.biWidth * bytesPerPixel;

	while (padWidth % 4) ++padWidth;

	padWidth -= bmih.biWidth * bytesPerPixel;
//	std::cout << "bytesPerPixel: " << bytesPerPixel << std::endl;
//	std::cout << "padWidth: " << padWidth << std::endl;
//	std::cout << "height: " << bmih.biHeight << std::endl;

//	bool dump = false;

	for (; i != last; i += scanStep)
	{
		UInt32 color;
		for (UInt32 j = 0; j < (UInt32)bmih.biWidth; ++j)
		{
			color = 0;
			UInt8 r = 0;
			UInt8 g = 0;
			UInt8 b = 0;
			UInt8 a = 0xff;

			stream.read((char*)&color, bytesPerPixel);
			if (bytesPerPixel == 3)
			{
				r = *(((UInt8*)&color) + 2);
				g = *(((UInt8*)&color) + 1);
				b = *(((UInt8*)&color));
			}
			else if (bytesPerPixel == 4)
			{
				a = *(((UInt8*)&color) + 3);
				r = *(((UInt8*)&color) + 2);
				g = *(((UInt8*)&color) + 1);
				b = *(((UInt8*)&color) + 0);
			}

//			if (r == 32 && g == 105 && b == 255) a = 0;


//			if (!dump)
//			{
//				std::cout << "R: " << std::hex << (UInt32)r << ", G: " << (UInt32)g << ", B: " << (UInt32)b << ", A: " << (UInt32)a << std::endl;
//				dump = true;
//			}

			UInt8* destPixel = pixelData + (i * bmih.biWidth + j) * destBytesPerPixel;
			if (destBytesPerPixel == 3)
			{
				*(destPixel) = r;
				*(destPixel + 1) = g;
				*(destPixel + 2) = b;
			}
			else if (destBytesPerPixel == 4)
			{
				*(destPixel) = r;
				*(destPixel + 1) = g;
				*(destPixel + 2) = b;
				*(destPixel + 3) = a;
			}
		}
		stream.read((char*)&color, padWidth); // Omit padding
	}
	insertFrame(0, CImageFrame(new CImageFrameImpl(size, (EPixelFormat)LE_BMP_BITS_PER_PIXEL, pixelData, 0)));
	return true;
}

	} // namespace le
} // namespace sokira
