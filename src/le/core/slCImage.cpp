#include "slTypes.h"
#include "slCURL.h"
#include "slCImage.h"
#include "slCNumber.h"
#include "base/slCBitmapImageImpl.hp"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CImage);

CImage::CImage() :
	mImpl(NULL)
{

}

CImage::CImage(const CImage& image) :
	mImpl(image.mImpl)
{
	if (mImpl) mImpl->retain();
}

CImage::CImage(const CURL& url) :
	mImpl(NULL)
{
	loadFromURL(url);
}

CImage::~CImage()
{
	if (mImpl) mImpl->release();
}

Bool CImage::loadFromURL(const CURL& url)
{
//	std::cout << "Loading image: " << url.path() << std::endl;
	if (mImpl) mImpl->release();

	FILE* file = fopen(url.path().cString(), "r");
	if (file)
	{
		UInt16 type;
		fread(&type, sizeof(type), 1, file);
		type = CNumber::littleEndianToHost(type);
		switch (type)
		{
			case 19778: // 'BM' - Windows BMP image
				mImpl = new CBitmapImageImpl(file);
				break;
			default:
				break;
		}
		fclose(file);
		return _LE_BOOL_CAST(mImpl);
	}
	return false;
}

const UInt8* CImage::pixelData() const
{
	return (mImpl)?(mImpl->pixelData()):(NULL);
}

CSize2D CImage::size() const
{
	return (mImpl)?(mImpl->size()):(CSize2D());
}

CImageImpl* CImage::_impl() const
{
	return mImpl;
}

	} // namespace le
} // namespace sokira
