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
		public TIFunctionBase<RetType, TypeList, TypeList::length>
{
	public:
		virtual CFunctionDescriptor functionDescriptor() const { return CFunctionDescriptor(); };
};





////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// TIFunctionBase specialization. Limitations are equal to LE_PP_IFUNCTION_LIMIT
template <typename RetType, class TList>
class TIFunctionBase<RetType, TList, 0> : public CSimpleRefCountable
{
	public: virtual RetType operator()() const { return RetType(); };
};

#define _le_val(x) ,typename TList::template TypeAt<x>::result

#define _LE_DEFINE_TIFunctionBase(x) \
template <typename RetType, class TList> \
class TIFunctionBase<RetType, TList, x + 1> : public CSimpleRefCountable \
{ \
	public: virtual RetType operator()(typename TList::template TypeAt<0>::result LE_PP_REPETITION_FROM_0_TO(x, _le_val)) const = 0; \
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
