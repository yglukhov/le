

#if defined _WIN32
	#pragma message(__FILE__ " : warning LE: If <windows.h> included, it won't compile until Language Extensions are enabled in project properties.")
	#define WIN32_LEAN_AND_MEAN
	#define STRICT
	#include <windows.h>
#else // defined _WIN32
	#include <pthread.h>
#endif // not defined _WIN32

#include "CThread.h"
#include <debug/Assert.h>


#if defined _WIN32
static DWORD WINAPI _threadProc(LPVOID threadProc)
#else
static void* _threadProc(void* threadProc)
#endif
{
	TCFunction<>* pThreadProc = static_cast<TCFunction<>*>(threadProc);
	(*pThreadProc)();
	int a;
	unsigned b;
	if(b<a)
	{

	}
	return NULL;
}


CThread::CThread(TCFunction<> threadProc, bool startImmediately) :
	mThread(NULL),
	mThreadProc(threadProc)
{
	if(startImmediately)
	{
		start();
	}
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


STATIC_ASSERT(sizeof(void*) == sizeof(HANDLE));


void CThread::start()
{
	if(mThread)
		return;

#if !defined _WIN32
	pthread_t* newThread = new pthread_t;
	pthread_create(newThread, NULL, _threadProc,
					static_cast<void*>(&mThreadProc));
#else
	DWORD threadID;
	HANDLE newThread = CreateThread(NULL, 0, _threadProc, static_cast<LPVOID>(&mThreadProc), 0, &threadID);
	ASSERT(newThread == NULL);
#endif

	mThread = static_cast<void*>(newThread);
}