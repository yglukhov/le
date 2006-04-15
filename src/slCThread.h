#pragma once

#include <config/slPrefix.h>
#include <function/slTCFunction.h>

LE_NAMESPACE_START

class CThread
{
	public:
		CThread(const TCFunction<>& threadProc, bool startImmediately = true);
		~CThread();

		void start();
//		void stop();

	private:
		void* mThread;
		TCFunction<> mThreadProc;
};

LE_NAMESPACE_END
