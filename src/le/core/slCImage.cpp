#include "slTypes.h"
#include "slCURL.h"
#include "slCImage.h"
#include "slCNumber.h"
#include "base/slCBitmapImageImpl.hp"
#include "base/slCGifImageImpl.hp"
#include "base/slCJpegImageImpl.hp"
#include "base/slCImageImpl.hp"

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
//	std::cout << "Loading image: " << url << std::endl;
	if (mImpl)
	{
		mImpl->release();
		mImpl = NULL;
	}

	FILE* file = fopen(url.path().cString(), "rb");
	if (file)
	{
		UInt16 type;
		fread(&type, sizeof(type), 1, file);
		type = CNumber::littleEndianToHost(type);

//		std::cout << "Type: " << type << std::endl;

		switch (type)
		{
			case 19778: // 'BM' - Windows BMP image
				mImpl = new CImageImpl();
				CBitmapImageImpl::loadFromFileToImageImpl(file, mImpl);
				break;
			case 18759: // 'GI' - GIF image
				mImpl = new CImageImpl();
				CGifImageImpl::loadFromFileToImageImpl(file, mImpl);
				break;
			case 55551: // FF D8 - JPEG image
				mImpl = new CImageImpl();
				CJpegImageImpl::loadFromFileToImageImpl(file, mImpl);
				break;
		}
		fclose(file);
	}
	return _LE_BOOL_CAST(mImpl);
}

UInt32 CImage::frameCount() const
{
	return (mImpl)?(mImpl->frameCount()):(0);
}

CImageFrame CImage::frameAtIndex(UInt32 index) const
{
	return (mImpl)?(mImpl->frameAtIndex(index)):(CImageFrame());
}

void CImage::insertFrame(UInt32 position, const CImageFrame& frame)
{
	if (mImpl) mImpl->insertFrame(position, frame);
}


//UInt32 CImage::frameCount() const
//{
//	return (mImpl)?(mImpl->frameCount()):(0);
//}
//
//CImageFrame frameAtIndex(UInt32 frame) const
//{
//	return (mImpl)?(mImpl->frameAtIndex(
//}
//
//UInt32 CImage::currentFrame() const
//{
//	return (mImpl)?(mImpl->currentFrame()):(0);
//}
//
//void CImage::setCurrentFrame(UInt32 frame)
//{
//	if (mImpl) mImpl->setCurrentFrame(frame);
//}
//
//EPixelFormat CImage::pixelFormat() const
//{
//	return (mImpl)?(mImpl->pixelFormat()):(ePixelFormatRGB);
//}
//
//const UInt8* CImage::pixelData() const
//{
//	return (mImpl)?(mImpl->pixelData()):(NULL);
//}
//
//CSize2D CImage::size() const
//{
//	return (mImpl)?(mImpl->size()):(CSize2D());
//}
//
//UInt32 CImage::duration()
//{
//	return (mImpl)?(mImpl->duration()):(0);
//}
//

const CImage& CImage::operator = (const CImage& copy)
{
	if (mImpl) mImpl->release();
	mImpl = copy.mImpl;
	if (mImpl) mImpl->retain();
	return *this;
}

CImageImpl* CImage::_impl() const
{
	return mImpl;
}

	} // namespace le
} // namespace sokira
