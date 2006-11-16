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
#elif (LE_FLAG_COMPILER_CONFIGURED == LE_TRUE)
#	define LE_COMPILER_FULL_NAME_STRING LE_COMPILER_VENDOR_STRING##" "##	\
			LE_COMPILER_NAME_STRING##" "##LE_COMPILER_VERSION_STRING
#endif // defined LE_FLAG_COMPILER_CONFIGURED

#endif // not defined H_slCompiler_included
