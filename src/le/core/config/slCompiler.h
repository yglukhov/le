#if !defined H_slCompiler_included
#define H_slCompiler_included

#include "slPrefix.h"

#define LE_PLATFORM_WINDOWS 1
#define LE_PLATFORM_WINDOWS_CE 2
#define LE_PLATFORM_UNIX 3
#define LE_PLATFORM_MACOSX 4
#define LE_PLATFORM_IOS 5

#define LE_PLATFORM_FAMILY_WINDOWS 1
#define LE_PLATFORM_FAMILY_UNIX 2

#define LE_ENDIAN_BIG 1
#define LE_ENDIAN_LITTLE 2

#if (!defined LE_FLAG_COMPILER_CONFIGURED) || (!LE_FLAG_COMPILER_CONFIGURED)
#	include "base/slGCC.h"
#endif

#if (!defined LE_FLAG_COMPILER_CONFIGURED) || (!LE_FLAG_COMPILER_CONFIGURED)
#	include "base/slMSVC.h"
#endif


#if ! defined LE_TARGET_PLATFORM
#define LE_TARGET_PLATFORM LE_PLATFORM_UNIX

#	if ! defined LE_TARGET_PLATFORM_FAMILY
#	define LE_TARGET_PLATFORM_FAMILY LE_PLATFORM_FAMILY_UNIX
#	endif

#else

#	if ! defined LE_TARGET_PLATFORM_FAMILY
#		if LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS || LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS_CE
#			define LE_TARGET_PLATFORM_FAMILY LE_PLATFORM_FAMILY_WINDOWS
#		else
#			define LE_TARGET_PLATFORM_FAMILY LE_PLATFORM_FAMILY_UNIX
#		endif
#	endif

#endif

////////////////////////////////////////////////////////////////////////////////
// If compiler is not located, then just mark it.
#if !defined LE_FLAG_COMPILER_CONFIGURED
#	define LE_FLAG_COMPILER_CONFIGURED LE_FALSE
#elif (LE_FLAG_COMPILER_CONFIGURED == LE_TRUE)
#	define LE_COMPILER_FULL_NAME_STRING LE_COMPILER_VENDOR_STRING##" "##	\
			LE_COMPILER_NAME_STRING##" "##LE_COMPILER_VERSION_STRING
#endif // defined LE_FLAG_COMPILER_CONFIGURED

#if !defined LE_ENDIAN
#	define LE_ENDIAN LE_ENDIAN_LITTLE
#endif

#if defined(__LP64__) && (__LP64__ == 1)
#	define LE_ARCHITECTURE_BITS 64
#else
#	define LE_ARCHITECTURE_BITS 32
#endif // defined(__LP64__) && (__LP64__ == 1)

#endif // not defined H_slCompiler_included
