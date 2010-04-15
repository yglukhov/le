#include "slCSource.h"
#include "base/slCSourceImpl.hp"

namespace sokira
{
	namespace le
	{


CSource::CSource() :
	mImpl(NULL)
{

}

CSource::CSource(const CSource& source) :
	mImpl(source.mImpl)
{
	if (mImpl) mImpl->retain();
}

CSource::CSource(CSourceImpl* impl) :
	mImpl(impl)
{
	if (mImpl) mImpl->retain();
}

CSource::~CSource()
{
	if (mImpl) mImpl->release();
}

Bool CSource::loadFromURL(const CURL& url)
{
	LE_ASSERT(mImpl);
	return mImpl->loadFromURL(url);
}

void CSource::setPosition()
{

}

void CSource::setVolume()
{

}

void CSource::play()
{
	mImpl->play();
}

void CSource::pause()
{

}

void CSource::stop()
{

}

const CSource& CSource::operator = (const CSource& source)
{
	if (mImpl) mImpl->release();
	mImpl = source.mImpl;
	if (mImpl) mImpl->retain();
	return *this;
}

	} // namespace le
} // namespace sokira
