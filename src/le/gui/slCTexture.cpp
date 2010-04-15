#include <le/core/slCImage.h>
#include <le/core/base/slCImageImpl.hp>
#include "slCTexture.h"
#include "base/slCTextureImpl.hp"

namespace sokira
{
	namespace le
	{

CTexture::CTexture() :
	mImageImpl(NULL),
	mImpl(NULL)
{

}

CTexture::CTexture(const CTexture& texture) :
	mImageImpl(texture.mImageImpl),
	mImpl(texture.mImpl)
{
	if (mImageImpl) mImageImpl->retain();
	if (mImpl) mImpl->retain();
}


CTexture::CTexture(const CImage& image) :
	mImageImpl(image._impl()),
	mImpl(NULL)
{
	if (mImageImpl) mImageImpl->retain();
}

CTexture::~CTexture()
{
	disposeData();
}

void CTexture::disposeData()
{
	if (mImpl) mImpl->release();
	if (mImageImpl) mImageImpl->release();
}

void CTexture::setImage(const CImage& image)
{
	disposeData();
	mImpl = NULL;
	mImageImpl = image._impl();
	if (mImageImpl) mImageImpl->retain();
}

CSize2D CTexture::size() const
{
	return (mImpl)?(mImpl->size()):((mImageImpl)?(mImageImpl->frameAtIndex(0).size()):(CSize2D()));
}

	} // namespace le
} // namespace sokira
