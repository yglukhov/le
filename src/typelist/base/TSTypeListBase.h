#pragma once

struct _SNullType
{

};

template <typename U, typename V>
struct _TSTypeListNode
{
	typedef U Head;
	typedef V Tail;
};

////////////////////////////////////////////////////////////////////////////////
// Length
template <class TListNode> struct _TSTypeListLength;

template <>
struct _TSTypeListLength <_SNullType>
{
	enum
	{
		_result = 0
	};
};

template <typename T, typename U>
struct _TSTypeListLength<_TSTypeListNode<T, U> >
{
	enum
	{
		_result = 1 + _TSTypeListLength<U>::_result
	};
};


////////////////////////////////////////////////////////////////////////////////
// TypeAt
template <class TListNode, unsigned int index> struct _TSTypeListTypeAt;

template <typename T, typename U>
struct _TSTypeListTypeAt<_TSTypeListNode<T, U>, 0>
{
	typedef T _result;
};

template <typename T, typename U, unsigned int index>
struct _TSTypeListTypeAt<_TSTypeListNode<T, U>, index>
{
	typedef typename _TSTypeListTypeAt<U, index - 1>::_result _result;
};


////////////////////////////////////////////////////////////////////////////////
// TypeAtNonStrict
template <class TListNode, unsigned int index,
	typename DefaultType = _SNullType>
struct _TSTypeListTypeAtNonStrict
{
	typedef DefaultType _result;
};

template <class Head, class Tail, typename DefaultType>
struct _TSTypeListTypeAtNonStrict<_TSTypeListNode<Head, Tail>, 0, DefaultType>
{
	typedef Head _result;
};

template <class Head, class Tail, unsigned int i, typename DefaultType>
struct _TSTypeListTypeAtNonStrict<_TSTypeListNode<Head, Tail>, i, DefaultType>
{
	typedef typename
		 _TSTypeListTypeAtNonStrict<Tail, i - 1, DefaultType>::_result _result;
};


////////////////////////////////////////////////////////////////////////////////
// EraseAll
template <class TListNode, typename TTypeToErase> struct _TSTypeListEraseAll;

template <typename TTypeToErase>
struct _TSTypeListEraseAll <_SNullType, TTypeToErase>
{
	typedef _SNullType result;
};

template <typename TTypeToErase, typename Tail>
struct _TSTypeListEraseAll <_TSTypeListNode<TTypeToErase, Tail>, TTypeToErase>
{
	typedef typename _TSTypeListEraseAll<Tail, TTypeToErase>::result result;
};

template <typename Head, typename Tail, typename TTypeToErase>
struct _TSTypeListEraseAll <_TSTypeListNode<Head, Tail>, TTypeToErase>
{
	typedef _TSTypeListNode<Head,
		typename _TSTypeListEraseAll<Tail, TTypeToErase>::result> result;
};
