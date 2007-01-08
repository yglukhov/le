#include "slCMutex.h"
#include "base/slCThreadImpl.hp"

namespace sokira
{
	namespace le
	{

CMutex::CMutex(bool recursive) :
	mImpl(new CMutexImpl(recursive))
{

}

CMutex::~CMutex()
{
	delete mImpl;
}

void CMutex::lock()
{
	mImpl->lock();
}

void CMutex::unlock()
{
	mImpl->unlock();
}

	} // namespace le
} // namespace sokira
