#pragma once

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include "slTSFunctionTraits.h"
#include "base/slTSBind.h"

namespace sokira
{
	namespace le
	{

#define bindTo(bindToIndex) bindTo<(bindToIndex)>()


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

#define _le_typenameT(x) ,typename T##x
#define _le_paramT(x) ,T##x p##x
#define _le_rawT(x) ,T##x
#define _le_setP(x) paramTuple.template setValue<x>(p##x);


#define _LE_DEFINE_TCBind_operator(x)													\
	template <typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT)>					\
	RetType operator()(T0 p0 LE_PP_REPETITION_FROM_0_TO(x, _le_paramT)) const			\
	{																					\
		TCTuple<TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT)> > paramTuple;	\
		paramTuple.template setValue<0>(p0);											\
		LE_PP_REPETITION_FROM_0_TO(x, _le_setP)											\
																						\
		TCTuple<FuncParamList> tuple;													\
		copyFromParamToFuncTuple<0>(paramTuple, tuple);									\
																						\
		return TraitsType::callWithTuple(mFunction, tuple);								\
	}

	_LE_DEFINE_TCBind_operator(0)
	_LE_DEFINE_TCBind_operator(1)
	_LE_DEFINE_TCBind_operator(2)
	_LE_DEFINE_TCBind_operator(3)
	_LE_DEFINE_TCBind_operator(4)
	_LE_DEFINE_TCBind_operator(5)
	_LE_DEFINE_TCBind_operator(6)
	_LE_DEFINE_TCBind_operator(7)
	_LE_DEFINE_TCBind_operator(8)
	_LE_DEFINE_TCBind_operator(9)

#undef _LE_DEFINE_TCBind_operator
#undef _le_typenameT
#undef _le_paramT
#undef _le_rawT
#undef _le_setP

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
		funcTuple.template setValue<index>(paramForIndex<index, Traits::bind, TParamTypeList>(
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

#define _le_typenameB(x) ,typename B##x
#define _le_rawB(x) ,B##x
#define _le_paramB(x) ,B##x b##x
#define _le_tupleB(x) result.mTuple.template setValue<x>(b##x);

#define _LE_DEFINE_bind(x)																		\
template <typename FunctionType, typename B0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameB)>		\
TCBind<FunctionType, TSTypeList<B0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawB)> >					\
	bind(FunctionType func, B0 b0 LE_PP_REPETITION_FROM_0_TO(x, _le_paramB))					\
{																								\
	TCBind<FunctionType, TSTypeList<B0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawB)> > result(func); \
	result.mTuple.template setValue<0>(b0);														\
	LE_PP_REPETITION_FROM_0_TO(x, _le_tupleB)													\
	return result;																				\
}


_LE_DEFINE_bind(0)
_LE_DEFINE_bind(1)
_LE_DEFINE_bind(2)
_LE_DEFINE_bind(3)
_LE_DEFINE_bind(4)
_LE_DEFINE_bind(5)
_LE_DEFINE_bind(6)
_LE_DEFINE_bind(7)
_LE_DEFINE_bind(8)
_LE_DEFINE_bind(9)
_LE_DEFINE_bind(10)
_LE_DEFINE_bind(11)
_LE_DEFINE_bind(12)


#undef _LE_DEFINE_TCBind
#undef _le_typenameB
#undef _le_rawB
#undef _le_paramB
#undef _le_tupleB


	} // namespace le
} // namespace sokira
