#include "slCGuiApplication.h"

#include <le/gui/slCScreen.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCGuiApplicationCocoaImpl.hp"
#define CGuiApplicationImpl CGuiApplicationCocoaImpl
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCGuiApplicationWindowsImpl.hp"
#define CGuiApplicationImpl CGuiApplicationWindowsImpl
#endif

namespace sokira
{
	namespace le
	{

CGuiApplication::CGuiApplication() :
	mImpl(new CGuiApplicationImpl())
{

}

CGuiApplication::~CGuiApplication()
{
	std::cout << "CGuiApplication::~CGuiApplication" << std::endl;
	for (std::vector<CScreen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
	{
		delete *it;
	}
	delete ((CGuiApplicationImpl*)mImpl);
}

void CGuiApplication::addScreen(CScreen* screen)
{
	if (screen)
	{
		screen->screenWillBeAddedToApplication(this);
		screenWillBeAddedToApplication(screen);
		mScreens.push_back(screen);
		screenWasAddedToApplication(screen);
		screen->screenWasAddedToApplication(this);
	}
}

void CGuiApplication::quit()
{
	static_cast<CGuiApplicationImpl*>(mImpl)->quit();
}

void CGuiApplication::screenWillBeAddedToApplication(CScreen* screen)
{
	static_cast<CGuiApplicationImpl*>(mImpl)->screenWillBeAddedToApplication(screen);
}

void CGuiApplication::screenWasAddedToApplication(CScreen* screen)
{
	static_cast<CGuiApplicationImpl*>(mImpl)->screenWasAddedToApplication(screen);
}

SInt32 CGuiApplication::runApplication()
{
	LE_ENTER_LOG;

	return static_cast<CGuiApplicationImpl*>(mImpl)->run(delegate(), this);
}

	} // namespace le
} // namespace sokira
