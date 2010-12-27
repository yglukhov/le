#if !defined SL_LE_core_config_base_slGCC_h
#define SL_LE_core_config_base_slGCC_h

#if defined __GNUC__

#define LE_FLAG_COMPILER_CONFIGURED LE_TRUE

// __GNUC__
// __GNUC_MINOR__
// __GNUC_PATCHLEVEL__
//		These macros are defined by all GNU compilers that use the C
//		preprocessor: C, C++, Objective-C and Fortran. Their values are the
//		major version, minor version, and patch level of the compiler, as
//		integer constants. For example, GCC 3.2.1 will define __GNUC__ to 3,
//		__GNUC_MINOR__ to 2, and __GNUC_PATCHLEVEL__ to 1. These macros are also
//		defined if you invoke the preprocessor directly.

#define LE_COMPILER_VERSION_MAJOR __GNUC__
#define LE_COMPILER_VERSION_MINOR __GNUC_MINOR__

#if defined __GNUC_PATCHLEVEL__
#define LE_COMPILER_VERSION_BUG __GNUC_PATCHLEVEL__
#else
#define LE_COMPILER_VERSION_BUG 0
#endif

// In case of GCC version format we have 3 parts
#define LE_COMPILER_VERSION_PART_COUNT 3
#define LE_COMPILER_VERSION_PART_0 LE_COMPILER_VERSION_MAJOR
#define LE_COMPILER_VERSION_PART_1 LE_COMPILER_VERSION_MINOR
#define LE_COMPILER_VERSION_PART_2 LE_COMPILER_VERSION_BUG

// Define compiler family
#define LE_COMPILER_VENDOR_STRING "GNU"
#define LE_COMPILER_NAME_STRING "GCC"
#define LE_COMPILER_VERSION_STRING #LE_COMPILER_VERSION_MAJOR "." #LE_COMPILER_VERSION_MINOR "." #LE_COMPILER_VERSION_BUG


#define LE_COMPILER_VERSION (LE_COMPILER_VERSION_MAJOR * 10000 \
                               + LE_COMPILER_VERSION_MINOR * 100 \
                               + LE_COMPILER_VERSION_BUG)

#ifdef __MACH__
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#define LE_TARGET_PLATFORM LE_PLATFORM_IOS
#else
#define LE_TARGET_PLATFORM LE_PLATFORM_MACOSX
#endif
#define LE_TARGET_PLATFORM_FAMILY LE_PLATFORM_FAMILY_UNIX
#endif

#ifdef __ppc__
#define LE_ENDIAN LE_ENDIAN_BIG
#else
#define LE_ENDIAN LE_ENDIAN_LITTLE
#endif


#endif // defined __GNUC__

#endif // not defined SL_LE_core_config_base_slGCC_h
