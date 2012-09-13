#if !defined SL_LE_core_template_function_slTCVariadicFunction_h
#define SL_LE_core_template_function_slTCVariadicFunction_h

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include "slTSFunctionTraits.h"

namespace sokira
{
	namespace le
	{

template <class TFunction, class TContainer>
struct TSVariadicToAnyPacker : public TFunction
{
	template <class TTypeList>
	typename TFunction::template TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple)
	{
		TContainer arguments;
		arguments.reserve(TTypeList::length);
		SCollector<TTypeList, 0, 0 == TTypeList::length>::fillVectorWithTupleValues(arguments, tuple);
		return TFunction::operator()(arguments);
	}

private:
	template <class TTypeList, UInt32 i, bool end>
	struct SCollector
	{
		static inline void fillVectorWithTupleValues(TContainer& vector, const TCTuple<TTypeList>& tuple)
		{
#if 0
			vector.push_back(typename TContainer::value_type(tuple.template value<i>()));
#else
			std::cout << "Creating Any is ref : " << TSIsRef<typename TTypeList::template TypeAt<i>::result>::value << std::endl;
			vector.push_back(typename TContainer::value_type((typename TTypeList::template TypeAt<i>::result)tuple.template value<i>()));
#endif
			SCollector<TTypeList, i + 1, i + 1 == TTypeList::length>::fillVectorWithTupleValues(vector, tuple);
		}
	};

	template <class TTypeList, UInt32 i>
	struct SCollector<TTypeList, i, true>
	{
		static inline void fillVectorWithTupleValues(TContainer& vector, const TCTuple<TTypeList>& tuple) { }
	};
};

template <typename T>
struct TSVariadicFunctionConstantResult
{
	template <class TAnyTypeList>
	struct TResult
	{
		typedef T result;
	};
};

template <class TFunction, template <class TTypeList> class TResult,
			UInt32 argCount, bool isConst = false>
class TCFunctionInterfaceMixin;

template <class TFunction, template <class TTypeList> class TResult>
class TCFunctionInterfaceMixin<TFunction, TResult, 0, false>
{
public:
	typename TResult<TSTypeList<> >::result operator()()
	{
		return ((TFunction*)this)->operator()(TCTuple<TSTypeList<> >());
	}
};

template <class TFunction, template <class TTypeList> class TResult>
class TCFunctionInterfaceMixin<TFunction, TResult, 0, true>
{
public:
	typename TResult<TSTypeList<> >::result operator()() const
	{
		return ((const TFunction*)this)->operator()(TCTuple<TSTypeList<> >());
	}
};

#define _le_typenameT(x) ,typename T##x
#define _le_rawT(x) ,T##x
#define _le_paramT(x) ,T##x a##x
#define _le_tupleT(x) t.template setValue<x>(a##x);
#define _le_const
#define _le_const_flag false

#define _LE_DEFINE_variadic_function_operator(x) \
template <class TFunction, template <class TTypeList> class TResult> \
class TCFunctionInterfaceMixin<TFunction, TResult, x + 1, _le_const_flag> \
{ \
public: \
	template<typename T0 LE_PP_REPETITION_FROM_0_TO(x, _le_typenameT) > \
	typename TResult<TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT) > >::result operator()(T0 a0 LE_PP_REPETITION_FROM_0_TO(x, _le_paramT)) _le_const \
	{ \
		typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(x, _le_rawT) > TypeList; \
		TCTuple<TypeList> t; \
		t.template setValue<0>(a0); \
		LE_PP_REPETITION_FROM_0_TO(x, _le_tupleT) \
		return ((_le_const TFunction*)this)->operator()(t); \
	} \
};

#define _LE_DEFINE_variadic_function_operators()	\
	_LE_DEFINE_variadic_function_operator(0)		\
	_LE_DEFINE_variadic_function_operator(1)		\
	_LE_DEFINE_variadic_function_operator(2)		\
	_LE_DEFINE_variadic_function_operator(3)		\
	_LE_DEFINE_variadic_function_operator(4)		\
	_LE_DEFINE_variadic_function_operator(5)		\
	_LE_DEFINE_variadic_function_operator(6)		\
	_LE_DEFINE_variadic_function_operator(7)		\
	_LE_DEFINE_variadic_function_operator(8)		\
	_LE_DEFINE_variadic_function_operator(9)		\
	_LE_DEFINE_variadic_function_operator(10)		\
	_LE_DEFINE_variadic_function_operator(11)		\
	_LE_DEFINE_variadic_function_operator(12)

_LE_DEFINE_variadic_function_operators()

#undef _le_const
#define _le_const const
#undef _le_const_flag
#define _le_const_flag true
_LE_DEFINE_variadic_function_operators()
#undef _LE_DEFINE_variadic_function_operator
#undef _le_typenameT
#undef _le_rawT
#undef _le_paramT
#undef _le_tupleT
#undef _le_const


template <class TFunction, template <class TTypeList> class TResult, bool isConst = false, int maxArgs = 12>
class TCVariadicFunctionMixin : public TCFunctionInterfaceMixin<TFunction, TResult, maxArgs, isConst>,
			public TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs - 1>
{
	public:
		typedef TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs> TVariadic;
		using TCFunctionInterfaceMixin<TFunction, TResult, maxArgs, isConst>::operator();
		using TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs - 1>::operator();
};

template <class TFunction, template <class TTypeList> class TResult, bool isConst>
class TCVariadicFunctionMixin<TFunction, TResult, isConst, 0> :
		public TCFunctionInterfaceMixin<TFunction, TResult, 0, isConst>
{
	public:
		using TCFunctionInterfaceMixin<TFunction, TResult, 0, isConst>::operator();
};

template <class TFunction, bool isConst = false>
class TCVariadicFunction :
	public TFunction,
	public TCVariadicFunctionMixin<TCVariadicFunction<TFunction>, TFunction::template TResult, isConst>
{
public:
	using TCVariadicFunctionMixin<TCVariadicFunction<TFunction>, TFunction::template TResult>::operator();
	template <class TTypeList>
	typename TFunction::template TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple)
	{
		return TFunction::operator()(tuple);
	}
};

template <class TFunction>
class TCVariadicFunction<TFunction, true> :
	public TFunction,
	public TCVariadicFunctionMixin<TCVariadicFunction<TFunction>, TFunction::template TResult, true>
{
public:
	using TCVariadicFunctionMixin<TCVariadicFunction<TFunction>, TFunction::template TResult, true>::operator();
	template <class TTypeList>
	typename TFunction::template TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple) const
	{
		return TFunction::operator()(tuple);
	}
};


template <class TFunction, class TContainer>
class TCAnyVariadicFunction : public TCVariadicFunction<TSVariadicToAnyPacker<TFunction, TContainer> > { };

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_function_slTCVariadicFunction_h
