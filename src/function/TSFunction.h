#pragma once

#include <tuple/TCTuple.h>

template <typename R, class TList, unsigned length> struct _TSFunction;

template <typename ReturnType, class TypeList>
struct TSFunction
{
	typedef _TSFunction<ReturnType, TypeList, TypeList::length> FuncType;
	typedef typename FuncType::f function;
	static inline ReturnType callWithTuple(function func, TCTuple<TypeList>& tuple)
	{
		return FuncType::template c(func, tuple);
	}
};

#define p(index) typename L::TypeAt<index>::result
#define t(index) tuple.template value<index>()

template <typename R, class L>
struct _TSFunction <R, L, 0>
{
	typedef R(*f)();
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func();
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 1>
{
	typedef R(*f)(p(0));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 2>
{
	typedef R(*f)(p(0), p(1));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 3>
{
	typedef R(*f)(p(0), p(1), p(2));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 4>
{
	typedef R(*f)(p(0), p(1), p(2), p(3));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 5>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 6>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 7>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 8>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 9>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 10>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 11>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 12>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 13>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 14>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 15>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 16>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 17>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 18>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 19>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 20>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 21>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 22>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 23>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 24>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 25>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 26>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 27>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 28>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 29>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 30>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 31>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 32>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 33>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 34>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 35>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 36>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 37>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 38>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 39>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 40>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 41>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 42>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 43>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 44>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 45>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 46>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44), p(45));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44), t(45));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 47>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44), p(45), 
			p(46));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44), t(45), 
			t(46));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 48>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44), p(45), 
			p(46), p(47));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44), t(45), 
			t(46), t(47));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 49>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44), p(45), 
			p(46), p(47), p(48));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44), t(45), 
			t(46), t(47), t(48));
	}
};

template <typename R, class L>
struct _TSFunction <R, L, 50>
{
	typedef R(*f)(p(0), p(1), p(2), p(3), p(4), p(5), p(6), p(7), p(8), p(9), 
			p(10), p(11), p(12), p(13), p(14), p(15), p(16), p(17), p(18), 
			p(19), p(20), p(21), p(22), p(23), p(24), p(25), p(26), p(27), 
			p(28), p(29), p(30), p(31), p(32), p(33), p(34), p(35), p(36), 
			p(37), p(38), p(39), p(40), p(41), p(42), p(43), p(44), p(45), 
			p(46), p(47), p(48), p(49));
	template <typename FuncType, class Tuple>
	static inline R c(FuncType func, Tuple& tuple)
	{
		return func(t(0), t(1), t(2), t(3), t(4), t(5), t(6), t(7), t(8), t(9), 
			t(10), t(11), t(12), t(13), t(14), t(15), t(16), t(17), t(18), 
			t(19), t(20), t(21), t(22), t(23), t(24), t(25), t(26), t(27), 
			t(28), t(29), t(30), t(31), t(32), t(33), t(34), t(35), t(36), 
			t(37), t(38), t(39), t(40), t(41), t(42), t(43), t(44), t(45), 
			t(46), t(47), t(48), t(49));
	}
};

#undef p
#undef t
