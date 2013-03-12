#if !defined SL_LE_core_script_slCParserGrammar_h
#define SL_LE_core_script_slCParserGrammar_h

#include <le/core/script/slCLexer.h>
#include <le/core/template/function/slTCFunction.h>


namespace sokira
{
	namespace le
	{

class CParserGrammar : public CObject
{
	class CGrammarReader;
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CParserGrammar)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	typedef TCFunction<CObject::Ptr, TSTypeList<std::vector<CObject::Ptr>&> > TRuleHandler;
	enum EAssociativity
	{
		eAssociativityUndefined = 0,
		eAssociativityLeft,
		eAssociativityRight,
		eAssociativityNone
	};

	public:
		CParserGrammar();
		~CParserGrammar();

		void addRule(const CString& identifier, const std::vector<CString>& subIdentifiers, TRuleHandler handler);
		void addTerminal(const CString& identifier, ITokenMatcher* matcher, TRuleHandler handler);
		void setAssociativity(const CString& identifier, EAssociativity associativity);
		void setPrecedence(const CString& identifier, SInt precedence);

		CGrammarReader operator [] (const CString& identifier);

		struct SRule
		{
			CString identifier;
			std::vector<CString> subIdentifiers;
			TRuleHandler handler;
		};

		const std::vector<SRule*>& rules() const
		{
			return mRules;
		}

		bool isTerminal(const CString& identifier) const;
		bool isNonTerminal(const CString& identifier) const;
		EAssociativity associativityForTerminal(const CString& identifier) const;
		SInt precedenceForTerminal(const CString& identifier) const;
		ITokenMatcher* matcherForTerminal(const CString& identifier) const;

	private:
		class CGrammarReader
		{
			public:
				inline CGrammarReader(CParserGrammar*, const CString&);
				~CGrammarReader();

				CGrammarReader& operator >> (const CString& obj);
				CGrammarReader& operator >> (char c);
				CGrammarReader& operator >> (TCPointer<ITokenMatcher> matcher);

				CGrammarReader& operator << (const CString& obj);
				CGrammarReader& operator << (const TRuleHandler& obj);
				CGrammarReader& operator << (const char* obj);
				CGrammarReader& operator << (char c);
				CGrammarReader& operator << (TCPointer<ITokenMatcher> matcher);
				CGrammarReader& operator << (int pass);

			private:
				void flush();
				CString uniqueIdentifierForMatcher(ITokenMatcher* matcher) const;

				CParserGrammar* mParser;
				CString mIdentifier;
				std::vector<CString> mSubIdentifiers;
				TRuleHandler mHandler;
		};

		void finalize() const;
		inline bool ruleWithIdentifierExists(const CString& identifier) const;
		CString terminalForIdentifier(const CString& identifier) const;

		std::vector<SRule*> mRules;
		std::map<CString, ITokenMatcher*> mTokens;
		std::map<CString, EAssociativity> mAssociativities;
		std::map<CString, SInt> mPrecedences;

		mutable bool mFinalized;
		mutable std::set<CString> mTerminals;
		mutable std::set<CString> mNonTerminals;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_script_slCParserGrammar_h
