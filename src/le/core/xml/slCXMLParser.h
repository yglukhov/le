#if !defined SL_LE_core_xml_slCXMLParser_h
#define SL_LE_core_xml_slCXMLParser_h

#include <le/core/slCString.h>
#include <le/core/template/function/slTCFunction.h>

namespace sokira
{
	namespace le
	{

class CXMLParser
{
	public:
		CXMLParser();

		Bool parseStream(std::istream& stream);
		Bool parseStream(std::wistream& stream);

		typedef std::map<CString, CString> TArrtibutes;
		typedef TCFunction<void, TSTypeList<CXMLParser*, CString, TArrtibutes> > TOnStartTag;
		typedef TCFunction<void, TSTypeList<CXMLParser*, CString> > TOnEndTag;
		typedef TCFunction<void, TSTypeList<CXMLParser*, CString> > TOnData;
		typedef TCFunction<void, TSTypeList<CXMLParser*, CString> > TOnError;

		void setOnStartTag(TOnStartTag& onStartTag);
		void setOnEndTag(TOnEndTag& onEndTag);
		void setOnData(TOnData& onData);
		void setOnError(TOnError& onError);

		void setTrimsWhitespace(Bool trimWhitespace = true);
		Bool trimsWhitespace() const;

		UInt32 line() const;
		UInt32 column() const;

	private:

		Bool parse();

		inline WChar nextNChar();
		inline WChar nextWChar();

		inline Bool isNEOF();
		inline Bool isWEOF();

		inline WChar nextChar();
		inline Bool isEOF();

		inline void onStartTag(const CString& tagName, const TArrtibutes& attrs);
		inline void onEndTag(const CString& tagName);
		inline void onData(CString data);
		inline void onError(const CString& error);

		WChar (CXMLParser::*mNextChar)();
		Bool (CXMLParser::*mIsEOF)();

		UInt32 mFlags;
		UInt32 mLine;
		UInt32 mColumn;

		void *mStream;
		TOnStartTag mOnStartTag;
		TOnEndTag mOnEndTag;
		TOnData mOnData;
		TOnError mOnError;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_xml_slCXMLParser_h
