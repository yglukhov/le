#if !defined SL_LE_core_template_function_slTCFunction_h
#define SL_LE_core_template_function_slTCFunction_h

//#include <le/core/debug/slAssert.h>
#include <le/core/slTCPointer.h>
#include "base/slTIFunction.h"
#include "slTCVariadicFunction.h"

namespace sokira
{
	namespace le
	{

template <typename RetType = void, class TypeList = TSTypeList<> >
class TCFunction : public TIFunction<RetType, TypeList>
{
	public:
		TCFunction()
		{

		}

		TCFunction(const TCFunction& func) :
			mFunc(func.mFunc)
		{

		}

		template <typename FuncType>
		inline TCFunction(FuncType func) :
			mFunc(new TCFunctionImpl<FuncType>(func))
		{

		}

		inline operator Bool() const
		{
			return (mFunc);
		}

		using TIFunction<RetType, TypeList>::operator();
		virtual RetType operator()(const TCTuple<TypeList>& t) const
		{
			return mFunc->operator()(t);
		}

		virtual CFunctionDescriptor functionDescriptor() const
		{
			return mFunc->functionDescriptor();
		}

	private:
		TCPointer<TIFunction<RetType, TypeList> > mFunc;

		template <typename FunctionType>
		class TCFunctionImpl : public TIFunction<RetType, TypeList>
		{
				FunctionType mFunction;
			public:
				inline TCFunctionImpl(const FunctionType& func) :
					mFunction(func)
				{ }

				virtual CFunctionDescriptor functionDescriptor() const
				{
					return CFunctionDescriptor(mFunction);
				}

				virtual RetType operator()(const TCTuple<TypeList>& t) const
				{
					return TSFreeFunctionCallWithTuple<RetType, TypeList::length>::callWithTuple(mFunction, t);
				}
		};
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_function_slTCFunction_h
