#pragma once

template <typename FuncType> struct TSFunctionTraits;

#include "base/TSFunctionCallWithTuple.h"
#include "base/TSFreeFunctionTraits.h"
#include "base/TSFreeFunctionPointerTraits.h"
#include "base/TSMemberFunctionTraits.h"

template <typename RetType, class TypeList> class TCFunction;
template <typename FunctionType, class RealTypeList> class TCBind;

template <typename TRetType, class TypeList>
struct TSFunctionTraits<TCFunction<TRetType, TypeList> > :
	public TSFunctionCallWithTuple<TRetType, TypeList::length>
{
	typedef TRetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
};

template <typename FuncType, class TypeList>
struct TSFunctionTraits<TCBind<FuncType, TypeList> > :
	public TSFunctionCallWithTuple<
		typename TSFunctionTraits<FuncType>::RetType,
		TypeList::length>
{
	typedef typename TSFunctionTraits<FuncType>::RetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
};