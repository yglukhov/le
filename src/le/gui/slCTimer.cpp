#include <iostream>
#include "slCTimer.h"

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#include "base/slCTimerImplWindows.hp"
#else
#include "base/slCTimerImplMacOS.hp"
#endif


namespace sokira
{
	namespace le
	{

CTimer::CTimer(UInt32 msInterval)
{
	mImpl = new CTimerImpl(msInterval, static_cast<void*>(this));
}

void CTimer::__onTimer_private()
{
	std::cout << "Timer!" << std::endl;
}


	} // namespace le
} // namespace sokira
