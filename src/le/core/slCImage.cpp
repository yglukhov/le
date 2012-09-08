#include "slTypes.h"
#include "slCURL.h"
#include "slCImage.h"
#include "slCDictionary.h"
#include "slCClassFactory.h"
#include "base/slCImageImpl.hp"
#include "base/slCImageFrameImpl.hp"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CImage);
LE_IMPLEMENT_RUNTIME_CLASS(CImageImpl);

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

CImage CImage::createWithPixelData(const CSize2D& size, EPixelFormat format, UInt8* data)
{
	CImage result;
	result.mImpl = new CImageImpl();
	result.mImpl->insertFrame(0, CImageFrame(new CImageFrameImpl(size, format, data, 0)));
	return result;
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
		UInt16 fileSignature;
		fread(&fileSignature, sizeof(fileSignature), 1, file);
		fileSignature = CNumber::littleEndianToHost(fileSignature);

		CDictionary parameters;
		parameters.setValueForKey(LESTR("fileSignature"), fileSignature);
		parameters.setValueForKey(LESTR("fileExtension"), url.extension());
		parameters.setValueForKey(LESTR("fileURL"), url);

		mImpl = CClassFactory::defaultInstance()->bestSubclassOfClassWithParameters(CImageImpl::staticClass(), parameters).create<CImageImpl>().retain();

		if (mImpl)
		{
			mImpl->loadFromFile(file);
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
