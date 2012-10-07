#if !defined included_core_script_slCLexer_h
#define included_core_script_slCLexer_h

//#include <iterator>
#include <le/core/slCObject.h>
#include <le/core/template/function/slTCFunction.h>
#include "slCTokenizer.h"
#include "slCParserGrammar.h"

namespace sokira
{
	namespace le
	{

//class CParserGrammarReader;
//struct CRule;
//
//class CParser : public CObject
//{
//	LE_RTTI_BEGIN
//		LE_RTTI_SELF(CParser)
//		LE_RTTI_SINGLE_PUBLIC_PARENT
//	LE_RTTI_END
//
//	public:
//	
//	typedef TCFunction<CObject::Ptr, TSTypeList<std::vector<CObject::Ptr>&> > TRuleHandler;
//	CParser();
//	~CParser();
//
//	void addRule(const CString& identifier, const std::vector<CString>& subIdentifiers, TRuleHandler handler);
//	void setLexer(CLexer::Ptr lexer)
//	{
//		mLexer = lexer;
//	}
//
//	CLexer::Ptr lexer() const
//	{
//		return mLexer;
//	}
//
//	void setEntryIdentifier(const CString& entry)
//	{
//		mEntryIdentifier = entry;
//	}
//
//	CString entryIdentifier() const
//	{
//		return mEntryIdentifier;
//	}
//
//	CObject::Ptr parse();
//
//	CParserGrammarReader operator [] (const CString& identifier);
//
//	UInt32 position() const
//	{
//		return mPosition;
//	}
//
//	void setPosition(UInt32 position)
//	{
//		mPosition = position;
//	}
//	
//private:
//
//	bool isTerminal(const CString& identifier) const;
//	bool parseUsingRule(CRule* rule, CObject::Ptr& result, std::vector<void*>& rulesStack);
//	bool parseForRuleIdentifier(const CString& identifier, CObject::Ptr& result, std::vector<void*>& rulesStack);
//
//	CToken nextToken();
//	CLexer::Ptr mLexer;
//	void* mRules;
//	CString mEntryIdentifier;
//	std::vector<CToken> mTokens;
//	std::vector<void*> mRulesStack;
//	UInt32 mPosition;
//};
//
//class CParserGrammarReader
//{
//	friend class CParser;
//
//	public:
//		~CParserGrammarReader();
//
//		CParserGrammarReader& operator >> (const CString& obj);
//		CParserGrammarReader& operator >> (char c);
//
//		CParserGrammarReader& operator << (const CString& obj);
//		CParserGrammarReader& operator << (const CParser::TRuleHandler& obj);
//		CParserGrammarReader& operator << (const char* obj);
//		CParserGrammarReader& operator << (char c);
//
//	private:
//		inline CParserGrammarReader(CParser*, const CString&);
//		void flush();
//
//		CParser* mParser;
//		CString mIdentifier;
//		std::vector<CString> mSubIdentifiers;
//		CParser::TRuleHandler mHandler;
//};
//
class CParser : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CParser)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CObject::Ptr parse(std::istream& stream);

		void setGrammar(CParserGrammar::Ptr grammar);
		CParserGrammar::Ptr grammar() const;

	private:
		CParserGrammar::Ptr mGrammar;
};

class CSokriptParser : public CParser
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CSokriptParser)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CSokriptParser();
};



	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCLexer_h
