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
	//		testXMLParser2();
		}

	private:
		void testXMLParser();
		void testXMLParser2();

		void onStartTag(CXMLParser*, CString tagName, CXMLParser::TArrtibutes);
		void onEndTag(CXMLParser*, CString tagName);
		void onData(CXMLParser* parser, CString data);
		void onError(CXMLParser* parser, CString error);

		void onStartTagDump(CXMLParser*, CString tagName, CXMLParser::TArrtibutes);
		void onEndTagDump(CXMLParser*, CString tagName);
		void onDataDump(CXMLParser* parser, CString data);
		void onErrorDump(CXMLParser* parser, CString error);

		CString mActualResult;
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCXMLTestSuite_included
