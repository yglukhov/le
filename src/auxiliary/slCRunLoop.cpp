#include "slCRunLoop.h"

LE_NAMESPACE_START

CRunLoop::CRunLoop() :
	mSources(0),
	mStopped(true)
{

}

void CRunLoop::run()
{
	while(!isStopped())
	{
		{
			CMutexLock locker(mQueueMutex);
			if(!mEventQueue.empty())
			{
				mEventQueue.front()();
				mEventQueue.pop_front();
				continue;
			}
		}

		if (mSources == 0)
		{
			stop();
		}
	}
}

void CRunLoop::stop()
{
	mStopped = true;
}

bool CRunLoop::isStopped() const
{
	return mStopped;
}

void CRunLoop::pushEvent(const TCFunction<>& event)
{
	CMutexLock locker(mQueueMutex);
	mEventQueue.push_back(event);
}

LE_NAMESPACE_END
