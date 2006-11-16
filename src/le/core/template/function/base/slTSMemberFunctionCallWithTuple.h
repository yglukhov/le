#pragma once

#include <le/core/config/slPrefix.h>
#include <le/core/template/tuple/slTCTuple.h>
//#include <util/slToPointer.h>

LE_NAMESPACE_START

template <class T, typename RetType, unsigned length>
struct TSMemberFunctionCallWithTuple;

//template <class T, typename R>
//struct TSMemberFunctionCallWithTuple<T, R, 0>
//{
//	template <typename FuncType, class TList>
//	static inline R callWithTuple(FuncType func, const TCTuple<TList>& tuple)
//	{
//		return (toMutablePointer(tuple.template value<0>())->*func)();
//	}
//};

#define f_declare_start(number)											\
template <class T, typename R>											\
struct TSMemberFunctionCallWithTuple<T, R, number>						\
{																		\
	template <typename FuncType, class TList>							\
	static inline R callWithTuple(FuncType func, const TCTuple<TList>& tuple)	\
	{																	\
		return (tuple.template value<0>()->*func)(


#define t(index) tuple.template value<(index)+1>()

#define f_declare_end		);											\
	}																	\
};

f_declare_start(0)
f_declare_end;

f_declare_start(1)
t(0)
f_declare_end;

f_declare_start(2)
t(0), t(1)
f_declare_end;

f_declare_start(3)
t(0), t(1), t(2)
f_declare_end;

f_declare_start(4)
t(0), t(1), t(2), t(3)
f_declare_end;

f_declare_start(5)
t(0), t(1), t(2), t(3), t(4)
f_declare_end;

#undef f_declare_start
#undef t
#undef f_declare_end


LE_NAMESPACE_END
