#include <windows.h>

#include <le/core/auxiliary/slCApplicationDelegate.h>
#include <le/core/thread/slCThread.h>
#include <le/gui/slCScreen.h>
#include "slCGuiWindowsApplication.h"

namespace sokira
{
	namespace le
	{
		SInt32 CGuiWindowsApplication::runApplication()
		{
			std::map<DWORD, std::string> messageNames;
#define LE_ADD_MESSAGE_NAME(name) messageNames[name] = #name
			LE_ADD_MESSAGE_NAME(WM_CLOSE);
			LE_ADD_MESSAGE_NAME(WM_QUIT);
			LE_ADD_MESSAGE_NAME(WM_CREATE);
			LE_ADD_MESSAGE_NAME(WM_DESTROY);
			LE_ADD_MESSAGE_NAME(WM_TIMER);
			LE_ADD_MESSAGE_NAME(WM_ACTIVATE);
			
			delegate()->applicationWillFinishLaunching(*this);

			delegate()->applicationDidFinishLaunching(*this);
			std::cout << "Starting application runloop" << std::endl;

			CThread::thread().runLoop().run();
			
			//MSG msg;
			
			//while (GetMessage(&msg, NULL, 0, 0))
			//{
			//	//std::map<DWORD, std::string>::iterator it = messageNames.find(msg.message);
			//	//if (it != messageNames.end())
			//	//{
			//	//	std::cout << it->second << std::endl;
			//	//}
			//	//else
			//	//{
			//	//	std::cout << "Message: " << msg.message << std::endl;
			//	//}
			
			//	TranslateMessage(&msg);
			//	DispatchMessage(&msg);
			//}
			
			std::cout << "Exited application runloop" << std::endl;
			
			return 0;
		}

		void CGuiWindowsApplication::addScreen(CScreen* screen)
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
			PostQuitMessage(0);
		}
		
	} // namespace le
} // namespace sokira
