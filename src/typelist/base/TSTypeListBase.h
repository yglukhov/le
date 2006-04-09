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
// Type List traits
template <class T>
struct TSTypeListTraits
{
	typedef T node;
};

template <typename U, typename V, typename T>
struct TSTypeListTraits <_TSTypeListNode<_TSTypeListNode<U, V>, T> >
{
	typedef _TSTypeListNode<U, V> node;
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
template <class TListNode, unsigned int index, typename DefaultType>
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
// IndexOf
template <class TListNode, class T> struct _TSTypeListIndexOf;

template <class T>
struct _TSTypeListIndexOf<_SNullType, T>
{
	enum { _result = -1 };
};

template <class T, class Tail>
struct _TSTypeListIndexOf<_TSTypeListNode<T, Tail>, T>
{
	enum { _result = 0 };
};

template <class Head, class Tail, class T>
struct _TSTypeListIndexOf<_TSTypeListNode<Head, Tail>, T>
{
	private:
		enum { temp = _TSTypeListIndexOf<Tail, T>::_result };
	public:
		enum { _result = temp == -1 ? -1 : 1 + temp };
};


////////////////////////////////////////////////////////////////////////////////
// Erase
template <class TListNode, class TTypeToErase> struct _TSTypeListErase; 
 
template <class TTypeToErase>
struct _TSTypeListErase<_SNullType, TTypeToErase>
{
	typedef _SNullType _result;
};

template <class TTypeToErase, class Tail>
struct _TSTypeListErase<_TSTypeListNode<TTypeToErase, Tail>, TTypeToErase>
{
	typedef Tail _result;
}; 

template <class Head, class Tail, class TTypeToErase>
struct _TSTypeListErase<_TSTypeListNode<Head, Tail>, TTypeToErase>
{
	typedef _TSTypeListNode<Head,
				typename _TSTypeListErase<Tail, TTypeToErase>::_result> _result;
};


////////////////////////////////////////////////////////////////////////////////
// EraseAll
template <class TListNode, typename TTypeToErase> struct _TSTypeListEraseAll;

template <typename TTypeToErase>
struct _TSTypeListEraseAll <_SNullType, TTypeToErase>
{
	typedef _SNullType _result;
};

template <typename TTypeToErase, typename Tail>
struct _TSTypeListEraseAll <_TSTypeListNode<TTypeToErase, Tail>, TTypeToErase>
{
	typedef typename _TSTypeListEraseAll<Tail, TTypeToErase>::_result _result;
};

template <typename Head, typename Tail, typename TTypeToErase>
struct _TSTypeListEraseAll <_TSTypeListNode<Head, Tail>, TTypeToErase>
{
	typedef _TSTypeListNode<Head,
		typename _TSTypeListEraseAll<Tail, TTypeToErase>::_result> _result;
};


////////////////////////////////////////////////////////////////////////////////
// Unique
template <class TListNode> struct _TSTypeListUnique;

template <>
struct _TSTypeListUnique<_SNullType>
{
	typedef _SNullType _result;
};

template <class Head, class Tail>
struct _TSTypeListUnique<_TSTypeListNode<Head, Tail> >
{
	private:
		typedef typename _TSTypeListUnique<Tail>::_result L1;
		typedef typename _TSTypeListErase<L1, Head>::_result L2;
	public:
		typedef _TSTypeListNode<Head, L2> _result;
};


////////////////////////////////////////////////////////////////////////////////
// Append
template <class TListNode, class TTypeToAppend> struct _TSTypeListAppend;

template <>
struct _TSTypeListAppend<_SNullType, _SNullType>
{
	typedef _SNullType _result;
};

template <class T>
struct _TSTypeListAppend<_SNullType, T>
{
	typedef _TSTypeListNode<T, _SNullType> _result;
};

template <class Head, class Tail>
struct _TSTypeListAppend<_SNullType, _TSTypeListNode<Head, Tail> >
{
	typedef _TSTypeListNode<Head, Tail> _result;
};

template <class Head, class Tail, class T>
struct _TSTypeListAppend<_TSTypeListNode<Head, Tail>, T>
{
	typedef _TSTypeListNode<Head,
						typename _TSTypeListAppend<Tail, T>::_result> _result;
};


////////////////////////////////////////////////////////////////////////////////
// Sort
template <class TListNode, template <typename T1, typename T2> TSelector>
struct _TSTypeListSort;

template <template <typename T1, typename T2> TSelector>
struct _TSTypeListSort<_SNullType, TSelector>
{
	typedef _SNullType _result;
};

template <typename U, typename V, typename C,
			template <typename T1, typename T2> TSelector> >
struct _TSTypeListSort<_TSTypeListNode<U, _TSTypeListNode<V, C> >, TSelector>
{
	typedef _SNullType _result;
};



