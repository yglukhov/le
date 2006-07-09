#pragma once

#include <memory>
#include <common/strategies/slCNonCopyable.h>


LE_NAMESPACE_START

class CMutexImpl;

class CMutex : CNonCopyable
{
	public:
		CMutex(bool recursive = false);
		~CMutex();
		void lock();
		void unlock();

	private:
		std::auto_ptr<CMutexImpl> mImpl;
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
