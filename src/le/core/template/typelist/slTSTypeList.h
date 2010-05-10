#pragma once

#include <le/core/config/slPrefix.h>
#include "base/slTSTypeListBase.h"
#include "base/slTSTypeListAppendTraits.h"
#include "base/slTSTypeListSorting.h"

namespace sokira
{
	namespace le
	{

template <typename T0 = _SNullType, typename T1 = _SNullType, typename T2 = _SNullType,
		typename T3 = _SNullType, typename T4 = _SNullType, typename T5 = _SNullType,
		typename T6 = _SNullType, typename T7 = _SNullType, typename T8 = _SNullType,
		typename T9 = _SNullType, typename T10 = _SNullType, typename T11 = _SNullType,
		typename T12 = _SNullType, typename T13 = _SNullType, typename T14 = _SNullType,
		typename T15 = _SNullType, typename T16 = _SNullType, typename T17 = _SNullType,
		typename T18 = _SNullType, typename T19 = _SNullType, typename T20 = _SNullType,
		typename T21 = _SNullType, typename T22 = _SNullType, typename T23 = _SNullType,
		typename T24 = _SNullType, typename T25 = _SNullType, typename T26 = _SNullType,
		typename T27 = _SNullType, typename T28 = _SNullType, typename T29 = _SNullType,
		typename T30 = _SNullType, typename T31 = _SNullType, typename T32 = _SNullType,
		typename T33 = _SNullType, typename T34 = _SNullType, typename T35 = _SNullType,
		typename T36 = _SNullType, typename T37 = _SNullType, typename T38 = _SNullType,
		typename T39 = _SNullType, typename T40 = _SNullType, typename T41 = _SNullType,
		typename T42 = _SNullType, typename T43 = _SNullType, typename T44 = _SNullType,
		typename T45 = _SNullType, typename T46 = _SNullType, typename T47 = _SNullType,
		typename T48 = _SNullType, typename T49 = _SNullType>
struct TSTypeList
{
	private:

	typedef typename TSTypeListTraits<
		_TSTypeListNode<T0, _TSTypeListNode<T1, _TSTypeListNode<T2,
		_TSTypeListNode<T3, _TSTypeListNode<T4, _TSTypeListNode<T5,
		_TSTypeListNode<T6, _TSTypeListNode<T7, _TSTypeListNode<T8,
		_TSTypeListNode<T9, _TSTypeListNode<T10, _TSTypeListNode<T11,
		_TSTypeListNode<T12, _TSTypeListNode<T13, _TSTypeListNode<T14,
		_TSTypeListNode<T15, _TSTypeListNode<T16, _TSTypeListNode<T17,
		_TSTypeListNode<T18, _TSTypeListNode<T19, _TSTypeListNode<T20,
		_TSTypeListNode<T21, _TSTypeListNode<T22, _TSTypeListNode<T23,
		_TSTypeListNode<T24, _TSTypeListNode<T25, _TSTypeListNode<T26,
		_TSTypeListNode<T27, _TSTypeListNode<T28, _TSTypeListNode<T29,
		_TSTypeListNode<T30, _TSTypeListNode<T31, _TSTypeListNode<T32,
		_TSTypeListNode<T33, _TSTypeListNode<T34, _TSTypeListNode<T35,
		_TSTypeListNode<T36, _TSTypeListNode<T37, _TSTypeListNode<T38,
		_TSTypeListNode<T39, _TSTypeListNode<T40, _TSTypeListNode<T41,
		_TSTypeListNode<T42, _TSTypeListNode<T43, _TSTypeListNode<T44,
		_TSTypeListNode<T45, _TSTypeListNode<T46, _TSTypeListNode<T47,
		_TSTypeListNode<T48, _TSTypeListNode<T49, _SNullType> > > > > > > > >
		> > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > > >
		> > > > > > >::node _dirtyList;

	public:

	typedef typename _TSTypeListEraseAll<_dirtyList, _SNullType>::_result _headNode;
	typedef typename _TSTypeListEraseAll<typename _dirtyList::Tail, _SNullType>::_result _popFront;

	enum
	{
		length = _TSTypeListLength<_headNode>::_result
	};

	typedef TSTypeList<typename _TSTypeListUnique<_headNode>::_result> uniqueItems;
	typedef typename TSSelect<TSTypesEqual<_popFront, _SNullType>, TSTypeList<>, TSTypeList<_popFront> >::result PopFront;

	template <UInt index>
	struct TypeAt
	{
		typedef typename _TSTypeListTypeAt<_headNode, index>::_result result;
	};

	template <UInt index, typename TDefaultType = _SNullType>
	struct TypeAtNonStrict
	{
		typedef typename _TSTypeListTypeAtNonStrict<_headNode, index,
												TDefaultType>::_result result;
	};

	typedef typename TypeAtNonStrict<0>::result Front;
	typedef typename TypeAtNonStrict<length-1>::result Back;

	template <typename T>
	struct Find
	{
		enum { result = _TSTypeListFind<_headNode, T>::_result };
	};

	template <template <typename T> class TPredicate>
	struct FindIf
	{
		enum { result = _TSTypeListFindIf<_headNode, TPredicate>::_result };
	};

	template <typename T>
	struct PushBack : public TSTypeList<typename _TSTypeListAppend<_headNode,
				typename TSTypeListAppendTraits<T>::listNode>::_result>
	{
		typedef TSTypeList<typename _TSTypeListAppend<_headNode,
				typename TSTypeListAppendTraits<T>::listNode>::_result> result;
	};

	template <typename T>
	struct PushFront : public TSTypeList<typename _TSTypeListAppend<
			typename TSTypeListAppendTraits<T>::listNode, _headNode>::_result>
	{};

	template <typename T>
	struct Erase : public TSTypeList<typename _TSTypeListErase<_headNode, T>::_result>
	{};

	template <typename T>
	struct EraseAll : public TSTypeList<typename _TSTypeListEraseAll<_headNode, T>::_result>
	{};

	// TPredicate<T1, T2>::value should be < 0, =0 or > 0.
	template <template <typename Arg1, typename Arg2> class TPredicate, bool ascending>
	struct Sort : public TSTypeList<typename _TSTypeListSort<_headNode, TPredicate, ascending>::_result>
	{};

	template <template <typename Arg1, typename Arg2> class TPredicate>
	struct SortAsc : public Sort<TPredicate, true>
	{};

	template <template <typename Arg1, typename Arg2> class TPredicate>
	struct SortDes : public Sort<TPredicate, false>
	{};

	template <template <typename T> class mutator>
	struct Mutate : public TSTypeList<typename _TSTypeListMutate<_headNode, mutator>::_result>
	{};

	// Collects a new list of types, for which predicate<T>::value == 1;
	template <template <typename T> class predicate>
	struct CollectIf : public TSTypeList<typename _TSTypeListCollectIf<_headNode, predicate>::_result>
	{};

	template <template <typename T> class mutator>
	struct CollectMutantsIf : public TSTypeList<typename _TSTypeListCollectMutantsIf<_headNode, mutator>::_result>
	{};
};


///////////////////////////////////////////////////////////////////////////////
// Maximum number of elements in TSTypeList
#define LE_PP_TYPELIST_LIMIT 50


	} // namespace le
} // namespace sokira
