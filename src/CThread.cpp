#include "CThread.h"

#if !defined _WIN32
#include <pthread.h>
#else
#pragma warning("Threading is NOT implemented in Win32!")
struct pthread_t
{

};
#endif

IFuncContext::~IFuncContext()
{

}

static void* threadFunc(void* context)
{
	static_cast<IFuncContext*>(context)->run();
	return NULL;
}

CThread::~CThread()
{
	if(mThread)
	{
		// TODO: stop the thread
		delete static_cast<pthread_t*>(mThread);
	}

	delete mFuncContext;
}

void CThread::start()
{
	if(mThread)
		return;

	pthread_t* newThread = new pthread_t;

#if !defined _WIN32
	pthread_create(newThread, NULL, threadFunc,
						static_cast<void*>(dynamic_cast<IFuncContext*>(mFuncContext)));
#else
	threadFunc(mFuncContext);
#endif

	mThread = static_cast<void*>(newThread);
}