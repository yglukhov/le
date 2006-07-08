#include <common/config/slPrefix.h>

#ifdef _WIN32

#include "slCThreadImplWindows.hp"

LE_NAMESPACE_START

inline static DWORD WINAPI windowsThreadProc(LPVOID thread)
{
	CThreadImplBase::threadProc(static_cast<CThreadImplWindows*>(thread));
	return NULL;
}

void CThreadImplWindows::start()
{
	mThread = CreateThread(NULL, 0, windowsThreadProc, static_cast<LPVOID>(this), 0, &mThreadID);
}

LE_NAMESPACE_END

#endif // defined _WIN32
