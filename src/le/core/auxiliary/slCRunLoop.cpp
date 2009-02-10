#include "slCRunLoop.h"

namespace sokira
{
	namespace le
	{

CRunLoop::CRunLoop() :
	mStopped(true)
{

}

void CRunLoop::run()
{
//	do
//	{
//		{
//			CMutexLock locker(mQueueMutex);
//			if(!mEventQueue.empty())
//			{
//				mEventQueue.front()();
//				mEventQueue.pop_front();
//				continue;
//			}
//		}
//
//		if (!mSources)
//		{
//			stop();
//		}
//	} while(!isStopped());
	mStopped = false;
}

void CRunLoop::stop()
{
	mStopped = true;
}

bool CRunLoop::isStopped() const
{
	return mStopped;
}

	} // namespace le
} // namespace sokira
