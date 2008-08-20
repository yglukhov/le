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

namespace sokira
{
	namespace le
	{

class CScript
{
	public:

};


	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCScript_h
