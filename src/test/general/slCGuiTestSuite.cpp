#include <stdio.h>
#include <le/core/config/slCompiler.h>
#include <le/core/thread/slCThread.h>
#include "slCGuiTestSuite.h"

// Do not test gui on windows CE

#if LE_TARGET_PLATFORM != LE_PLATFORM_WINDOWS_CE
#pragma comment(lib, "leGui")
#pragma comment(lib, "leSound")
#include <le/gui/auxiliary/slCGuiApplication.h>
#endif

namespace sokira
{
	namespace le
	{

//LE_IMPLEMENT_RUNTIME_CLASS(CGuiTestSuite);

void CGuiTestSuite::testGuiApp()
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS_CE
	printf("Skipping gui test\n");
#else
	for (int i = 5; i > 0; --i)
	{
		printf("Preparing to test Gui. Press any key to skip. [%d]\r", i);
//		CThread::sleep(1);
	}
	printf("\nRunning gui test...\n");

	::sokira::le::CGuiApplication app;
	app.setDelegateClass(LESTR("CGuiTestAppDelegate"));
	app.run(0, NULL);
#endif
}

	} // namespace le
} // namespace sokira
