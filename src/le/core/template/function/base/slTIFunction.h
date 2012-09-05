#pragma once

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/template/function/slTSFunctionTraits.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
template <typename RetType, class TList, unsigned TListLength> class TIFunctionBase;

class CFunctionDescriptor;

////////////////////////////////////////////////////////////////////////////////
// TIFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, class TypeList>
class TIFunction :
		public TIFunctionBase<RetType, TypeList, TypeList::length>,
		public CSimpleRefCountable
{
	public:
		virtual CFunctionDescriptor functionDescriptor() const  = 0;
};





////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// TIFunctionBase specialization. Limitations are equal to LE_PP_IFUNCTION_LIMIT
template <typename RetType, class TList>
class TIFunctionBaseBase
{
	public:
		virtual RetType operator()(const TCTuple<TList>& tuple) const = 0;
};

template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 0> : public TIFunctionBaseBase<RetType, TList>
{
	public:
	using TIFunctionBaseBase<RetType, TList>::operator();
	RetType operator()() const { return operator()(TCTuple<TList>()); };
};

#define _le_val(x) ,typename TList::template TypeAt<x>::result a##x
#define _le_tuple(x) t.template setValue<x>(a##x);

#define _LE_DEFINE_TIFunctionBase(x) \
template <typename RetType, class TList> \
class TIFunctionBase<RetType, TList, x + 1> : public TIFunctionBaseBase<RetType, TList> \
{ \
	public: \
		using TIFunctionBaseBase<RetType, TList>::operator(); \
		RetType operator()(typename TList::template TypeAt<0>::result a0 LE_PP_REPETITION_FROM_0_TO(x, _le_val)) const \
	{ \
		TCTuple<TList> t; \
		t.template setValue<0>(a0); \
		LE_PP_REPETITION_FROM_0_TO(x, _le_tuple) \
		return operator()(t); \
	} \
};

_LE_DEFINE_TIFunctionBase(0)
_LE_DEFINE_TIFunctionBase(1)
_LE_DEFINE_TIFunctionBase(2)
_LE_DEFINE_TIFunctionBase(3)
_LE_DEFINE_TIFunctionBase(4)
_LE_DEFINE_TIFunctionBase(5)
_LE_DEFINE_TIFunctionBase(6)
_LE_DEFINE_TIFunctionBase(7)
_LE_DEFINE_TIFunctionBase(8)
_LE_DEFINE_TIFunctionBase(9)
_LE_DEFINE_TIFunctionBase(10)

#undef _LE_DEFINE_TIFunctionBase
#undef _le_val


////////////////////////////////////////////////////////////////////////////////
// Maximum number of parameters for TIFunction
#define LE_PP_IFUNCTION_LIMIT 10


	} // namespace le
} // namespace sokira
