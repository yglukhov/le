#pragma once


namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// Free function traits
////////////////////////////////////////////////////////////////////////////////
template <typename TRetType>
struct TSFunctionTraits<TRetType()> :
	public TSFreeFunctionCallWithTuple<TRetType, 0>
{
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
	typedef TSFalse IsConst;
};

#define _le_typenameT(x) ,typename T##x
#define _le_rawT(x) ,T##x

#define _LE_DEFINE_TSFunctionTraits(x) \
template <typename TRetType, typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT)>  \
struct TSFunctionTraits<TRetType(T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT))> :	\
	public TSFreeFunctionCallWithTuple<TRetType, x + 1>								\
{																					\
	typedef TRetType RetType;														\
	typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT)> ParamList;		\
	typedef _SNullType OwnerClass;													\
	typedef ParamList TupleParamList;												\
	typedef TSFalse IsConst;														\
};

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

////////////////////////////////////////////////////////////////////////////////
// Free function pointer traits
////////////////////////////////////////////////////////////////////////////////
template <typename TRetType>
struct TSFunctionTraits<TRetType(*)()> :
	public TSFreeFunctionCallWithTuple<TRetType, 0>
{
	typedef TRetType RetType;
	typedef TSTypeList<> ParamList;
	typedef _SNullType OwnerClass;
	typedef ParamList TupleParamList;
	typedef TSFalse IsConst;
};


#define _LE_DEFINE_TSFunctionTraits(x) \
template <typename TRetType, typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT)> \
struct TSFunctionTraits<TRetType(*)(T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT))> : \
	public TSFreeFunctionCallWithTuple<TRetType, x + 1> \
{ \
	typedef TRetType RetType; \
	typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT)> ParamList; \
	typedef _SNullType OwnerClass; \
	typedef ParamList TupleParamList; \
	typedef TSFalse IsConst; \
};

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
