#include "CMutex.h"

#if defined _WIN32
	#pragma message(__FILE__ " : warning LE: Mutexes are not implemented for Win32 yet.")
#endif

CMutex::CMutex(bool recursive)
{
#if !defined _WIN32
	if(recursive)
	{
		// Creating RECURSIVE mutex
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		
		pthread_mutex_init(&mMutex, &attr);
		
		pthread_mutexattr_destroy(&attr);
	}
	else
	{
		// Creating NORMAL mutex
		pthread_mutex_init(&mMutex, NULL);
	}
#endif
}

CMutex::~CMutex()
{
#if !defined _WIN32
	pthread_mutex_destroy(&mMutex);
#endif
}

void CMutex::lock()
{
#if !defined _WIN32
	pthread_mutex_lock(&mMutex);
#endif
}

void CMutex::unlock()
{
#if !defined _WIN32
	pthread_mutex_unlock(&mMutex);
#endif
}