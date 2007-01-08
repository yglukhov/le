#include <le/core/config/slPrefix.h>

#ifdef _WIN32

#include "slCThreadImplWindows.hp"
#include "slCThreadImplMain.hp"

namespace sokira
{
	namespace le
	{

inline static DWORD WINAPI windowsThreadProc(LPVOID thread)
{
	CThreadImplBase::threadProc(static_cast<CThreadImplWindows*>(thread));
	return NULL;
}

void CThreadImplWindows::start()
{
	mThread = CreateThread(NULL, 0, windowsThreadProc, static_cast<LPVOID>(this), 0, &mThreadID);
}

CThreadImplBase* CThreadImplWindows::thread()
{
	DWORD threadToFind = GetCurrentThreadId();
	if(!threadList().empty())
	{
		for (std::list<CThreadImplWindows*>::iterator it = threadList().begin(); it != threadList().end(); ++it)
		{
			if ((*it)->mThreadID == threadToFind)
			{
				return (*it);
			}
		}
	}

	// Assume that the current thread is a main thread.
	CThreadImplWindows* mainThread = new CThreadImplMain(threadToFind);
	threadList().push_back(mainThread);

	return mainThread;
}

	} // namespace le
} // namespace sokira

#endif // defined _WIN32
