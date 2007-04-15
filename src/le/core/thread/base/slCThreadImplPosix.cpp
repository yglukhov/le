#include <le/core/config/slPrefix.h>

#if !defined _WIN32

#include "slCThreadImplPosix.hp"
#include "slCThreadImplMain.hp"

namespace sokira
{
	namespace le
	{

inline static void* posixThreadProc(void* thread)
{
	CThreadImplBase::threadProc(static_cast<CThreadImplPosix*>(thread));
	return NULL;
}

void CThreadImplPosix::start()
{
	pthread_create(&mThreadID, NULL, posixThreadProc,
					static_cast<void*>(this));
}

CThreadImplBase* CThreadImplPosix::thread()
{
	pthread_t threadToFind = pthread_self();
	if(!threadList().empty())
	{
		for (std::list<CThreadImplPosix*>::iterator it = threadList().begin(); it != threadList().end(); ++it)
		{
			if (pthread_equal((*it)->mThreadID, threadToFind))
			{
				return (*it);
			}
		}
	}

	// Assume that the current thread is a main thread.
	CThreadImplPosix* mainThread = new CThreadImplMain(threadToFind);
	threadList().push_back(mainThread);

	return mainThread;
}

	} // namespace le
} // namespace sokira

#endif // !defined _WIN32
