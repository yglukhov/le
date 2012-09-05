#if !defined H_slCGeneralTestSuite_included
#define H_slCGeneralTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CGeneralTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CGeneralTestSuite);

	public:
		virtual void runTest()
		{
			testTypeTraits();
			testTypeList();
			testBasicTypes();
			testBinds();
			testTuples();
			testStrings();
			testUrls();
			testFunctionTraits();
			testPreprocessor();
			testAny();
		}

	private:
		void testTypeTraits();
		void testTypeList();
		void testBasicTypes();
		void testBinds();
		void testTuples();
		void testStrings();
		void testUrls();
		void testFunctionTraits();
		void testPreprocessor();
		void testAny();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCGeneralTestSuite_included
