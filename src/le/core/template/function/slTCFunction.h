#pragma once

#include <le/core/config/slPrefix.h>
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

		inline RetType operator()() const
		{
			return mFunc->operator ()();
		}

		template <typename T0>
		inline RetType operator()(T0 p0) const
		{
			return mFunc->operator ()(p0);
		}

		template <typename T0, typename T1>
		inline RetType operator()(T0 p0, T1 p1) const
		{
			return mFunc->operator ()(p0, p1);
		}

		template <typename T0, typename T1, typename T2>
		inline RetType operator()(T0 p0, T1 p1, T2 p2) const
		{
			return mFunc->operator ()(p0, p1, p2);
		}

	private:
		TCPointer<TIFunction<RetType, TypeList> > mFunc;
};

	} // namespace le
} // namespace sokira
