#include "slCApplicationDelegate.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CApplicationDelegate);

void CApplicationDelegate::applicationWillFinishLaunching(CApplication& application)
{

}

void CApplicationDelegate::applicationDidFinishLaunching(CApplication& application)
{

}

Bool CApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(CApplication& application)
{
	return false;
}


	} // namespace le
} // namespace sokira
