#pragma once

#include <list>
#include <common/types/slBasic.h>
#include <thread/slCMutex.h>
#include <template/function/slTCFunction.h>

LE_NAMESPACE_START

class CRunLoop
{
	public:
		CRunLoop();

		void run();
		void stop();
		bool isStopped() const;

		void pushEvent(const TCFunction<>& event);

	private:
		std::list<TCFunction<> > mEventQueue;
		CMutex mQueueMutex;
		UInt4 mSources;
		bool mStopped;
};

LE_NAMESPACE_END
