#pragma once

#include <iostream>
#include <string>

#if defined __GNUC__
#define LE_PP_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define LE_PP_PRETTY_FUNCTION __FUNCSIG__
#else
#define LE_PP_PRETTY_FUNCTION "_ unknown function name _"
#endif


////////////////////////////////////////////////////////////////////////////////
// ASSERTS
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

//#define LOG

class CObject;

void _assert(bool, const char*, unsigned, const char*, const CObject*, const char*);

#	define ASSERT(x) _assert((x), #x, __LINE__, __FILE__, NULL, NULL)
#	define ASSERT_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, NULL, message)

#	define ASSERT_EX(x) _assert((x), #x, __LINE__, __FILE__, this, NULL)
#	define ASSERT_EX_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, this, message)

#else

#	define ASSERT(x)
#	define ASSERT_MESSAGE(x, message)

#	define ASSERT_EX(x)
#	define ASSERT_EX_MESSAGE(x, message)

#endif // defined DEBUG

#include "CLogEntry.h"

