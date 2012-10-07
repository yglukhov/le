#include <le/core/slCString.h>
#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTestSuite);

void CTestSuite::runTest()
{
	std::set<ISelector*> selectors = objectClass().selectors();
	for (std::set<ISelector*>::iterator it = selectors.begin(); it != selectors.end(); ++it)
	{
		CString name = (*it)->name();
		if (name.hasPrefix("test"))
		{
			selector(name)();
		}
	}
}

	} // namespace le
} // namespace sokira
