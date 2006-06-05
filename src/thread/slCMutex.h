#pragma once

#include <common/strategies/slCNonCopyable.h>

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

class CMutexLock : CNonCopyable
{
	public:
		inline CMutexLock(CMutex& mutex) :
			mMutex(mutex)
		{
			mMutex.lock();
		}

		inline ~CMutexLock()
		{
			mMutex.unlock();
		}

	private:
		CMutex& mMutex;
};

LE_NAMESPACE_END
