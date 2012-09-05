#pragma once

#include "slTIFunction.h"
#include <le/core/template/function/slTSFunctionTraits.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// TCFreeFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename FunctionType, typename RetType = typename TSFunctionTraits<FunctionType>::RetType,
						class ParamList = typename TSFunctionTraits<FunctionType>::ParamList>
class TCFreeFunction :
	public TIFunction<RetType, ParamList>
{
	FunctionType mFunction;
	public:
		inline TCFreeFunction(const FunctionType& func) :
			mFunction(func)
		{

		}

		virtual CFunctionDescriptor functionDescriptor() const
		{
			return CFunctionDescriptor(mFunction);
		}

		virtual RetType operator()(const TCTuple<ParamList>& t) const
		{
			return TSFreeFunctionCallWithTuple<RetType, ParamList::length>::callWithTuple(mFunction, t);
		}
};

	} // namespace le
} // namespace sokira
