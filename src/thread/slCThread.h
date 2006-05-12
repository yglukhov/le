#pragma once

#include <common/config/slPrefix.h>
#include <template/function/slTCFunction.h>
#include <string>

LE_NAMESPACE_START

class CThread
{
	public:
		static CThread* create(const TCFunction<>& threadProc,
							   bool startImmediately = true);
		
		
		static CThread* thread();
		void start();
//		void stop();

		const char* someString()
		{
			return mSomeString.c_str();
		}
		
	private:
		inline CThread(const TCFunction<>&, bool);
		~CThread();

		void* mThread;
		TCFunction<> mThreadProc;
		std::string mSomeString;
};

LE_NAMESPACE_END
