#pragma once

#include <list>
#include <le/core/slTypes.h>
#include <le/core/thread/slCMutex.h>
#include <le/core/template/function/slTCFunction.h>

namespace sokira
{
	namespace le
	{

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

	} // namespace le
} // namespace sokira
