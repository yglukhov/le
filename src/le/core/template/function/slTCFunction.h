#pragma once

#include <le/core/slTCPointer.h>
#include "base/slTCFreeFunction.h"

namespace sokira
{
	namespace le
	{

template <typename RetType = void, class TypeList = TSTypeList<> >
class TCFunction
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

		inline RetType operator()() const
		{
			return mFunc->operator ()();
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
