#include <Windows.h>
#include <OleCtl.h>
#include "slCImageImpl.hp"
#include "slCImageFrameImpl.hp"
#include <le/core/slCDictionary.h>

namespace sokira
{
	namespace le
	{

class CIPictureImageImpl : public CImageImpl
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CIPictureImageImpl)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		virtual void loadFromFile(FILE* file);
		static Float32 priorityForParameters(const CDictionary& parameters)
		{
			UInt16 fileSignature = parameters.valueAsUInt16ForKey("fileSignature");
			if (fileSignature == 55551 || fileSignature == 18759) // FF D8 - JPEG image or 'GI'
			{
				return 100;
			}
			return -1;
		}
};

LE_IMPLEMENT_RUNTIME_CLASS(CIPictureImageImpl);

void CIPictureImageImpl::loadFromFile(FILE* file)
{
	fseek(file, 0, SEEK_END);
	UInt32 fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, fileSize);
	LPVOID pvData = GlobalLock( hGlobal );
	fread(pvData, fileSize, 1, file);
	GlobalUnlock(hGlobal);

	LPSTREAM pStream = NULL;
	HRESULT hr = CreateStreamOnHGlobal( hGlobal, TRUE, &pStream );
	IPicture *pic = NULL;

	OleLoadPicture(pStream, 0, FALSE, IID_IPicture, (void **)&pic);
	pStream->Release();

	OLE_XSIZE_HIMETRIC cx;
	OLE_YSIZE_HIMETRIC cy;
	pic->get_Width(&cx);
	pic->get_Height(&cy);

	HDC screenDC = GetDC(NULL);
	HDC dcPictureLoad = CreateCompatibleDC(screenDC);
	ReleaseDC(NULL, screenDC);

	#define HIMETRIC_INCH 2540 
	#define MAP_LOGHIM_TO_PIX(x,ppli) ( ((ppli)*(x) + HIMETRIC_INCH/2) / HIMETRIC_INCH ) 

	unsigned long width = MAP_LOGHIM_TO_PIX(cx, GetDeviceCaps(dcPictureLoad, LOGPIXELSX));
	unsigned long height = MAP_LOGHIM_TO_PIX(cy, GetDeviceCaps(dcPictureLoad, LOGPIXELSX));

	pic->Render(dcPictureLoad, 0, 0, width, height, 0, 0, width, height, NULL);
	pic->Release();

	UInt8* pixelData = new UInt8[width * height * 4];
	for (unsigned i = 0; i < height; ++i)
	{
		for (unsigned j = 0; j < width; ++j)
		{
			COLORREF col = GetPixel(dcPictureLoad, j, i);
			UInt8* pixel = pixelData + (i * width + j) * 4;
			*pixel = GetRValue(col);
			*(pixel + 1) = GetGValue(col);
			*(pixel + 2) = GetBValue(col);
			*(pixel + 3) = 0x0;
		}
	}

	DeleteDC(dcPictureLoad);

	insertFrame(0, CImageFrame(new CImageFrameImpl(CSize2D(width, height), ePixelFormatRGBA, pixelData, 0)));
}

	} // namespace le
} // namespace sokira
