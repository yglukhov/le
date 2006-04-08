#pragma once

template <typename FuncType> struct TSFunctionTraits;

#include "base/TSFunctionCallWithTuple.h"
#include "base/TSFreeFunctionTraits.h"
#include "base/TSFreeFunctionPointerTraits.h"
#include "base/TSMemberFunctionTraits.h"

template <typename TRetType, class TypeList>
struct TSFunctionTraits<TCFunction<TRetType, TypeList> > :
	public TSFunctionCallWithTuple<TRetType, TypeList::length>
{
	typedef TRetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
};
