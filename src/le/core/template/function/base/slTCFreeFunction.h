#pragma once

#include "slTIFunction.h"
#include <le/core/template/function/slTSFunctionTraits.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
template <typename RetType, class TypeList, unsigned paramCount, typename FuncType>
class TCFreeFunctionBase;

////////////////////////////////////////////////////////////////////////////////
// TCFreeFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename FunctionType, typename RetType = typename TSFunctionTraits<FunctionType>::RetType,
						typename ParamList = typename TSFunctionTraits<FunctionType>::ParamList>
class TCFreeFunction :
	public TCFreeFunctionBase<RetType, ParamList, ParamList::length, FunctionType>
{
	public:
		inline TCFreeFunction(FunctionType func) :
			TCFreeFunctionBase<RetType, ParamList, ParamList::length, FunctionType>(func)
		{

		}
};






////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, class TypeList, typename FuncType>
class TCFreeFunctionBase <RetType, TypeList, 0, FuncType> :
	public TIFunction<RetType, TypeList>
{
	protected:
		FuncType mFunction;
		inline TCFreeFunctionBase(FuncType func) : mFunction(func)
		{

		}

	public:
		RetType operator()() const
		{
			return mFunction();
		}
};

#define _le_param(x) ,typename TypeList::template TypeAt<x>::result p##x
#define _le_val(x) ,p##x

#define _LE_DEFINE_TCFreeFunctionBase(x)								\
template <typename RetType, class TypeList, typename FuncType>			\
class TCFreeFunctionBase <RetType, TypeList, x + 1, FuncType> :			\
	public TIFunction<RetType, TypeList>								\
{																		\
	protected:															\
		FuncType mFunction;												\
		inline TCFreeFunctionBase(FuncType func) : mFunction(func)		\
		{																\
																		\
		}																\
																		\
	public:																\
		RetType operator()(typename TypeList::template TypeAt<0>::result p0 LE_PP_REPETITION_FROM_0_TO(x, _le_param)) const \
		{																\
			return mFunction(p0 LE_PP_REPETITION_FROM_0_TO(x, _le_val));\
		}																\
};

_LE_DEFINE_TCFreeFunctionBase(0)
_LE_DEFINE_TCFreeFunctionBase(1)
_LE_DEFINE_TCFreeFunctionBase(2)
_LE_DEFINE_TCFreeFunctionBase(3)
_LE_DEFINE_TCFreeFunctionBase(4)
_LE_DEFINE_TCFreeFunctionBase(5)
_LE_DEFINE_TCFreeFunctionBase(6)
_LE_DEFINE_TCFreeFunctionBase(7)
_LE_DEFINE_TCFreeFunctionBase(8)
_LE_DEFINE_TCFreeFunctionBase(9)
_LE_DEFINE_TCFreeFunctionBase(10)

#undef _LE_DEFINE_TCFreeFunctionBase
#undef _le_param
#undef _le_val

////////////////////////////////////////////////////////////////////////////////
// Maximum number of parameters for TCFreeFunction
#define LE_PP_FREEFUNCTION_LIMIT 10


	} // namespace le
} // namespace sokira
