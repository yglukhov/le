#if !defined H_slCScriptTestSuite_included
#define H_slCScriptTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CScriptTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CScriptTestSuite);

	public:
		virtual void runTest()
		{
			testTokenizer();
		}

	private:
		void testTokenizer();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCScriptTestSuite_included
