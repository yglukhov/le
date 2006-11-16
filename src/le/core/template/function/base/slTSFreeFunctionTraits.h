#pragma once

#include <common/config/slPrefix.h>
LE_NAMESPACE_START

template <typename TRetType>
struct TSFunctionTraits<TRetType()> :
	public TSFreeFunctionCallWithTuple<TRetType, 0>
{
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

template <typename TRetType, typename T0>
struct TSFunctionTraits<TRetType(T0)> :
	public TSFreeFunctionCallWithTuple<TRetType, 1>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

template <typename TRetType, typename T0, typename T1>
struct TSFunctionTraits<TRetType(T0, T1)> :
	public TSFreeFunctionCallWithTuple<TRetType, 2>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0, T1> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

template <typename TRetType, typename T0, typename T1, typename T2>
struct TSFunctionTraits<TRetType(T0, T1, T2)> :
	public TSFreeFunctionCallWithTuple<TRetType, 3>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0, T1, T2> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};


LE_NAMESPACE_END
