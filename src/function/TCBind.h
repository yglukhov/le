#pragma once

#include "TSFunction.h"
#include "base/TSBind.h"

#define bindTo(bindToIndex) TSBindToIndexedParam<(bindToIndex)>()


////////////////////////////////////////////////////////////////////////////////
// Functor
template <typename RetType, class FuncParamList, class RealTypeList>
class TCBind
{
	typedef TSFunction<RetType, FuncParamList> TSFuncType;
	typedef typename TSFuncType::function FunctionType;
	typedef TCTuple<RealTypeList> TupleType;

public:
	TCBind(FunctionType func) : mFunction(func)
	{

	}

	RetType operator()()
	{
		return TSFuncType::callWithTuple(mFunction, mTuple);
	}

	template <typename T0>
	RetType operator()(T0 p0)
	{
		TCTuple<TSTypeList<T0> > paramTuple;
		paramTuple.template value<0>() = p0;

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TSFuncType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1>
	RetType operator()(T0 p0, T1 p1)
	{
		TCTuple<TSTypeList<T0, T1> > paramTuple;
		paramTuple.template value<0>() = p0;
		paramTuple.template value<1>() = p1;

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TSFuncType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1, typename T2>
	RetType operator()(T0 p0, T1 p1, T2 p2)
	{
		TCTuple<TSTypeList<T0, T1, T2> > paramTuple;
		paramTuple.template value<0>() = p0;
		paramTuple.template value<1>() = p1;
		paramTuple.template value<2>() = p2;

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TSFuncType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1, typename T2, typename T3>
	RetType operator()(T0 p0, T1 p1, T2 p2, T3 p3)
	{
		TCTuple<TSTypeList<T0, T1, T2, T3> > paramTuple;
		paramTuple.template value<0>() = p0;
		paramTuple.template value<1>() = p1;
		paramTuple.template value<2>() = p2;
		paramTuple.template value<3>() = p3;

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TSFuncType::callWithTuple(mFunction, tuple);
	}

private:
	template <unsigned index /* should be 0 */, class TParamTypeList>
	inline void copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
													 TCTuple<FuncParamList>& funcTuple)
	{
		_copyFromParamToFuncTuple<index, TParamTypeList>(paramTuple, funcTuple,
														Bool2Type<(index < FuncParamList::length)>());
	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
													  TCTuple<FuncParamList>& funcTuple,
													  Bool2Type<false> /* inBands */)
	{

	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
													  TCTuple<FuncParamList>& funcTuple,
													  Bool2Type<true> /* inBands */)
	{
		typedef TSParamTraits<typename RealTypeList::TypeAt<index>::result> Traits;
		__copyFromParamToFuncTuple<index, Traits::bind, TParamTypeList>(paramTuple, funcTuple,
															Bool2Type<Traits::bind == -1>());
		copyFromParamToFuncTuple<index + 1, TParamTypeList>(paramTuple, funcTuple);
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline void __copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
														TCTuple<FuncParamList>& funcTuple,
														Bool2Type<true> /* notBinded */)
	{
		funcTuple.template value<index>() = mTuple.template value<index>();
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline void __copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
														TCTuple<FuncParamList>& funcTuple,
														Bool2Type<false> /* notBinded */)
	{
		funcTuple.template value<index>() = paramTuple.template value<bindIndex>();
	}

	FunctionType mFunction;

	public:
		TupleType mTuple;
};

template <typename RetType>
TCBind<RetType, TSTypeList<>, TSTypeList<> > bind(RetType(*func)())
{
	return TCBind<RetType, TSTypeList<>, TSTypeList<> >(func);
}

template <typename RetType, typename T0, typename B0>
TCBind<RetType, TSTypeList<T0>, TSTypeList<B0> > bind(RetType(*func)(T0), B0 b0)
{
	TCBind<RetType, TSTypeList<T0>, TSTypeList<B0> > result(func);
	result.mTuple.template value<0>() = b0;
	return result;
}

template <typename RetType, typename T0, typename T1, typename B0, typename B1>
TCBind<RetType, TSTypeList<T0, T1>, TSTypeList<B0, B1> > bind(RetType(*func)(T0, T1), B0 b0, B1 b1)
{
	TCBind<RetType, TSTypeList<T0, T1>, TSTypeList<B0, B1> > result(func);
	result.mTuple.template value<0>() = b0;
	result.mTuple.template value<1>() = b1;
	return result;
}

