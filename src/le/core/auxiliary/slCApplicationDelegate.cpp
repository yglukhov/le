#include "slCApplicationDelegate.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CApplicationDelegate);

CApplicationDelegate::CApplicationDelegate() :
	mApplication(NULL)
{

}

CApplication* CApplicationDelegate::application()
{
	return mApplication;
}

void CApplicationDelegate::applicationWillFinishLaunching(CApplication& application)
{

}

void CApplicationDelegate::applicationDidFinishLaunching(CApplication& application)
{

}

void CApplicationDelegate::applicationWillTerminate(CApplication& application)
{
	std::cout << "Application will terminate" << std::endl;
}

Bool CApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(CApplication& application)
{
	return false;
}

void CApplicationDelegate::_setApplication(CApplication* application)
{
	mApplication = application;
}

	} // namespace le
} // namespace sokira
