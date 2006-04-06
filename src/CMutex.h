#pragma once

#if !defined _WIN32
#include <pthread.h>
#endif

class CMutex
{
	public:
		CMutex(bool recursive = false);
		~CMutex();
		void lock();
		void unlock();

#if !defined _WIN32
	private:
		pthread_mutex_t mMutex;
#endif
};