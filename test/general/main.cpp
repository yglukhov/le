#pragma comment(lib, "leCore")

#include <le/core/slCClassFactory.h>
#include <le/core/debug/slDebug.h>
#include <le/core/debug/slCAssertControl.h>
#include <le/core/debug/slCAssertionPolicy.h>

#include "slCTestSuite.h"

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
		it->create<CTestSuite>()->runTest();
	}

	return 0;
}
