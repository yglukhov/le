#include "slCImageFrame.h"
#include "base/slCImageFrameImpl.hp"

namespace sokira
{
	namespace le
	{

CImageFrame::CImageFrame() :
	mImpl(0)
{

}

CImageFrame::CImageFrame(const CImageFrame& frame) :
	mImpl(frame.mImpl)
{
	if (mImpl) mImpl->retain();
}

CImageFrame::CImageFrame(CImageFrameImpl* impl) :
	mImpl(impl)
{

}

CImageFrame::~CImageFrame()
{
	if (mImpl) mImpl->release();
}


EPixelFormat CImageFrame::pixelFormat() const
{
	return (mImpl)?(mImpl->mFormat):(ePixelFormatRGB);
}

const UInt8* CImageFrame::pixelData() const
{
	return (mImpl)?(mImpl->mData):(0);
}

CSize2D CImageFrame::size() const
{
	return (mImpl)?(mImpl->mSize):(CSize2D());
}

UInt32 CImageFrame::duration() const
{
	return (mImpl)?(mImpl->mDuration):(0);
}
 // Duration of a frame in milliseconds;

const CImageFrame& CImageFrame::operator = (const CImageFrame& frame)
{
	if (mImpl) mImpl->release();
	mImpl = frame.mImpl;
	if (mImpl) mImpl->retain();
	return *this;
}

	} // namespace le
} // namespace sokira
