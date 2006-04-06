#pragma once

#define NULL 0 // TODO remove it

class IFuncContext;

class CThread
{
	public:
		template<typename RetVal, typename ContextVal>
		CThread(RetVal(*threadProc)(ContextVal), ContextVal context, bool startImmediately = true);

		~CThread();

		void start();
//		void stop();
	
	private:
		void* mThread;
		IFuncContext* mFuncContext;
};

class IFuncContext
{
	public:
		virtual void run() = 0;
		virtual ~IFuncContext();
};

template<typename RetVal, typename ContextVal>
class TCFuncContext : public IFuncContext
{
	public:
		TCFuncContext(const ContextVal& context, RetVal(*func)(ContextVal)) :
				mContext(context), mFunc(func)
		{

		}

	private:
		ContextVal mContext;
		RetVal(*mFunc)(ContextVal);
		
		virtual void run()
		{
			mFunc(mContext);
		}
};

template<typename RetVal, typename ContextVal>
CThread::CThread(RetVal(*threadProc)(ContextVal), ContextVal context, bool startImmediately) :
	mThread(NULL),
	mFuncContext(new TCFuncContext<RetVal, ContextVal>(context, threadProc))
{
	if(startImmediately)
	{
		start();
	}
}
