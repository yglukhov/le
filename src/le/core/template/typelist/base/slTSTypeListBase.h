#pragma once

#include <le/core/template/util/slTSCommon.h>

namespace sokira
{
	namespace le
	{

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
// Find
template <class TListNode, class T> struct _TSTypeListFind;

template <class T>
struct _TSTypeListFind<_SNullType, T>
{
	enum { _result = -1 };
};

template <class T, class Tail>
struct _TSTypeListFind<_TSTypeListNode<T, Tail>, T>
{
	enum { _result = 0 };
};

template <class Head, class Tail, class T>
struct _TSTypeListFind<_TSTypeListNode<Head, Tail>, T>
{
	private:
		enum { temp = _TSTypeListFind<Tail, T>::_result };
	public:
		enum { _result = (temp == -1) ? (-1) : 1 + temp };
};


////////////////////////////////////////////////////////////////////////////////
// Find if
template <class TListNode, template <class T> class TPredicate>
struct _TSTypeListFindIf;

template <template <class T> class TPredicate>
struct _TSTypeListFindIf<_SNullType, TPredicate>
{
	enum { _result = -1 };
};

template <typename U, typename V, template <class T> class TPredicate>
struct _TSTypeListFindIf<_TSTypeListNode<U, V>, TPredicate>
{
	private:
		enum { temp = _TSTypeListFindIf<V, TPredicate>::_result };

	public:
		enum { _result = (TPredicate<U>::result)?
						(0)
						:
						((temp == -1)?(-1):(1 + temp)) };
};


////////////////////////////////////////////////////////////////////////////////
// EraseAt
template <class TListNode, UInt32 i>
struct _TSTypeListEraseAt
{
	typedef typename _TSTypeListEraseAt<typename TListNode::Tail, i - 1>::_result _result;
};

template <typename U, typename V>
struct _TSTypeListEraseAt<_TSTypeListNode<U, V>, 0>
{
	typedef V _result;
};

template <UInt32 i>
struct _TSTypeListEraseAt<_SNullType, i>
{
	typedef _SNullType _result;
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
template <class TListNode, class TTypeToAppend> struct _TSTypeListAppend
{
	typedef _TSTypeListNode<TListNode, TTypeToAppend> _result;
};

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

//template <class Head, class Tail, class T>
//struct _TSTypeListAppend<T, _TSTypeListNode<Head, Tail> >
//{
//	typedef _TSTypeListNode<Head,
//	typename _TSTypeListAppend<Tail, T>::_result> _result;
//};

////////////////////////////////////////////////////////////////////////////////
// Mutate
template <class TListNode, template <typename T> class TMutator>
struct _TSTypeListMutate;

template <template <typename T> class TMutator>
struct _TSTypeListMutate<_SNullType, TMutator>
{
	typedef _SNullType _result;
};

template <typename U, typename V, template <typename T> class TMutator>
struct _TSTypeListMutate<_TSTypeListNode<U, V>, TMutator>
{
	typedef _TSTypeListNode<typename TMutator<U>::result,
					typename _TSTypeListMutate<V, TMutator>::_result> _result;
};

////////////////////////////////////////////////////////////////////////////////
// Collect if
template <class TListNode, template <typename T> class predicate>
struct _TSTypeListCollectIf;

template <template <typename T> class predicate>
struct _TSTypeListCollectIf<_SNullType, predicate>
{
	typedef _SNullType _result;
};

template <typename U, typename V, template <typename T> class predicate>
struct _TSTypeListCollectIf<_TSTypeListNode<U, V>, predicate>
{
	private:
		typedef typename _TSTypeListCollectIf<V, predicate>::_result _tailCollect;

	public:
		typedef typename TSIntSelect<predicate<U>::value,
				_TSTypeListNode<U, _tailCollect>, _tailCollect>::result _result;
};

////////////////////////////////////////////////////////////////////////////////
// Collect mutants if
template <class TListNode, template <typename T> class predicate>
struct _TSTypeListCollectMutantsIf;

template <template <typename T> class predicate>
struct _TSTypeListCollectMutantsIf<_SNullType, predicate>
{
	typedef _SNullType _result;
};

template <bool, typename, template <typename> class pred>
struct _TSMutatorStubResultSelector
{
	typedef _SNullType _result;
};

template <typename T, template <typename> class pred>
struct _TSMutatorStubResultSelector<true, T, pred>
{
	typedef typename pred<T>::result _result;
};

template <typename U, typename V, template <typename T> class predicate>
struct _TSTypeListCollectMutantsIf<_TSTypeListNode<U, V>, predicate>
{
	private:
		typedef typename _TSTypeListCollectMutantsIf<V, predicate>::_result _tailCollect;

	public:
		typedef typename TSIntSelect<predicate<U>::value,
				_TSTypeListNode<typename _TSMutatorStubResultSelector<predicate<U>::value, U, predicate>::_result,
					_tailCollect>, _tailCollect>::result _result;
};


	} // namespace le
} // namespace sokira
