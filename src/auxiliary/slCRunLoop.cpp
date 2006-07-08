#include "slCRunLoop.h"

LE_NAMESPACE_START

CRunLoop::CRunLoop(bool sourceDependent) :
	mSources(static_cast<UInt32>(!sourceDependent)),
	mStopped(true)
{

}

CRunLoop::CRunLoop(const TCFunction<>& firstEvent, bool sourceDependent) :
	mSources(static_cast<UInt32>(!sourceDependent)),
	mStopped(true)
{
	pushEvent(firstEvent);
}

void CRunLoop::run()
{
	do
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

		if (!mSources)
		{
			stop();
		}
	} while(!isStopped());
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
