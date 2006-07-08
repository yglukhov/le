#pragma once

#include <template/function/slTCFunction.h>
#include <common/types/slCString.h>

LE_NAMESPACE_START

class CThreadImplBase;

class CThread
{
	public:
		CThread(const CThread& copy);
		CThread(const TCFunction<>& threadProc, const CString& threadName = LESTR(""),
				bool startImmediately = true);
		~CThread();

		static CThread thread();
		void start();
		void stop();
		bool isRunning() const;

		const CThread& operator = (const CThread& copy);

	private:
		CThread();
		inline CThread(CThreadImplBase*);

		CThreadImplBase* mImpl;
};


LE_NAMESPACE_END
