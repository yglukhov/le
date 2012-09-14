#pragma once

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/template/function/slTSFunctionTraits.h>
#include <le/core/template/function/slTCVariadicFunction.h>
#include <le/core/template/tuple/slTCTuple.h>

namespace sokira
{
	namespace le
	{

class CFunctionDescriptor;

////////////////////////////////////////////////////////////////////////////////
// TIFunction class declaration
////////////////////////////////////////////////////////////////////////////////
template <typename RetType, class TypeList>
class TIFunction :
		public TCConcreteFunctionInterfaceMixin<TIFunction<RetType, TypeList>, RetType, TypeList, true>,
		public CSimpleRefCountable
{
	public:
		using TCConcreteFunctionInterfaceMixin<TIFunction<RetType, TypeList>, RetType, TypeList, true>::operator();

		virtual CFunctionDescriptor functionDescriptor() const  = 0;
		virtual RetType operator()(const TCTuple<TypeList>& tuple) const = 0;
};


	} // namespace le
} // namespace sokira
