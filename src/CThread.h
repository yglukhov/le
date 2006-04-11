#pragma once

#include <function/TCFunction.h>

class IFuncContext;

class CThread
{
	public:
		CThread(TCFunction<> threadProc, bool startImmediately = true);
		~CThread();

		void start();
//		void stop();

	private:
		void* mThread;
		TCFunction<> mThreadProc;
};

//class IFuncContext
//{
//	public:
//		virtual void run() = 0;
//		virtual ~IFuncContext();
//};
//
//template<typename RetVal, typename ContextVal>
//class TCFuncContext : public IFuncContext
//{
//	public:
//		TCFuncContext(const ContextVal& context, RetVal(*func)(ContextVal)) :
//				mContext(context), mFunc(func)
//		{
//
//		}
//
//	private:
//		ContextVal mContext;
//		RetVal(*mFunc)(ContextVal);
//		
//		virtual void run()
//		{
//			mFunc(mContext);
//		}
//};


