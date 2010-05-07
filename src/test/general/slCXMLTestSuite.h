#if !defined H_slCXMLTestSuite_included
#define H_slCXMLTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CXMLTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CXMLTestSuite);

	public:
		virtual void runTest()
		{
			testXMLParser();
			testXMLDocument();
			testDictionaries();
			testPlistParsing();
		}

	private:
		void testXMLParser();
		void testXMLDocument();
		void testDictionaries();
		void testPlistParsing();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCXMLTestSuite_included
