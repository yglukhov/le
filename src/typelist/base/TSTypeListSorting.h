#pragma once

////////////////////////////////////////////////////////////////////////////////
// TSSelect utility struct to select 1 of 2 types depending on bool.
// TODO: Move it somewhere to utilities.
template <bool, typename T, typename F>
struct TSSelect
{
	typedef T result;
};

template <typename T, typename F>
struct TSSelect<false, T, F>
{
	typedef F result;
};


////////////////////////////////////////////////////////////////////////////////
// PopFront
// TODO: Remove this function when RemoveAt will be ready.
template <class TList> struct _TSTypeListPopFront;

template <>
struct _TSTypeListPopFront<_SNullType>
{
	typedef _SNullType _result;
};

template <typename U, typename V>
struct _TSTypeListPopFront<_TSTypeListNode<U, V> >
{
	typedef V _result;
};


////////////////////////////////////////////////////////////////////////////////
// SortJ - this algorithm is performed iteratively within a
// _TSTypeListSortIterate structure.
template <class TListNode, template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortJ;

template <typename T, template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortJ<_TSTypeListNode<T, _SNullType>, TPredicate, l2g>
{
	typedef _TSTypeListNode<T, _SNullType> _result;
};

template <template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortJ<_SNullType, TPredicate, l2g>
{
	typedef _SNullType _result;
};

#define xor(a, b) (((a) && !(b)) || ((b) && !(a)))

template <typename Head, typename Tail, template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortJ<_TSTypeListNode<Head, Tail>, TPredicate, l2g>
{
	typedef Head in1;
	typedef typename _TSTypeListTypeAt<Tail, 0>::_result in2;

	typedef typename TSSelect<((TPredicate<in1, in2>::result) < 0), in1, in2>::result outAsc1;
	typedef typename TSSelect<((TPredicate<in1, in2>::result) >= 0), in1, in2>::result outAsc2;

	typedef typename TSSelect<((TPredicate<in1, in2>::result) > 0), in1, in2>::result outDes1;
	typedef typename TSSelect<((TPredicate<in1, in2>::result) <= 0), in1, in2>::result outDes2;

	typedef typename TSSelect<l2g, outAsc1, outDes1>::result out1;
	typedef typename TSSelect<l2g, outAsc2, outDes2>::result out2;

	typedef _TSTypeListNode<out1, typename _TSTypeListSortJ<_TSTypeListNode<out2, typename _TSTypeListPopFront<Tail>::_result>, TPredicate, l2g>::_result> _result;
};

#undef xor

////////////////////////////////////////////////////////////////////////////////
// _TSTypeListSortIterate - loop to perform a SortJ algorithm on a Type List
template <unsigned start, unsigned end, class TList, template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortIterate
{
	typedef typename _TSTypeListSortJ<typename _TSTypeListSortIterate<start + 1, end, TList, TPredicate, l2g>::_result, TPredicate, l2g>::_result _result;
};

template <unsigned end, class TList, template <typename T1, typename T2> class TPredicate, bool l2g>
struct _TSTypeListSortIterate<end, end, TList, TPredicate, l2g>
{
	typedef typename _TSTypeListSortJ<TList, TPredicate, l2g>::_result _result;
};

////////////////////////////////////////////////////////////////////////////////
// _TSTypeListSort - sort TypeList. TPredicate must define a enum value,
// which is:
//		less than zero,		if	 T1 < T2
//		zero,				if	 T1 == T2
//		greater than zero,	if	 T1 > T2
template <class TListNode, template <typename T1, typename T2> class TPredicate,
			bool fromLessToGreater = true>
struct _TSTypeListSort
{
	typedef typename _TSTypeListSortIterate<2, _TSTypeListLength<TListNode>::_result,
		TListNode, TPredicate, fromLessToGreater>::_result _result;
};
