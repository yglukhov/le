#import <Cocoa/Cocoa.h>

#include <le/core/auxiliary/slCApplicationDelegate.h>
#include "slCGuiApplicationCocoaImpl.hp"

@interface SokiraLE_AppDelegate : NSObject
{
	::sokira::le::CApplicationDelegate* mDelegate;
	::sokira::le::CApplication* mApp;
}

@end

@implementation SokiraLE_AppDelegate

- (id)initWithDelegate:(::sokira::le::CApplicationDelegate *)delegate andApplication:(::sokira::le::CApplication *)app
{
	id theobj = [self init];
	mDelegate = delegate;
	mApp = app;
	return theobj;
}

- (void) applicationWillFinishLaunching:(NSNotification *)aNotification
{
	mDelegate->applicationWillFinishLaunching(*mApp);
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	mDelegate->applicationDidFinishLaunching(*mApp);
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	[sender stop: self];
	return NSTerminateCancel;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return NO;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification
{
//	std::cout << "applicationWillTerminate" << std::endl;
}

- (void)applicationWillBecomeActive:(NSNotification *)aNotification
{

}

- (void)applicationDidResignActive:(NSNotification *)aNotification
{

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

SInt32 CGuiApplicationCocoaImpl::run(CApplicationDelegate* delegate, CApplication* application)
{
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    NSApplication *app = [NSApplication sharedApplication];
	[app setDelegate:[[SokiraLE_AppDelegate alloc] initWithDelegate: delegate andApplication: application]];
	
//	NSImage* myImage = [NSImage imageNamed: @"NSFollowLinkFreestandingTemplate"]; // Get the original icon
//	[app setApplicationIconImage: myImage];

	
//	[[NSMenu alloc] initWithTitle:@"MyApp"];
//		[NSApp setMenu:[[NSMenu alloc] initWithTitle:@"MyApp"]];
    [app run];
	[pool release];

	return 0;
}

	} // namespace le
} // namespace sokira
