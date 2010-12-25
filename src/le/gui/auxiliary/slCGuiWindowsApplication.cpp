
#include <le/core/auxiliary/slCApplicationDelegate.h>
#include <le/core/thread/slCThread.h>
#include <le/gui/slCWindow.h>
#include "slCGuiWindowsApplication.h"

namespace sokira
{
	namespace le
	{
		SInt32 CGuiWindowsApplication::runApplication()
		{
			delegate()->applicationWillFinishLaunching(*this);
			delegate()->applicationDidFinishLaunching(*this);
			CThread::thread().runLoop().run();
			return 0;
		}

		void CGuiWindowsApplication::addScreen(CWindow* screen)
		{
			if (screen)
			{
				screen->screenWillBeAddedToApplication(this);
				mScreens.push_back(screen);
				screen->screenWasAddedToApplication(this);
			}
		}

		void CGuiWindowsApplication::quit()
		{
			CThread::thread().runLoop().stop();
		}
		
	} // namespace le
} // namespace sokira
