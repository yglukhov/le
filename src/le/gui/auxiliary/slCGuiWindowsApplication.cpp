
#include <le/core/auxiliary/slCApplicationDelegate.h>
#include <le/core/thread/slCThread.h>
#include <le/gui/slCWindow.h>
#include "slCGuiWindowsApplication.h"

namespace sokira
{
	namespace le
	{

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS

		SInt32 CGuiWindowsApplication::runApplication()
		{
			delegate()->applicationWillFinishLaunching(*this);
			delegate()->applicationDidFinishLaunching(*this);
			CThread::thread().runLoop().run();
			return 0;
		}

		void CGuiWindowsApplication::addWindow(CWindow* window)
		{
			if (window)
			{
				window->screenWillBeAddedToApplication(this);
				mScreens.push_back(window);
				window->screenWasAddedToApplication(this);
			}
		}

		void CGuiWindowsApplication::removeWindow(CWindow* window)
		{
			if (window)
			{
				window->screenWillBeRemovedFromApplication(this);
				std::vector<CWindow*>::iterator it = std::find(mScreens.begin(), mScreens.end(), window);
				if (it != mScreens.end())
				{
					mScreens.erase(it);
				}
				window->screenWasRemovedFromApplication(this);
			}
		}

		void CGuiWindowsApplication::quit()
		{
			CThread::thread().runLoop().stop();
		}

#endif

	} // namespace le
} // namespace sokira
