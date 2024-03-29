#pragma once

#ifdef _MSC_VER

#define LE_FLAG_COMPILER_CONFIGURED LE_TRUE

// _MSC_VER usually expands to something like xxyz, where
// xx - major revision,
// y - minor revision,
// z - bug
#define LE_COMPILER_VERSION _MSC_VER

#if LE_COMPILER_VERSION < 1000
#define LE_COMPILER_VERSION_MAJOR ((LE_COMPILER_VERSION-(LE_COMPILER_VERSION%10))/100)
#else
#define LE_COMPILER_VERSION_MAJOR ((LE_COMPILER_VERSION-(LE_COMPILER_VERSION%100))/100)
#endif // LE_COMPILER_VERSION < 1000

#define LE_COMPILER_VERSION_MINOR_AND_BUG (LE_COMPILER_VERSION - LE_COMPILER_VERSION_MAJOR*100)
#define LE_COMPILER_VERSION_BUG (LE_COMPILER_VERSION_MINOR_AND_BUG%10)
#define LE_COMPILER_VERSION_MINOR ((LE_COMPILER_VERSION_MINOR_AND_BUG - \
									LE_COMPILER_VERSION_BUG)/10)

// In case of MSVC version format we have 3 parts
#define LE_COMPILER_VERSION_PART_COUNT 3
#define LE_COMPILER_VERSION_PART_0 LE_COMPILER_VERSION_MAJOR
#define LE_COMPILER_VERSION_PART_1 LE_COMPILER_VERSION_MINOR
#define LE_COMPILER_VERSION_PART_2 LE_COMPILER_VERSION_BUG

// Define compiler family
#define LE_COMPILER_VENDOR_STRING "Microsoft"
#define LE_COMPILER_NAME_STRING "Visual C++"
////////////////////////////////////////////////////////////////////////////////
// Some version deciphering
// 1300 - MS Visual C++ .NET
// 1310 - MS Visual C++ .NET 2003
// 1400 - MS Visual C++ .NET 2005

#if (LE_COMPILER_VERSION == 1300)
#define LE_COMPILER_VERSION_STRING ".NET"
#elif (LE_COMPILER_VERSION == 1310)
#define LE_COMPILER_VERSION_STRING ".NET 2003"
#elif (LE_COMPILER_VERSION == 1400)
#define LE_COMPILER_VERSION_STRING ".NET 2005"
#endif

#ifdef WINCE
#define LE_TARGET_PLATFORM LE_PLATFORM_WINDOWS_CE
#else
#define LE_TARGET_PLATFORM LE_PLATFORM_WINDOWS
#endif

#define LE_TARGET_PLATFORM_FAMILY LE_PLATFORM_FAMILY_WINDOWS

#define LE_ENDIAN LE_ENDIAN_LITTLE

#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4503 )

#endif // defined _MSC_VER
