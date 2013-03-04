#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#import <Cocoa/Cocoa.h>
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#import <UIKit/UIKit.h>
#endif

#include <le/core/thread/slCThread.h>
#include <le/core/auxiliary/slCApplicationDelegate.h>
#include <le/core/auxiliary/slCNotificationCenter.h>
#include <le/gui/slCWindow.h>
#include "slCGuiCocoaApplication.h"

static ::sokira::le::CGuiCocoaApplication* gGuiApplication;

@interface SokiraLE_AppDelegate : NSObject
{
	::sokira::le::CApplicationDelegate* mDelegate;
	::sokira::le::CGuiCocoaApplication* mApp;
}

@end

@implementation SokiraLE_AppDelegate

- (id) init
{
	if ((self = [super init]))
	{
		mApp = gGuiApplication;
		mDelegate = mApp->delegate();
	}
	return self;
}

- (id)initWithDelegate:(::sokira::le::CApplicationDelegate *)delegate andApplication:(::sokira::le::CGuiCocoaApplication *)app
{
	if ((self = [super init]))
	{
		mDelegate = delegate;
		mApp = app;
	}
	return self;
}

- (void) applicationWillFinishLaunching:(NSNotification *)aNotification
{
	mDelegate->applicationWillFinishLaunching(*mApp);
	::sokira::le::CNotificationCenter::instance()->postNotification(mApp, LESTR("com.7lifes.notification.applicationWillFinishLaunching"));
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	mDelegate->applicationDidFinishLaunching(*mApp);
}

- (BOOL)application:(id)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	mDelegate->applicationDidFinishLaunching(*mApp);
	::sokira::le::CNotificationCenter::instance()->postNotification(mApp, LESTR("com.7lifes.notification.applicationDidFinishLaunching"));
	return NO;
}

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	[sender stop: self];
	return NSTerminateCancel;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return mDelegate->applicationShouldTerminateAfterLastWindowClosed(*mApp);
}
#endif

- (void)applicationWillTerminate:(NSNotification *)aNotification
{
	std::cout << "applicationWillTerminate" << std::endl;
	mDelegate->applicationWillTerminate(*mApp);
}

- (void)applicationWillBecomeActive:(NSNotification *)aNotification
{
	std::cout << "applicationWillBecomeActive" << std::endl;
}

- (void)applicationWillResignActive:(NSNotification *)aNotification
{
	std::cout << "applicationWillResignActive" << std::endl;
}

- (void)applicationDidResignActive:(NSNotification *)aNotification
{
	std::cout << "applicationDidResignActive" << std::endl;
}

- (void)applicationWillHide:(NSNotification *)aNotification
{
	
}

- (void)applicationDidHide:(NSNotification *)aNotification
{
	
}

- (void)applicationWillUnhide:(NSNotification *)aNotification
{
	
}

- (void)applicationDidUnhide:(NSNotification *)aNotification
{
	
}

- (void)applicationWillUpdate:(NSNotification *)aNotification
{
	
}

- (void)applicationDidUpdate:(NSNotification *)aNotification
{
	
}

//- (BOOL)applicationShouldHandleReopen:(NSApplication *)theApplication hasVisibleWindows:(BOOL)flag
//{
//
//}
//
//- (NSMenu *)applicationDockMenu:(NSApplication *)sender
//{
//
//}
//
//- (NSError *)application:(NSApplication *)application willPresentError:(NSError *)error
//{
//
//}
//
//- (BOOL)application:(NSApplication *)sender delegateHandlesKey:(NSString *)key
//{
//
//}
//
//- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification
//{
//
//}
//
//
//- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
//{
//
//}
//
//- (void)application:(NSApplication *)sender openFiles:(NSArray *)filenames
//{
//
//}
//
//- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename
//{
//
//}
//
//- (BOOL)application:(NSApplication *)theApplication openTempFile:(NSString *)filename
//{
//
//}
//
//- (BOOL)applicationOpenUntitledFile:(NSApplication *)theApplication
//{
//
//}
//
//- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender
//{
//
//}
//
//
//- (BOOL)application:(NSApplication *)theApplication printFile:(NSString *)filename
//{
//
//}
//
//- (NSApplicationPrintReply)application:(NSApplication *)application printFiles:(NSArray *)fileNames withSettings:(NSDictionary *)printSettings showPrintPanels:(BOOL)showPrintPanels
//{
//
//}

@end


namespace sokira
{
	namespace le
	{

CGuiCocoaApplication::~CGuiCocoaApplication()
{
	// Release mScreens
}

SInt32 CGuiCocoaApplication::runApplication()
{
	NSAutoreleasePool *pool = [NSAutoreleasePool new];
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	id app = [NSApplication sharedApplication];
	id appDelegate = [[SokiraLE_AppDelegate alloc] initWithDelegate: delegate() andApplication: this];
	[app setDelegate: appDelegate];
	[app run];
	[appDelegate release];
	SInt32 result = 0;
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	gGuiApplication = this;
	SInt32 result = UIApplicationMain(commandLine().argumentCount(), (char**)commandLine().argv(), nil, @"SokiraLE_AppDelegate");
#endif

	[pool release];

	std::cout << "EXITING!!!" << std::endl;
	return result;
}

void CGuiCocoaApplication::addWindow(CWindow* window)
{
	if (window)
	{
		window->screenWillBeAddedToApplication(this);
		mScreens.push_back(window);
		window->screenWasAddedToApplication(this);
	}
}

void CGuiCocoaApplication::removeWindow(CWindow* window)
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

void CGuiCocoaApplication::quit()
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	[[NSApplication sharedApplication] stop: nil];
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
//	[[UIApplication sharedApplication] stop: nil];
#endif
}

Bool CGuiCocoaApplication::canQuit() const
{
	return (LE_TARGET_PLATFORM != LE_PLATFORM_IOS);
}

	} // namespace le
} // namespace sokira
