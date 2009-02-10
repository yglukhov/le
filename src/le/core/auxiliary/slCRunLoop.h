#pragma once

#include <list>
#include <le/core/slTypes.h>
#include <le/core/thread/slCMutex.h>
#include <le/core/template/function/slTCFunction.h>

namespace sokira
{
	namespace le
	{

class CRunLoopSource;

class CRunLoop
{
	public:
		void run();
		void stop();
		bool isStopped() const;


	private:
		friend class CThread;
		CRunLoop();
		CMutex mQueueMutex;
		bool mStopped;
};

	} // namespace le
} // namespace sokira
