#pragma once


namespace sokira
{
	namespace le
	{

template <class T, typename TRetType>
struct TSFunctionTraits<TRetType (T::*)()> :
	public TSMemberFunctionCallWithTuple<TRetType, 0>
{
	typedef TSTrue IsFunction;
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef T OwnerClass;
	typedef typename ParamList::template PushFront<OwnerClass*>::result TupleParamList;
	typedef TSFalse IsConst;
};

template <class T, typename TRetType>
struct TSFunctionTraits<TRetType (T::*)() const> :
public TSMemberFunctionCallWithTuple<TRetType, 0>
{
	typedef TSTrue IsFunction;
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef T OwnerClass;
	typedef typename ParamList::template PushFront<OwnerClass*>::result TupleParamList;
	typedef TSTrue IsConst;
};

#define _le_typenameT(x) ,typename T##x
#define _le_rawT(x) ,T##x

#define _LE_DEFINE_TSFunctionTraitsWithConst(x, CONST, TIsConst)								\
template <class T, typename TRetType, typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT)> \
struct TSFunctionTraits<TRetType (T::*)(T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT)) CONST> :	\
	public TSMemberFunctionCallWithTuple<TRetType, x + 1>										\
{																								\
	typedef TSTrue IsFunction;																	\
	typedef TRetType RetType;																	\
	typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT)> ParamList;					\
	typedef CONST T OwnerClass;																	\
	typedef typename ParamList::template PushFront<OwnerClass*>::result TupleParamList;			\
	typedef TIsConst IsConst;																	\
};

#define _LE_NOTHING
#define _LE_DEFINE_TSFunctionTraits(x) _LE_DEFINE_TSFunctionTraitsWithConst(x, _LE_NOTHING, TSFalse) _LE_DEFINE_TSFunctionTraitsWithConst(x, const, TSTrue)

_LE_DEFINE_TSFunctionTraits(0)
_LE_DEFINE_TSFunctionTraits(1)
_LE_DEFINE_TSFunctionTraits(2)
_LE_DEFINE_TSFunctionTraits(3)
_LE_DEFINE_TSFunctionTraits(4)
_LE_DEFINE_TSFunctionTraits(5)
_LE_DEFINE_TSFunctionTraits(6)
_LE_DEFINE_TSFunctionTraits(7)
_LE_DEFINE_TSFunctionTraits(8)
_LE_DEFINE_TSFunctionTraits(9)
_LE_DEFINE_TSFunctionTraits(10)
_LE_DEFINE_TSFunctionTraits(11)
_LE_DEFINE_TSFunctionTraits(12)

#undef _LE_DEFINE_TSFunctionTraits
#undef _le_typenameT
#undef _le_rawT

	} // namespace le
} // namespace sokira
