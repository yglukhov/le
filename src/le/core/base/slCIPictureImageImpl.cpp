#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS

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
		virtual CResult loadFromStream(std::istream& stream);
		static Float32 priorityForParameters(const CDictionary& parameters)
		{
			UInt16 fileSignature = parameters.valueAsUInt16ForKey("fileSignature");
			std::cout << "IPICTURE: " << fileSignature << "\n";
			if (fileSignature == 55551 || fileSignature == 18759) // FF D8 - JPEG image or 'GI'
			{
				return 1000;
			}
			return -1;
		}
};

LE_IMPLEMENT_RUNTIME_CLASS(CIPictureImageImpl);

CResult CIPictureImageImpl::loadFromStream(std::istream& stream)
{
	CoInitialize(NULL);
	OleInitialize(NULL);

	stream.seekg(0, std::ios::end);
	UInt32 fileSize = stream.tellg();
	stream.seekg(0, std::ios::beg);

	CResult result = true;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, fileSize);
	if (hGlobal)
	{
		LPVOID pvData = GlobalLock(hGlobal);
		if (pvData)
		{
			stream.read((char*)pvData, fileSize);
			GlobalUnlock(hGlobal);

			LPSTREAM pStream = NULL;
			HRESULT res = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);

			if (SUCCEEDED(res) && pStream)
			{
				IPicture *pic = NULL;
				res = OleLoadPicture(pStream, 0, FALSE, IID_IPicture, (LPVOID*)&pic);
				pStream->Release();

				if (SUCCEEDED(res) && pic)
				{
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
				else
				{
					result = CResult("Could not load picture");
				}
			}
			else
			{
				GlobalFree(hGlobal);
				result = CResult("Could not create stream");
			}
		}
		else
		{
			result = CResult("Could not lock global");
		}
	}
	else
	{
		result = CResult("Could not create HGLOBAL");
	}

	return result;
}

	} // namespace le
} // namespace sokira

#endif // LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
