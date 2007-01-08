#pragma once

#include <common/config/slPrefix.h>
#include "slTSFunctionTraits.h"
#include "base/slTSBind.h"
//#include <util/slCompareTypes.h>

namespace sokira
{
	namespace le
	{

#define bindTo(bindToIndex) TSBindToIndexedParam<(bindToIndex)>()


////////////////////////////////////////////////////////////////////////////////
// TCBind class declaration.
template <typename FunctionType, class RealTypeList>
class TCBind
{
	typedef TSFunctionTraits<FunctionType> TraitsType;
	typedef typename TraitsType::TupleParamList FuncParamList;
	typedef typename TraitsType::RetType RetType;
	typedef TCTuple<RealTypeList> TupleType;

public:
	inline TCBind(FunctionType func) : mFunction(func)
	{

	}

	inline RetType operator()() const
	{
		return TraitsType::callWithTuple(mFunction, mTuple);
	}

	template <typename T0>
	RetType operator()(T0 p0) const
	{
		TCTuple<TSTypeList<T0> > paramTuple;
		paramTuple.template value<0>(p0);

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TraitsType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1>
	RetType operator()(T0 p0, T1 p1) const
	{
		TCTuple<TSTypeList<T0, T1> > paramTuple;
		paramTuple.template value<0>(p0);
		paramTuple.template value<1>(p1);

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TraitsType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1, typename T2>
	RetType operator()(T0 p0, T1 p1, T2 p2) const
	{
		TCTuple<TSTypeList<T0, T1, T2> > paramTuple;
		paramTuple.template value<0>(p0);
		paramTuple.template value<1>(p1);
		paramTuple.template value<2>(p2);

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TraitsType::callWithTuple(mFunction, tuple);
	}

	template <typename T0, typename T1, typename T2, typename T3>
	RetType operator()(T0 p0, T1 p1, T2 p2, T3 p3)
	{
		TCTuple<TSTypeList<T0, T1, T2, T3> > paramTuple;
		paramTuple.template value<0>(p0);
		paramTuple.template value<1>(p1);
		paramTuple.template value<2>(p2);
		paramTuple.template value<3>(p3);

		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);

		return TraitsType::callWithTuple(mFunction, tuple);
	}

private:
	template <unsigned index /* should be 0 */, class TParamTypeList>
	inline void copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
													 TCTuple<FuncParamList>& funcTuple) const
	{
		_copyFromParamToFuncTuple<index>(paramTuple, funcTuple,
										TSBoolToType<(index < FuncParamList::length)>());
	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(TCTuple<TParamTypeList>& /*paramTuple*/,
													  TCTuple<FuncParamList>& /*funcTuple*/,
													  TSBoolToType<false> /* inBands */) const
	{

	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(TCTuple<TParamTypeList>& paramTuple,
													  TCTuple<FuncParamList>& funcTuple,
													  TSBoolToType<true> /* inBands */) const
	{
		typedef TSParamTraits<typename RealTypeList::template TypeAt<index>::result> Traits;
		funcTuple.template value<index>(paramForIndex<index, Traits::bind, TParamTypeList>(
											paramTuple, TSBoolToType<Traits::bind != -1>()));

		copyFromParamToFuncTuple<index + 1>(paramTuple, funcTuple);
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline typename TSConstRef<typename FuncParamList::template TypeAt<index>::result>::result
		paramForIndex(TCTuple<TParamTypeList>& /*paramTuple*/, TSBoolToType<false> /* isBinded */) const
	{
		return mTuple.template value<index>();
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline typename TSConstRef<typename FuncParamList::template TypeAt<index>::result>::result
		paramForIndex(TCTuple<TParamTypeList>& paramTuple, TSBoolToType<true> /* isBinded */) const
	{
		return paramTuple.template value<bindIndex>();
	}

	FunctionType mFunction;

	public:
		TupleType mTuple;
};

template <typename FunctionType>
TCBind<FunctionType, TSTypeList<> > bind(FunctionType func)
{
	return TCBind<FunctionType, TSTypeList<> >(func);
}

template <typename FunctionType, typename B0>
TCBind<FunctionType, TSTypeList<B0> > bind(FunctionType func, B0 b0)
{
	TCBind<FunctionType, TSTypeList<B0> > result(func);
	result.mTuple.template value<0>(b0);
	return result;
}

template <typename FunctionType, typename B0, typename B1>
TCBind<FunctionType, TSTypeList<B0, B1> > bind(FunctionType func, B0 b0, B1 b1)
{
	TCBind<FunctionType, TSTypeList<B0, B1> > result(func);
	result.mTuple.template value<0>(b0);
	result.mTuple.template value<1>(b1);
	return result;
}

template <typename FunctionType, typename B0, typename B1, typename B2>
TCBind<FunctionType, TSTypeList<B0, B1, B2> > bind(FunctionType func, B0 b0, B1 b1, B2 b2)
{
	TCBind<FunctionType, TSTypeList<B0, B1, B2> > result(func);
	result.mTuple.template value<0>(b0);
	result.mTuple.template value<1>(b1);
	result.mTuple.template value<2>(b2);
	return result;
}


	} // namespace le
} // namespace sokira
