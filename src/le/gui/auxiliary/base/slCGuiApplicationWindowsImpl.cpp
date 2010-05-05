#include <windows.h>

#include <le/core/auxiliary/slCApplicationDelegate.h>
#include "slCGuiApplicationWindowsImpl.hp"

namespace sokira
{
	namespace le
	{

SInt32 CGuiApplicationWindowsImpl::run(CApplicationDelegate* delegate, CApplication* application)
{
	MSG msg;

	std::map<DWORD, std::string> messageNames;
#define LE_ADD_MESSAGE_NAME(name) messageNames[name] = #name
	LE_ADD_MESSAGE_NAME(WM_CLOSE);
	LE_ADD_MESSAGE_NAME(WM_QUIT);
	LE_ADD_MESSAGE_NAME(WM_CREATE);
	LE_ADD_MESSAGE_NAME(WM_DESTROY);
	LE_ADD_MESSAGE_NAME(WM_TIMER);
	LE_ADD_MESSAGE_NAME(WM_ACTIVATE);

	delegate->applicationWillFinishLaunching(*application);

	delegate->applicationDidFinishLaunching(*application);
	std::cout << "Starting application runloop" << std::endl;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		//std::map<DWORD, std::string>::iterator it = messageNames.find(msg.message);
		//if (it != messageNames.end())
		//{
		//	std::cout << it->second << std::endl;
		//}
		//else
		//{
		//	std::cout << "Message: " << msg.message << std::endl;
		//}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	std::cout << "Exited application runloop" << std::endl;

	return 0;
}

void CGuiApplicationWindowsImpl::quit()
{

}

	} // namespace le
} // namespace sokira
