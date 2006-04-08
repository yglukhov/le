#pragma once

template <typename RetType, unsigned length>
struct TSFunctionCallWithTuple;

template <typename R>
struct TSFunctionCallWithTuple<R, 0>
{
	template <typename FuncType, class TList>
	static inline R callWithTuple(FuncType func, TCTuple<TList>& /*tuple*/)
	{
		return func();
	}
};

#define f_declare_start(number)	\
template <typename R>	\
struct TSFunctionCallWithTuple<R, number>	\
{	\
	template <typename FuncType, class TList>	\
	static inline R callWithTuple(FuncType func, TCTuple<TList>& tuple)	\
	{	\
		return func(


#define t(index) tuple.template value<index>()

#define f_declare_end		);	\
	}	\
};

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