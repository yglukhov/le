#if !defined SL_LE_core_template_function_base_slTSFunctionCallWithTuple_h
#define SL_LE_core_template_function_base_slTSFunctionCallWithTuple_h

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include <le/core/template/tuple/slTCTuple.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// TSFreeFunctionCallWithTuple
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, unsigned length>
struct TSFreeFunctionCallWithTuple;

template <typename R>
struct TSFreeFunctionCallWithTuple<R, 0>
{
	template <typename FuncType, class TList>
	static inline R callWithTuple(FuncType func, const TCTuple<TList>& /*tuple*/)
	{
		return func();
	}
};

#define _le_val(x) ,tuple.template value<x>()

#define _LE_DEFINE_TSFreeFunctionCallWithTuple(x)								\
template <typename R>															\
struct TSFreeFunctionCallWithTuple<R, x + 1>									\
{																				\
	template <typename FuncType, class TList>									\
	static inline R callWithTuple(FuncType func, const TCTuple<TList>& tuple)	\
	{																			\
		return func(tuple.template value<0>() LE_PP_REPETITION_FROM_0_TO(x, _le_val)); \
	}																			\
};

_LE_DEFINE_TSFreeFunctionCallWithTuple(0)
_LE_DEFINE_TSFreeFunctionCallWithTuple(1)
_LE_DEFINE_TSFreeFunctionCallWithTuple(2)
_LE_DEFINE_TSFreeFunctionCallWithTuple(3)
_LE_DEFINE_TSFreeFunctionCallWithTuple(4)
_LE_DEFINE_TSFreeFunctionCallWithTuple(5)
_LE_DEFINE_TSFreeFunctionCallWithTuple(6)
_LE_DEFINE_TSFreeFunctionCallWithTuple(7)
_LE_DEFINE_TSFreeFunctionCallWithTuple(8)
_LE_DEFINE_TSFreeFunctionCallWithTuple(9)
_LE_DEFINE_TSFreeFunctionCallWithTuple(10)
_LE_DEFINE_TSFreeFunctionCallWithTuple(11)

#undef _LE_DEFINE_TSFreeFunctionCallWithTuple
#undef _le_val


////////////////////////////////////////////////////////////////////////////////
// TSMemberFunctionCallWithTuple
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, unsigned length>
struct TSMemberFunctionCallWithTuple;

template <typename R>
struct TSMemberFunctionCallWithTuple<R, 0>
{
	template <typename FuncType, class TList>
	static inline R callWithTuple(FuncType func, const TCTuple<TList>& tuple)
	{
		return (tuple.template value<0>()->*func)();
	}
};

#define _le_val(x) ,tuple.template value<x + 1>()

#define _LE_DEFINE_TSMemberFunctionCallWithTuple(x)						\
template <typename R>											\
struct TSMemberFunctionCallWithTuple<R, x + 1>						\
{																		\
	template <typename FuncType, class TList>							\
	static inline R callWithTuple(FuncType func, const TCTuple<TList>& tuple)	\
	{																	\
		return (tuple.template value<0>()->*func)(						\
			tuple.template value<1>()									\
			LE_PP_REPETITION_FROM_0_TO(x, _le_val));					\
	}																	\
};

_LE_DEFINE_TSMemberFunctionCallWithTuple(0)
_LE_DEFINE_TSMemberFunctionCallWithTuple(1)
_LE_DEFINE_TSMemberFunctionCallWithTuple(2)
_LE_DEFINE_TSMemberFunctionCallWithTuple(3)
_LE_DEFINE_TSMemberFunctionCallWithTuple(4)
_LE_DEFINE_TSMemberFunctionCallWithTuple(5)
_LE_DEFINE_TSMemberFunctionCallWithTuple(6)
_LE_DEFINE_TSMemberFunctionCallWithTuple(7)
_LE_DEFINE_TSMemberFunctionCallWithTuple(8)
_LE_DEFINE_TSMemberFunctionCallWithTuple(9)
_LE_DEFINE_TSMemberFunctionCallWithTuple(10)
_LE_DEFINE_TSMemberFunctionCallWithTuple(11)

#undef _le_val
#undef _LE_DEFINE_TSMemberFunctionCallWithTuple

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_xml_slCXMLParser_h
