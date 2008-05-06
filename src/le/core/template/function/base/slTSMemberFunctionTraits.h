#pragma once

#include <le/core/config/slPrefix.h>

namespace sokira
{
	namespace le
	{

template <class T, typename TRetType>
struct TSFunctionTraits<TRetType (T::*)()> :
	public TSMemberFunctionCallWithTuple<T, TRetType, 0>
{
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef T OwnerClass;
	typedef typename ParamList::template PushFront<OwnerClass*> TupleParamList;
};

template <class T, typename TRetType, typename T0>
struct TSFunctionTraits<TRetType (T::*)(T0)> :
	public TSMemberFunctionCallWithTuple<T, TRetType, 1>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0> ParamList;
	typedef T OwnerClass;
	typedef typename ParamList::template PushFront<OwnerClass*> TupleParamList;
};

template <class T, typename TRetType, typename T0, typename T1>
struct TSFunctionTraits<TRetType (T::*)(T0, T1)> :
	public TSMemberFunctionCallWithTuple<T, TRetType, 2>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0, T1> ParamList;
	typedef T OwnerClass;
	typedef typename ParamList::template PushFront<OwnerClass*> TupleParamList;
};

	} // namespace le
} // namespace sokira
