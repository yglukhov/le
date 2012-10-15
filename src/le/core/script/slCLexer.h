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

class CData;

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

typedef CObject::Ptr (*TSokriptFunction)(CObject::Ptr);

class CSokript : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CSokript)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CSokript();
		bool compileStream(std::istream& stream, std::ostream& ostream);
		CObject::Ptr runBytecode(const CData& data);

		CObject::Ptr runScript(const CString& script);

		void addExternalObject(const CString& name, CObject::Ptr object);
		void addExternalFunction(const CString& name, TSokriptFunction function);

	private:
		std::map<CString, CObject::Ptr> mExternalObjects;
};



	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCLexer_h
