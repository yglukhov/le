#pragma once

#include <common/debug/slCLogControl.h>
#include <template/function/slTCFunction.h>
#include <auxiliary/slCRunLoop.h>

LE_NAMESPACE_START

class CThread
{
	public:
		static TCPointer<CThread> create(const TCFunction<>& threadProc,
										const CString& threadName = CString(),
										bool startImmediately = true);

		static TCPointer<CThread> thread();
		void start();
//		void stop();

	private:
		inline CThread(const TCFunction<>&, const CString&, bool);
		~CThread();

		void threadProc();
		void* mThread;
		TCFunction<> mThreadProc;
		CLogControl mLogControl;
		CRunLoop mRunLoop;
		template <class T> friend class TCPointer;
		TCPointer<CThread> mThis;
};

LE_NAMESPACE_END
