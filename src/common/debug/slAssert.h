#pragma once

#include <common/config/slPrefix.h>
LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// ASSERTS
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

class CObject;

void _le_assert(bool, const char*, unsigned, const char*, const CObject*, const char*);

#	define ASSERT(x) _le_assert((x), #x, __LINE__, __FILE__, NULL, NULL)
#	define ASSERT_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, NULL, message)

#	define ASSERT_EX(x) _le_assert((x), #x, __LINE__, __FILE__, this, NULL)
#	define ASSERT_EX_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, this, message)

#else

#	define ASSERT(x)
#	define ASSERT_MESSAGE(x, message)

#	define ASSERT_EX(x)
#	define ASSERT_EX_MESSAGE(x, message)

#endif // defined DEBUG


////////////////////////////////////////////////////////////////////////////////
// Compile time ASSERT:		STATIC_ASSERT(const expression)
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

template <bool expression>
struct TSStaticAssert;

template <>
struct TSStaticAssert<true>
{

};

#define LE_STATIC_ASSERT(expression) \
static LE_NESTED_NAMESPACE TSStaticAssert<((bool)(expression))> _static_assert_object_##__LINE__

#else // defined DEBUG

#define LE_STATIC_ASSERT(expression)

#endif // not defined DEBUG


LE_NAMESPACE_END