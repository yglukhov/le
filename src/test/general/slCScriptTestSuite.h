#if !defined H_slCScriptTestSuite_included
#define H_slCScriptTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CScriptTestSuite : public CTestSuite
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CScriptTestSuite)
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELECTOR(testTokenizer)
		LE_RTTI_SELECTOR(testParser)
	LE_RTTI_END

	void testTokenizer();
	void testParser();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCScriptTestSuite_included
