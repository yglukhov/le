#pragma once

#include <memory>
#include "base/TCFreeFunction.h"

template <typename RetType, class TypeList>
class TCFunction
{
	public:
		TCFunction()
		{
		
		}

		TCFunction(const TCFunction& func)// :
		//	mFunc(new TCFreeFunction<RetType, TypeList, FuncType>(func))
		{
		
		}

		template <typename FuncType>
		inline TCFunction(FuncType func) :
			mFunc(new TCFreeFunction<RetType, TypeList, FuncType>(func))
		{
		
		}

		inline RetType operator()()
		{
			return (*mFunc)();
		}

		template <typename T0>
		inline RetType operator()(T0 p0)
		{
			return (*mFunc)(p0);
		}

		template <typename T0, typename T1>
		inline RetType operator()(T0 p0, T1 p1)
		{
			return (*mFunc)(p0, p1);
		}

		template <typename T0, typename T1, typename T2>
		inline RetType operator()(T0 p0, T1 p1, T2 p2)
		{
			return (*mFunc)(p0, p1, p2);
		}

	private:
		std::auto_ptr<TIFunction<RetType, TypeList> > mFunc;
};