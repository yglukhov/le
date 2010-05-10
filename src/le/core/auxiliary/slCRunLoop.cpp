#include "slCRunLoop.h"

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCRunloopImplMac.hp"
#elif  LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCRunloopImplWin.hp"
#else
#error No implementation
#endif

namespace sokira
{
	namespace le
	{

CRunLoop::CRunLoop() :
	mImpl(new CRunLoopImpl())
{

}

CRunLoop::~CRunLoop()
{
	delete mImpl;
}

void CRunLoop::run()
{
	mImpl->run();
}

void CRunLoop::stop()
{
	mImpl->stop();
}

CTimer CRunLoop::scheduledTimerWithInterval(UInt32 msInterval, TCFunction<> timerFunc)
{
	return mImpl->scheduledTimerWithInterval(msInterval, timerFunc);
}

	} // namespace le
} // namespace sokira
