#pragma once

//#include <le/core/preprocessor/slPPrepeat_from_0.h>
//#include "slTSFunctionTraits.h"
#include "slTCVariadicFunction.h"
#include "base/slTSBind.h"

namespace sokira
{
	namespace le
	{

#define bindTo(bindToIndex) bindTo<(bindToIndex)>()


////////////////////////////////////////////////////////////////////////////////
// TCBind class declaration.
template <typename FunctionType, class RealTypeList>
class TCBind : public TCVariadicFunctionMixin<
							TCBind<FunctionType, RealTypeList>,
							TSVariadicFunctionConstantResult<typename TSFunctionTraits<FunctionType>::RetType>::template TResult,
							true>
{
	typedef TSFunctionTraits<FunctionType> TraitsType;
	typedef typename TraitsType::TupleParamList FuncParamList;
	typedef typename TraitsType::RetType RetType;
	typedef TCTuple<RealTypeList> TupleType;

public:
	using TCVariadicFunctionMixin<
		TCBind<FunctionType, RealTypeList>,
		TSVariadicFunctionConstantResult<RetType>::template TResult,
		true
		>::operator();

	inline TCBind(FunctionType func) : mFunction(func)
	{

	}

	template <class TTypeList>
	inline RetType operator()(const TCTuple<TTypeList>& paramTuple) const
	{
		TCTuple<FuncParamList> tuple;
		copyFromParamToFuncTuple<0>(paramTuple, tuple);
		return TraitsType::callWithTuple(mFunction, tuple);
	}

	inline RetType operator()() const
	{
		return TraitsType::callWithTuple(mFunction, mTuple);
	}

	inline CFunctionDescriptor functionDescriptor() const
	{
		return CFunctionDescriptor(mFunction);
	}

private:
	template <unsigned index /* should be 0 */, class TParamTypeList>
	inline void copyFromParamToFuncTuple(const TCTuple<TParamTypeList>& paramTuple,
													 TCTuple<FuncParamList>& funcTuple) const
	{
		_copyFromParamToFuncTuple<index>(paramTuple, funcTuple,
										TSBoolToType<(index < FuncParamList::length)>());
	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(const TCTuple<TParamTypeList>& /*paramTuple*/,
													  TCTuple<FuncParamList>& /*funcTuple*/,
													  TSBoolToType<false> /* inBands */) const
	{

	}

	template <unsigned index, class TParamTypeList>
	inline void _copyFromParamToFuncTuple(const TCTuple<TParamTypeList>& paramTuple,
													  TCTuple<FuncParamList>& funcTuple,
													  TSBoolToType<true> /* inBands */) const
	{
		typedef TSParamTraits<typename RealTypeList::template TypeAt<index>::result> Traits;
		funcTuple.template setValue<index>(paramForIndex<index, Traits::bind, TParamTypeList>(
											paramTuple, TSBoolToType<Traits::bind != -1>()));

		copyFromParamToFuncTuple<index + 1>(paramTuple, funcTuple);
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline typename TSConstRef<typename FuncParamList::template TypeAt<index>::result>::result
		paramForIndex(const TCTuple<TParamTypeList>& /*paramTuple*/, TSBoolToType<false> /* isBinded */) const
	{
		return mTuple.template value<index>();
	}

	template <unsigned index, int bindIndex, class TParamTypeList>
	inline typename TSConstRef<typename FuncParamList::template TypeAt<index>::result>::result
		paramForIndex(const TCTuple<TParamTypeList>& paramTuple, TSBoolToType<true> /* isBinded */) const
	{
		return paramTuple.template value<bindIndex>();
	}

	FunctionType mFunction;

	public:
		TupleType mTuple;
};

struct TCBindConstructor
{
	template <class TTypeList>
	struct TResult
	{
		typedef TCBind<typename TTypeList::Front, typename TTypeList::PopFront> result;
	};

	template <class TTypeList>
	typename TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple)
	{
		typename TResult<TTypeList>::result result(tuple.template value<0>());
		SCollector<TTypeList, 1, 1 == TTypeList::length>::fillBindWithTupleValues(result, tuple);
		return result;
	}

	private:
		template <class TTypeList, UInt32 i, bool end>
		struct SCollector
		{
			template <class TBind>
			static inline void fillBindWithTupleValues(TBind& theBind, const TCTuple<TTypeList>& tuple)
			{
				theBind.mTuple.template setValue<i - 1>(tuple.template value<i>());
				SCollector<TTypeList, i + 1, i + 1 == TTypeList::length>::fillBindWithTupleValues(theBind, tuple);
			}
		};

		template <class TTypeList, UInt32 i>
		struct SCollector<TTypeList, i, true>
		{
			template <class TBind>
			static inline void fillBindWithTupleValues(TBind& vector, const TCTuple<TTypeList>& tuple) { }
		};
};

static TCVariadicFunction<TCBindConstructor> bind;

	} // namespace le
} // namespace sokira
