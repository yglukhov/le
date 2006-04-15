#pragma once

LE_NAMESPACE_START

template <typename FuncType> struct TSFunctionTraits;

LE_NAMESPACE_END

#include <config/slPrefix.h>
#include "base/slTSFunctionCallWithTuple.h"
#include "base/slTSFreeFunctionTraits.h"
#include "base/slTSFreeFunctionPointerTraits.h"
#include "base/slTSMemberFunctionTraits.h"

LE_NAMESPACE_START

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

LE_NAMESPACE_END
