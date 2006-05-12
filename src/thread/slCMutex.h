#pragma once

#include <common/config/slPrefix.h>

#if !defined _WIN32
#include <pthread.h>
#endif

LE_NAMESPACE_START

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

LE_NAMESPACE_END
