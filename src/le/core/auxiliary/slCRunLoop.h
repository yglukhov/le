#pragma once

#include <list>
#include <le/core/slTypes.h>
#include <le/core/thread/slCMutex.h>
#include <le/core/template/function/slTCFunction.h>

LE_NAMESPACE_START

class CRunLoop
{
	public:
		CRunLoop(bool sourceDependent = true);
		CRunLoop(const TCFunction<>& firstEvent, bool sourceDependent = true);

		void run();
		void stop();
		bool isStopped() const;

		void pushEvent(const TCFunction<>& event);

	private:
		std::list<TCFunction<> > mEventQueue;
		CMutex mQueueMutex;
		UInt32 mSources;
		bool mStopped;
};

LE_NAMESPACE_END
