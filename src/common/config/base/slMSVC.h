#pragma once

#ifdef _MSC_VER

#define LE_FLAG_COMPILER_CONFIGURED LE_TRUE

// _MSC_VER usually expands to something like xxyz, where
// xx - major revision,
// y - minor revision,
// z - bug
#define LE_COMPILER_VERSION _MSC_VER
#define LE_COMPILER_VERSION_MAJOR (LE_COMPILER_VERSION-(LE_COMPILER_VERSION%100))
#define LE_COMPILER_VERSION_MINOR_AND_BUG (LE_COMPILER_VERSION - LE_COMPILER_VERSION_MAJOR)
#define LE_COMPILER_VERSION_BUG (LE_COMPILER_VERSION_MINOR_AND_BUG%10)
#define LE_COMPILER_VERSION_MINOR (LE_COMPILER_VERSION_MINOR_AND_BUG - \
									LE_COMPILER_VERSION_BUG)

// In case of MSVC version format we have 3 parts
#define LE_COMPILER_VERSION_PART_COUNT 3
#define LE_COMPILER_VERSION_PART_0 LE_COMPILER_VERSION_MAJOR
#define LE_COMPILER_VERSION_PART_1 LE_COMPILER_VERSION_MINOR
#define LE_COMPILER_VERSION_PART_2 LE_COMPILER_VERSION_BUG

// Define compiler family
#define LE_COMPILER_IS_MSVC

////////////////////////////////////////////////////////////////////////////////
// Some version deciphering
// 1300 - MS Visual C++ .NET
// 1310 - MS Visual C++ .NET 2003
// 1400 - MS Visual C++ .NET 2005

#if (LE_COMPILER_VERSION == 1300)
#define LE_COMPILER_IS_MSVC_NET
#elif (LE_COMPILER_VERSION == 1310)
#define LE_COMPILER_IS_MSVC_2003
#elif (LE_COMPILER_VERSION == 1400)
#define LE_COMPILER_IS_MSVC_2005
#endif

#endif // defined _MSC_VER
