#if !defined SL_LE_core_template_function_slTCVariadicFunction_h
#define SL_LE_core_template_function_slTCVariadicFunction_h

#include <le/core/preprocessor/slPPrepeat_from_0.h>
#include <le/core/template/tuple/slTCTuple.h>
#include "slTSFunctionTraits.h"

namespace sokira
{
	namespace le
	{

template <class TTypeList, UInt32 i = 0, bool end = (0 == TTypeList::length)>
struct TSTupleToContainerCollector
{
	template <class TContainer>
	static inline void fillContainerWithTupleValues(TContainer& vector, const TCTuple<TTypeList>& tuple)
	{
		vector.push_back(typename TContainer::value_type(tuple.template value<i>()));
		TSTupleToContainerCollector<TTypeList, i + 1, i + 1 == TTypeList::length>::fillContainerWithTupleValues(vector, tuple);
	}
};

template <class TTypeList, UInt32 i>
struct TSTupleToContainerCollector<TTypeList, i, true>
{
	template <class TContainer>
	static inline void fillContainerWithTupleValues(TContainer& vector, const TCTuple<TTypeList>& tuple) { }
};


template <class TFunction, class TContainer>
struct TSVariadicToAnyPacker : public TFunction
{
	template <class TTypeList>
	typename TFunction::template TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple)
	{
		TContainer arguments;
		arguments.reserve(TTypeList::length);
		TSTupleToContainerCollector<TTypeList>::fillContainerWithTupleValues(arguments, tuple);
		return TFunction::operator()(arguments);
	}
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
			UInt32 argCount, bool isConst = false, class ConcreteTypeList = TSTypeList<> >
class TCVariadicFunctionInterfaceMixin;

template <class TFunction, template <class TTypeList> class TResult>
class TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0, false>
{
public:
	typename TResult<TSTypeList<> >::result operator()()
	{
		return ((TFunction*)this)->operator()(TCTuple<TSTypeList<> >());
	}
};

template <class TFunction, template <class TTypeList> class TResult>
class TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0, true>
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
template <class TFunction, template <class TTypeList> class TResult, class ConcreteTypeList> \
class TCVariadicFunctionInterfaceMixin<TFunction, TResult, x + 1, _le_const_flag, ConcreteTypeList> \
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

//		template <class TFunction, template <class TTypeList> class TResult> 
//		class TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0 + 1, _le_const_flag>
//		{ 
//		public: 
//			template<typename T0 LE_PP_REPETITION_FROM_0_TO(0, _le_typenameT) >
//			typename TResult<TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(0, _le_rawT) > >::result operator()(T0 a0 LE_PP_REPETITION_FROM_0_TO(0, _le_paramT)) _le_const
//			{ 
//				typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(0, _le_rawT) > TypeList;
//				TCTuple<TypeList> t;
//				std::cout << "IN MIXIN: " << &a0 << " : isRef : " << TSIsRef<T0>::value << std::endl;
//				t.template setValue<0>(a0);
//				LE_PP_REPETITION_FROM_0_TO(0, _le_tupleT)
//				return ((_le_const TFunction*)this)->operator()(t); 
//			} 
//		};


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
				
//				template <class TFunction, template <class TTypeList> class TResult>
//				class TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0 + 1, _le_const_flag>
//				{
//				public:
//					template<typename T0 LE_PP_REPETITION_FROM_0_TO(0, _le_typenameT) >
//					typename TResult<TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(0, _le_rawT) > >::result operator()(T0 a0 LE_PP_REPETITION_FROM_0_TO(0, _le_paramT)) _le_const
//					{
//						typedef TSTypeList<T0 LE_PP_REPETITION_FROM_0_TO(0, _le_rawT) > TypeList;
//						TCTuple<TypeList> t;
//						std::cout << "IN CONST MIXIN: " << &a0 << std::endl;
//						t.template setValue<0>(a0);
//						LE_PP_REPETITION_FROM_0_TO(0, _le_tupleT)
//						return ((_le_const TFunction*)this)->operator()(t);
//					} 
//				};

#undef _LE_DEFINE_variadic_function_operator
#undef _le_typenameT
#undef _le_rawT
#undef _le_paramT
#undef _le_tupleT
#undef _le_const
#undef _le_const_flag


template <class TFunction, typename TResult, class ConcreteTypeList = TSTypeList<>, bool isConst = false, UInt32 argCount = ConcreteTypeList::length>
class TCConcreteFunctionInterfaceMixin;

template <class TFunction, typename TResult, class ConcreteTypeList>
class TCConcreteFunctionInterfaceMixin<TFunction, TResult, ConcreteTypeList, false, 0>
{
public:
	TResult operator()()
	{
		return ((TFunction*)this)->operator()(TCTuple<ConcreteTypeList>());
	}
};

template <class TFunction, typename TResult, class ConcreteTypeList>
class TCConcreteFunctionInterfaceMixin<TFunction, TResult, ConcreteTypeList, true, 0>
{
public:
	TResult operator()() const
	{
		return ((const TFunction*)this)->operator()(TCTuple<ConcreteTypeList>());
	}
};

#define _le_typenameT(x) ,typename T##x
#define _le_paramT(x) ,typename ConcreteTypeList::template TypeAt<x>::result a##x
#define _le_tupleT(x) t.template setValue<x>(a##x);
#define _le_const
#define _le_const_flag false

#define _LE_DEFINE_variadic_function_operator(x) \
template <class TFunction, typename TResult, class ConcreteTypeList> \
class TCConcreteFunctionInterfaceMixin<TFunction, TResult, ConcreteTypeList, _le_const_flag, x + 1> \
{ \
public: \
	TResult operator()(typename ConcreteTypeList::template TypeAt<0>::result a0 LE_PP_REPETITION_FROM_0_TO(x, _le_paramT)) _le_const \
	{ \
		TCTuple<ConcreteTypeList> t; \
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
class TCVariadicFunctionMixin : public TCVariadicFunctionInterfaceMixin<TFunction, TResult, maxArgs, isConst>,
			public TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs - 1>
{
	public:
		typedef TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs> TVariadic;
		using TCVariadicFunctionInterfaceMixin<TFunction, TResult, maxArgs, isConst>::operator();
		using TCVariadicFunctionMixin<TFunction, TResult, isConst, maxArgs - 1>::operator();
};

template <class TFunction, template <class TTypeList> class TResult, bool isConst>
class TCVariadicFunctionMixin<TFunction, TResult, isConst, 0> :
		public TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0, isConst>
{
	public:
		using TCVariadicFunctionInterfaceMixin<TFunction, TResult, 0, isConst>::operator();
};

template <class TFunction, typename RetType, typename ArgType, bool isConst = false, int maxArgs = 12>
class TCMonoTypeVariadicFunctionMixin :
		public TCConcreteFunctionInterfaceMixin<TFunction, RetType, typename TSTypeList<>::PushBack<ArgType, maxArgs>::result, isConst, maxArgs>,
		public TCMonoTypeVariadicFunctionMixin<TFunction, RetType, ArgType, isConst, maxArgs - 1>
{
public:
	typedef TCMonoTypeVariadicFunctionMixin<TFunction, RetType, ArgType, isConst, maxArgs> TVariadic;
	using TCConcreteFunctionInterfaceMixin<TFunction, RetType, typename TSTypeList<>::PushBack<ArgType, maxArgs>::result, isConst, maxArgs>::operator();
	using TCMonoTypeVariadicFunctionMixin<TFunction, RetType, ArgType, isConst, maxArgs - 1>::operator();
};

template <class TFunction, typename RetType, typename ArgType, bool isConst>
class TCMonoTypeVariadicFunctionMixin<TFunction, RetType, ArgType, isConst, 0> :
		public TCConcreteFunctionInterfaceMixin<TFunction, RetType, TSTypeList<>, isConst, 0>
{
public:
	using TCConcreteFunctionInterfaceMixin<TFunction, RetType, TSTypeList<>, isConst, 0>::operator();
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
