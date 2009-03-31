#if !defined included_core_script_slCScript_h
#define included_core_script_slCScript_h

// Performing a script:
// std::istream | CTokenizer | CLexer | [ CLogicOptimizer | ]
// | CCompiler | [ CBytecodeOptimizer ] | CMachine
//
// Compiling script:
// std::istream | CTokenizer | CLexer | CLogicOptimizer |
// | CCompiler | CBytecodeOptimizer | std::ostream
//
// Performing compiled script
// std::istream | [ CBytecodeOptimizer | ] CMachine
//
// Requirements:
// CTokenizer	requires std::istream
//				produces CToken
//
// CLexer		requires CTokenizer
//				produces CLexem
//
// CLogicOptimizer	requires CLexer
//					produces CLexem
//					inherits CLexer
//
// CCompiler		requires CLexer
//					produces byte

#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

class CScript
{
	public:
	//	virtual void addFunction(const CString& signature, function);
		virtual void addClass(const CClass& theClass);
	//	virtual void addInstance(const CString& name, instance);
		virtual void runFromStream(std::istream& stream);
};

	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCScript_h
