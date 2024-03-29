#include "slCThread.h"
#include "base/slCThreadImpl.hp"

namespace sokira
{
	namespace le
	{

CThread::CThread(const CThread& copy) :
	mImpl(copy.mImpl)
{
	mImpl->retain();
}

CThread::CThread(const TCFunction<>& threadProc,
				 const CString& threadName,
				 bool startImmediately) :
	mImpl(new CThreadImpl(threadProc, threadName))
{
	if (startImmediately)
	{
		mImpl->start();
	}
}

CThread::CThread(CThreadImplBase* impl) :
	mImpl(impl)
{
	mImpl->retain();
}

CThread::~CThread()
{
	mImpl->release();
}

CThread CThread::thread()
{
	return CThread(CThreadImpl::thread());
}

const CThread& CThread::operator = (const CThread& copy)
{
	mImpl->release();
	mImpl = copy.mImpl;
	mImpl->retain();
	return *this;
}

void CThread::start()
{
	mImpl->start();
}

//void CThread::stop()
//{
//	mImpl->stop();
//}

//bool CThread::isRunning() const
//{
//	return mImpl->isRunning();
//}

CString CThread::name() const
{
	return mImpl->name();
}

CRunLoop& CThread::runLoop()
{
	return mImpl->mRunLoop;
}

void CThread::sleep(UInt32 milliSeconds)
{
	CThreadImpl::sleep(milliSeconds);
}

UInt32 CThread::milliSeconds()
{
	return CThreadImpl::milliSeconds();
}

void* CThread::_singletone(const char* stdTypeName, void*(*creator)(), void (*deleter)(void*))
{
	return mImpl->singletone(stdTypeName, creator, deleter);
}

	} // namespace le
} // namespace sokira
