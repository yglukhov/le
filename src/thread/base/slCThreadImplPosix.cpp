#include <common/config/slPrefix.h>

#if !defined _WIN32

#include "slCThreadImplPosix.hp"

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

#endif // !defined _WIN32
