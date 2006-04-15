#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

template <typename TRetType>
struct TSFunctionTraits<TRetType(*)()> :
	public TSFunctionCallWithTuple<TRetType, 0>
{
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef _SNullType OwnerClass;
};

template <typename TRetType, typename T0>
struct TSFunctionTraits<TRetType(*)(T0)> :
	public TSFunctionCallWithTuple<TRetType, 1>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0> ParamList;
	typedef _SNullType OwnerClass;
};

template <typename TRetType, typename T0, typename T1>
struct TSFunctionTraits<TRetType(*)(T0, T1)> :
	public TSFunctionCallWithTuple<TRetType, 2>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0, T1> ParamList;
	typedef _SNullType OwnerClass;
};

template <typename TRetType, typename T0, typename T1, typename T2>
struct TSFunctionTraits<TRetType(*)(T0, T1, T2)> :
	public TSFunctionCallWithTuple<TRetType, 3>
{
	typedef TRetType RetType;
	typedef TSTypeList<T0, T1, T2> ParamList;
	typedef _SNullType OwnerClass;
};


LE_NAMESPACE_END
