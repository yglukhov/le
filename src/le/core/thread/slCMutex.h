#if !defined SL_LE_core_thread_slCMutex_h
#define SL_LE_core_thread_slCMutex_h

#include <le/core/strategies/slCNonCopyable.h>


namespace sokira
{
	namespace le
	{

class CMutexImpl;

class CMutex : CNonCopyable
{
	public:
		CMutex(bool recursive = false);
		void lock();
		void unlock();
		~CMutex();
	private:
		CMutexImpl* mImpl;
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

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_thread_slCMutex_h
