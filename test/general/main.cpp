#pragma comment(lib, "leCore")

#include <le/core/slCClassFactory.h>
#include <le/core/debug/slDebug.h>
#include <le/core/debug/slCAssertControl.h>
#include <le/core/debug/slCAssertionPolicy.h>

#include "slCTestSuite.h"

#ifdef _WIN32_WCE
#include <windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	PROCESS_INFORMATION info;
	MessageBox(NULL, _T("GPS"), _T("Error"), IDOK);
	if (!CreateProcess(_T("\\ResidentFlash\\EnchancedOS\\_os\\os.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &info))
	{
		MessageBox(NULL, _T("Could not run EnchancedOS"), _T("Error"), IDOK);
	}
	else
	{
	//	WaitForSingleObject(info.hProcess, INFINITE);
	}

	return 1;
}

#else
int main(int argc, char * const argv[])
{
	LE_ENTER_LOG;
	using namespace sokira::le;

	CAssertControl::instance()->setAssertionPolicy(new CUnitTestingAssertionPolicy());

	CClassFactory* factory = CClassFactory::defaultInstance();
	CClassFactory::iterator it = factory->beginForChildsOf<CTestSuite>();
	CClassFactory::iterator end = factory->end();

	for (UInt32 i = 1; it != end; ++it, ++i)
	{
		std::cout << i << ". Running test " << it->name() << "..." << std::endl;
		try
		{
			it->create<CTestSuite>()->runTest();
		}
		catch (std::exception& ex)
		{
			std::cout << "Failed because of exception: " << ex.what() << std::endl;
		}
		catch (...)
		{
			std::cout << "Failed because of unknown exception." << std::endl;
		}
	}

	return 0;
}
#endif
