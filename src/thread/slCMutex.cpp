#include "slCMutex.h"
#include "base/slCThreadImpl.hp"

LE_NAMESPACE_START

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

LE_NAMESPACE_END
