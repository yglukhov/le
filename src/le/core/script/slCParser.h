#if !defined SL_LE_core_script_slCParser_h
#define SL_LE_core_script_slCParser_h


#include <le/core/slCObject.h>
#include <le/core/template/function/slTCFunction.h>
#include "slCParser.h"
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


	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_script_slCParser_h
