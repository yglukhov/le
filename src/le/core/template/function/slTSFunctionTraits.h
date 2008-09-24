#pragma once

#include <le/core/config/slPrefix.h>

namespace sokira
{
	namespace le
	{

template <typename FuncType> struct TSFunctionTraits;

	} // namespace le
} // namespace sokira

#include "base/slTSFunctionCallWithTuple.h"
#include "base/slTSFreeFunctionTraits.h"
#include "base/slTSMemberFunctionTraits.h"

namespace sokira
{
	namespace le
	{

template <typename RetType, class TypeList> class TCFunction;
template <typename FunctionType, class RealTypeList> class TCBind;

template <typename TRetType, class TypeList>
struct TSFunctionTraits<TCFunction<TRetType, TypeList> > :
	public TSFreeFunctionCallWithTuple<TRetType, TypeList::length>
{
	typedef TRetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

template <typename FuncType, class TypeList>
struct TSFunctionTraits<TCBind<FuncType, TypeList> > :
	public TSFreeFunctionCallWithTuple<
		typename TSFunctionTraits<FuncType>::RetType,
		TypeList::length>
{
	typedef typename TSFunctionTraits<FuncType>::RetType RetType;
	typedef TypeList ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
};

	} // namespace le
} // namespace sokira
