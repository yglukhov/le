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
{};


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
		enum { _result = (TPredicate<U>::value)?
						(0)
						:
						((temp == -1)?(-1):(1 + temp)) };
};


////////////////////////////////////////////////////////////////////////////////
// Erase at
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
// Push front
template <class TListNode, typename T, unsigned count>
struct _TSTypeListPushFront
{
	typedef typename _TSTypeListPushFront<_TSTypeListNode<T, TListNode>, T, count - 1>::_result _result;
};

template <class TListNode, typename T>
struct _TSTypeListPushFront<TListNode, T, 0>
{
	typedef TListNode _result;
};


////////////////////////////////////////////////////////////////////////////////
// Insert
template <class TListNode, typename T, unsigned position, unsigned count>
struct _TSTypeListInsert
{
	typedef typename _TSTypeListPushFront<TListNode, T, count>::_result _result;
};

template <typename U, typename V, typename T, unsigned position, unsigned count>
struct _TSTypeListInsert<_TSTypeListNode<U, V>, T, position, count>
{
	typedef _TSTypeListNode<U, typename _TSTypeListInsert<V, T, position - 1, count>::_result> _result;
};

template <typename U, typename V, typename T, unsigned count>
struct _TSTypeListInsert<_TSTypeListNode<U, V>, T, 0, count>
{
	typedef typename _TSTypeListPushFront<_TSTypeListNode<U, V>, T, count>::_result _result;
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
		enum { _predicateResult = predicate<U>::value };
		typedef typename _TSMutatorStubResultSelector<_predicateResult, U, predicate>::_result _mutatedHead;

	public:
		typedef typename TSIntSelect<_predicateResult, _TSTypeListNode<_mutatedHead, _tailCollect>, _tailCollect>::result _result;
};


////////////////////////////////////////////////////////////////////////////////
// Collect if
template <class TListNode, template <typename T> class predicate>
struct _TSTypeListCollectIf
{
	template <typename T> struct Mutator : public predicate<T> { typedef T result; };
	typedef typename _TSTypeListCollectMutantsIf<TListNode, Mutator>::_result _result;
};


////////////////////////////////////////////////////////////////////////////////
// Erase all
template <class TListNode, typename TTypeToErase>
struct _TSTypeListEraseAll
{
	template <typename T>
	struct Predicate : public TSNot<TSTypesEqual<T, TTypeToErase> > { };
	typedef typename _TSTypeListCollectIf<TListNode, Predicate>::_result _result;
};

	} // namespace le
} // namespace sokira
