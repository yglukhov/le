#if !defined H_slCGuiTestSuite_included
#define H_slCGuiTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CGuiTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CGuiTestSuite);

	public:
		virtual void runTest()
		{
			testGuiApp();
		}

	private:
		void testGuiApp();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCGuiTestSuite_included
