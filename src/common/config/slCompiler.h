#if !defined H_slCompiler_included
#define H_slCompiler_included

#include "slPrefix.h"


#if (!defined LE_FLAG_COMPILER_CONFIGURED) || (!LE_FLAG_COMPILER_CONFIGURED)
#	include "base/slGCC.h"
#endif

#if (!defined LE_FLAG_COMPILER_CONFIGURED) || (!LE_FLAG_COMPILER_CONFIGURED)
#	include "base/slMSVC.h"
#endif


////////////////////////////////////////////////////////////////////////////////
// If compiler is not located, then just mark it.
#if !defined LE_FLAG_COMPILER_CONFIGURED
#	define LE_FLAG_COMPILER_CONFIGURED LE_FALSE
#endif

#endif // not defined H_slCompiler_included
