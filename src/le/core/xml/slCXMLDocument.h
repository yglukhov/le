#if !defined SL_LE_core_xml_slCXMLDocument_h
#define SL_LE_core_xml_slCXMLDocument_h

#include <le/core/xml/slCXMLParser.h>

namespace sokira
{
	namespace le
	{

class CXMLNode;
class CURL;

class CXMLDocument
{
	public:
		CXMLDocument(const CURL& url);
		CXMLDocument(std::istream& stream);
		~CXMLDocument();

		CXMLNode* rootNode();

		void dump(std::ostream& stream);

	private:
		void onStartTag(CXMLParser* parser, CString name, CXMLParser::TArrtibutes attributes);
		void onEndTag(CXMLParser*, CString tagName);
		void onData(CXMLParser* parser, CString data);
		void onError(CXMLParser* parser, CString error);

		void initWithStream(std::istream& stream);

		CXMLNode* mRootNode;
		CXMLNode* mCurrentNode;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_xml_slCXMLDocument_h
