#include <le/core/config/slPrefix.h>

#if !defined _WIN32

#include "slCThreadImplPosix.hp"
#include "slCThreadImplMain.hp"

namespace sokira
{
	namespace le
	{

static inline pthread_key_t threadKey()
{
	static pthread_key_t result = NULL;
	if (!result) pthread_key_create(&result, NULL);
	return result;
}

inline static void* posixThreadProc(void* thread)
{
	pthread_setspecific(threadKey(), thread);
	CThreadImplPosix::threadProc(static_cast<CThreadImplPosix*>(thread));
	return NULL;
}

void CThreadImplPosix::start()
{
	pthread_create(&mThreadID, NULL, posixThreadProc,
					static_cast<void*>(this));
}

CThreadImplBase* CThreadImplPosix::thread()
{
	void* result = pthread_getspecific(threadKey());

	if (!result)
	{
		// This is a main thread and we need to create a new ThreadImpl for it
		result = new CThreadImplMain(pthread_self());
		pthread_setspecific(threadKey(), result);
	}

	return static_cast<CThreadImplBase*> (result);
}

	} // namespace le
} // namespace sokira

#endif // !defined _WIN32
