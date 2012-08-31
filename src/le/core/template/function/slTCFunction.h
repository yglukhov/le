#if !defined SL_LE_core_template_function_slTCFunction_h
#define SL_LE_core_template_function_slTCFunction_h

#include <le/core/debug/slAssert.h>
#include <le/core/slTCPointer.h>
#include "base/slTCFreeFunction.h"
#include "slTCVariadicFunction.h"

namespace sokira
{
	namespace le
	{

template <typename RetType = void, class TypeList = TSTypeList<> >
		class TCFunction : public TCFunctionInterfaceMixin<TCFunction<RetType, TypeList>, TSVariadicFunctionConstantResult<RetType>::template TResult, TypeList::length, true>
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
			mFunc(new TCFreeFunction<FuncType, RetType, TypeList>(func))
		{

		}

		inline operator Bool() const
		{
			return (mFunc);
		}

//		template <class TTypeList>
//		inline RetType operator()(const TCTuple<TTypeList>& t) const
//		{
//			return TSFreeFunctionCallWithTuple<RetType, TTypeList::length>::callWithTuple(*mFunc, t);
//		}

//		using TCFunctionInterfaceMixin<TCFunction<RetType, TypeList>, TSVariadicFunctionConstantResult<RetType>::template TResult, TypeList::length, true>::operator();
		inline RetType operator()() const
		{
			return mFunc->operator ()();
		}

		inline CFunctionDescriptor functionDescriptor() const
		{
			return mFunc->functionDescriptor();
		}

#define _le_typenameT(x) ,typename T##x
#define _le_paramT(x) ,T##x p##x
#define _le_val(x) ,p##x

#define _LE_DEFINE_TCFunction_operator(x)													\
		template <typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT)>					\
		inline RetType operator()(T0 p0 LE_PP_REPETITION_FROM_0_TO(x, _le_paramT)) const	\
		{																					\
			return mFunc->operator ()(p0 LE_PP_REPETITION_FROM_0_TO(x, _le_val));			\
		}

		_LE_DEFINE_TCFunction_operator(0)
		_LE_DEFINE_TCFunction_operator(1)
		_LE_DEFINE_TCFunction_operator(2)
		_LE_DEFINE_TCFunction_operator(3)
		_LE_DEFINE_TCFunction_operator(4)
		_LE_DEFINE_TCFunction_operator(5)
		_LE_DEFINE_TCFunction_operator(6)
		_LE_DEFINE_TCFunction_operator(7)
		_LE_DEFINE_TCFunction_operator(8)
		_LE_DEFINE_TCFunction_operator(9)
		_LE_DEFINE_TCFunction_operator(10)
		_LE_DEFINE_TCFunction_operator(11)
		_LE_DEFINE_TCFunction_operator(12)

#undef _LE_DEFINE_TCFunction_operator
#undef _le_paramT
#undef _le_typenameT
#undef _le_val

	private:
		TCPointer<TIFunction<RetType, TypeList> > mFunc;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_function_slTCFunction_h
