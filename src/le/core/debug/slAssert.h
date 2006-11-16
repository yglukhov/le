#pragma once

#include <common/config/slPrefix.h>
LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// ASSERTS
////////////////////////////////////////////////////////////////////////////////
#if LE_FLAG_DEBUG

class CObject;

void _le_assert(bool, const char*, unsigned, const char*, const CObject*, const char*);

#	define LE_ASSERT(x) _le_assert((x), #x, __LINE__, __FILE__, NULL, NULL)
#	define LE_ASSERT_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, NULL, message)

#	define LE_ASSERT_EX(x) _le_assert((x), #x, __LINE__, __FILE__, this, NULL)
#	define LE_ASSERT_EX_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, this, message)

#else

#	define LE_ASSERT(x)
#	define LE_ASSERT_MESSAGE(x, message)

#	define LE_ASSERT_EX(x)
#	define LE_ASSERT_EX_MESSAGE(x, message)

#endif // LE_FLAG_DEBUG


////////////////////////////////////////////////////////////////////////////////
// Compile time ASSERT:		STATIC_ASSERT(const expression)
////////////////////////////////////////////////////////////////////////////////
#if LE_FLAG_DEBUG

template <bool expression>
struct TSStaticAssert;

template <>
struct TSStaticAssert<true>
{

};

#define LE_STATIC_ASSERT(expression) \
static LE_NESTED_NAMESPACE TSStaticAssert<((bool)(expression))> _static_assert_object_##__LINE__

#else // LE_FLAG_DEBUG

#define LE_STATIC_ASSERT(expression)

#endif // not LE_FLAG_DEBUG


LE_NAMESPACE_END
