#if !defined SL_LE_gui_auxiliary_slCGuiApplication_h
#define SL_LE_gui_auxiliary_slCGuiApplication_h

#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "slCGuiCocoaApplication.h"
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "slCGuiWindowsApplication.h"
#endif

namespace sokira
{
	namespace le
	{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
		typedef CGuiCocoaApplication CGuiApplication;
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
		typedef CGuiWindowsApplication CGuiApplication;
#endif
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_auxiliary_slCGuiApplication_h
