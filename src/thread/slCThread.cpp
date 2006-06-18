
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
	return 0;
}

#else

static pthread_key_t* _threadKey = NULL;

static void* _threadProc(void* theCThread)
{
	if(!_threadKey)
	{
		_threadKey = new pthread_key_t;
		int pthreadKeyCreateResult = pthread_key_create(_threadKey, NULL);
		LE_ASSERT(pthreadKeyCreateResult == 0);
	}

	int pthreadSetSpecificResult = pthread_setspecific(*_threadKey, theThread);
	LE_ASSERT(pthreadSetSpecificResult == 0);

	static_cast<CThread*>(theCThread)->threadProc();
	return NULL;
}

CThread* CThread::thread()
{
	return static_cast<CThread*>(pthread_getspecific(*_threadKey));
}

#endif

CThread::CThread(const TCFunction<>& threadProc, const CString& name,
				 bool startImmediately) :
	mThread(NULL),
	mLogControl(name)
{
	mRunLoop.pushEvent(threadProc);
	if(startImmediately)
	{
		start();
	}
}

TCPointer<CThread> CThread::create(const TCFunction<>& threadProc,
									const CString& name, bool startImmediately)
{
	return new CThread(threadProc, name, startImmediately);
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

	LE_ASSERT(!mThis);
}

void CThread::start()
{
	if(mThis) return;
	mThis.reset(this);
#if !defined _WIN32
	pthread_t* newThread = new pthread_t;
	pthread_create(newThread, NULL, _threadProc,
					static_cast<void*>(this));
#else
	DWORD threadID;
	HANDLE newThread = CreateThread(NULL, 0, _threadProc, static_cast<LPVOID>(this), 0, &threadID);
	LE_ASSERT(newThread == NULL);
#endif

	mThread = static_cast<void*>(newThread);
}

void CThread::threadProc()
{
	// ...

	mThis.release();
	mThis.reset();
}

LE_NAMESPACE_END
