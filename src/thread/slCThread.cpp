
#if defined _WIN32
	#pragma message(__FILE__ " : warning LE: If <windows.h> included, it won't compile until Language Extensions are enabled in project properties.")
	#define WIN32_LEAN_AND_MEAN
	#define STRICT
	#include <windows.h>

	#include <common/debug/slAssert.h>
	LE_STATIC_ASSERT(sizeof(void*) == sizeof(HANDLE));
#else // defined _WIN32
	#include <pthread.h>
#endif // not defined _WIN32

#include "slCThread.h"

LE_NAMESPACE_START


struct SThreadProcContext
{
	inline SThreadProcContext(const TCFunction<>& proc, CThread* thr) :
		threadProc(proc),
		thread(thr)
	{

	}

	const TCFunction<>& threadProc;
	CThread* thread;
};


#if defined _WIN32
static DWORD WINAPI _threadProc(LPVOID threadProcContext)
{
	const SThreadProcContext* threadData = static_cast<SThreadProcContext*>(threadProcContext);

	// TODO: attach threadData->thread to OS thread

	(threadData->threadProc)();
	delete threadData;
	return NULL;
}

#else

static pthread_key_t* _threadKey = NULL;

static void* _threadProc(void* threadProcContext)
{
	const SThreadProcContext* threadData = static_cast<SThreadProcContext*>(threadProcContext);

	if(!_threadKey)
	{
		_threadKey = new pthread_key_t;
		int pthreadKeyCreateResult = pthread_key_create(_threadKey, NULL);
		LE_ASSERT(pthreadKeyCreateResult == 0);
	}

	int pthreadSetSpecificResult = pthread_setspecific(*_threadKey, threadData->thread);
	LE_ASSERT(pthreadSetSpecificResult == 0);

	(threadData->threadProc)();
	delete threadData;
	return NULL;
}

CThread* CThread::thread()
{
	return static_cast<CThread*>(pthread_getspecific(*_threadKey));
}

#endif

CThread::CThread(const TCFunction<>& threadProc, bool startImmediately) :
	mThread(NULL),
	mThreadProc(threadProc),
		mSomeString("THREAD_IS_VALID")
{
	if(startImmediately)
	{
		start();
	}
}

CThread* CThread::create(const TCFunction<>& threadProc, bool startImmediately)
{
	return new CThread(threadProc, startImmediately);
}

CThread::~CThread()
{
	if(mThread)
	{
#if defined _WIN32
		CloseHandle(static_cast<HANDLE>(mThread));
#else // defined _WIN32
		// TODO: stop the thread
		delete static_cast<pthread_t*>(mThread);
#endif // not defined _WIN32
	}
}


void CThread::start()
{
	if(mThread)
		return;

	SThreadProcContext* threadProcContext = new SThreadProcContext(mThreadProc, this);

#if !defined _WIN32
	pthread_t* newThread = new pthread_t;
	pthread_create(newThread, NULL, _threadProc,
					static_cast<void*>(threadProcContext));
#else
	DWORD threadID;
	HANDLE newThread = CreateThread(NULL, 0, _threadProc, static_cast<LPVOID>(threadProcContext), 0, &threadID);
	LE_ASSERT(newThread == NULL);
#endif

	mThread = static_cast<void*>(newThread);
}


LE_NAMESPACE_END
