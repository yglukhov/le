#if !defined SL_LE_core_debug_slAssert_h
#define SL_LE_core_debug_slAssert_h

#include <le/core/slTypes.h>


namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// ASSERTS
////////////////////////////////////////////////////////////////////////////////
class CObject;

void _le_assert(bool, const char*, unsigned, const char*, const CObject*, const char*);

#	define LE_ASSERT(x) ::sokira::le::_le_assert(_LE_BOOL_CAST(x), #x, __LINE__, __FILE__, NULL, NULL)
#	define LE_ASSERT_MESSAGE(x, message) ::sokira::le::_le_assert(_LE_BOOL_CAST(x), #x, __LINE__, __FILE__, NULL, message)

#	define LE_ASSERT_EX(x) ::sokira::le::_le_assert(_LE_BOOL_CAST(x), #x, __LINE__, __FILE__, this, NULL)
#	define LE_ASSERT_EX_MESSAGE(x, message) ::sokira::le::_le_assert(_LE_BOOL_CAST(x), #x, __LINE__, __FILE__, this, message)


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


	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_debug_slAssert_h
