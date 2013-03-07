#include <fstream>
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

CResult CImage::loadFromURL(const CURL& url)
{
//	std::cout << "Loading image: " << url << std::endl;
	if (mImpl)
	{
		mImpl->release();
		mImpl = NULL;
	}

	std::ifstream stream(url.path().UTF8String(), std::ifstream::binary);
	if (stream)
	{
		UInt16 fileSignature;
		stream.read((char*)&fileSignature, sizeof(fileSignature));
		fileSignature = CNumber::littleEndianToHost(fileSignature);

		CDictionary parameters;
		parameters.setValueForKey(LESTR("fileSignature"), fileSignature);
		parameters.setValueForKey(LESTR("fileExtension"), url.extension());
		parameters.setValueForKey(LESTR("fileURL"), new CURL(url));

		mImpl = CClassFactory::defaultInstance()->bestSubclassOfClassWithParameters(CImageImpl::staticClass(), parameters).create<CImageImpl>().retain();

		LE_ASSERT(mImpl);

		if (mImpl)
		{
			CResult result = mImpl->loadFromStream(stream);
			if (!result)
			{
				std::cout << "Error loading image: " << result << std::endl;
				return result;
			}
			LE_ASSERT(mImpl->frameCount());
		}
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
