#pragma once

#include <le/core/config/slPrefix.h>
#include "base/slTSTypeListBase.h"
#include "base/slTSTypeListSorting.h"

namespace sokira
{
	namespace le
	{

template <typename THeadNode>
struct TSTypeListBase
{
	enum
	{
		length = _TSTypeListLength<THeadNode>::_result
	};

	typedef TSTypeListBase<typename _TSTypeListUnique<THeadNode>::_result> Unique;
	typedef TSTypeListBase<typename _TSTypeListEraseAt<THeadNode, 0>::_result> PopFront;

	template <UInt index>
	struct TypeAt
	{
		typedef typename _TSTypeListTypeAt<THeadNode, index>::_result result;
	};

	template <UInt index, typename TDefaultType = _SNullType>
	struct TypeAtNonStrict
	{
		typedef typename _TSTypeListTypeAtNonStrict<THeadNode, index,
												TDefaultType>::_result result;
	};

	typedef typename TypeAtNonStrict<0>::result Front;
	typedef typename TypeAtNonStrict<(UInt)(length-1)>::result Back;

	template <template <typename T> class TPredicate>
	struct FindIf
	{
		enum { result = _TSTypeListFindIf<THeadNode, TPredicate>::_result };
	};

	template <typename T>
	struct Find
	{
		template <typename Rhs> struct Predicate : public TSTypesEqual<Rhs, T> {};
		enum { result = FindIf<Predicate>::result };
	};

	template <int position, typename TTypeToInsert, int count = 1>
	struct Insert
	{
		typedef TSTypeListBase<typename _TSTypeListInsert<THeadNode, TTypeToInsert, position, count>::_result> result;
	};

	template <typename T, unsigned count = 1>
	struct PushBack : public Insert<length, T, count>
	{};

	template <typename T, unsigned count = 1>
	struct PushFront : public Insert<0, T, count>
	{};

	template <UInt32 i>
	struct EraseAt
	{
		typedef TSTypeListBase<typename _TSTypeListEraseAt<THeadNode, i>::_result> result;
	};

	template <typename T>
	struct Erase
	{
		typedef TSTypeListBase<typename _TSTypeListErase<THeadNode, T>::_result> result;
	};

	template <typename T>
	struct EraseAll
	{
		typedef TSTypeListBase<typename _TSTypeListEraseAll<THeadNode, T>::_result> result;
	};

	// TPredicate<T1, T2>::value should be < 0, =0 or > 0.
	template <template <typename Arg1, typename Arg2> class TPredicate, bool ascending>
	struct Sort
	{
		typedef TSTypeListBase<typename _TSTypeListSort<THeadNode, TPredicate, ascending>::_result> result;
	};

	template <template <typename Arg1, typename Arg2> class TPredicate>
	struct SortAsc : public Sort<TPredicate, true>
	{};

	template <template <typename Arg1, typename Arg2> class TPredicate>
	struct SortDes : public Sort<TPredicate, false>
	{};

	// Collects a new list of types, for which predicate<T>::value == 1;
	template <template <typename T> class predicate>
	struct CollectIf
	{
		typedef TSTypeListBase<typename _TSTypeListCollectIf<THeadNode, predicate>::_result> result;
	};

	template <template <typename T> class mutator>
	struct CollectMutantsIf
	{
		typedef TSTypeListBase<typename _TSTypeListCollectMutantsIf<THeadNode, mutator>::_result> result;
	};

	template <template <typename T> class mutator>
	struct Mutate
	{
		template <typename T> struct Mutator : public mutator<T>, public TSTrue {};
		typedef typename CollectMutantsIf<Mutator>::result result;
	};

	//////////////
	// Enumeration
	template <template <class TContext> class TEnumerator, UInt32 i, class CustomDefinitions, class TerminationEnumerator>
	struct TSTypeListEnumerationContext;

	template <int i, bool atEnd, template <class TContext> class TEnumerator, class CustomDefinitions, class TerminationEnumerator>
	struct TSEnumerationCycle : public TEnumerator<TSTypeListEnumerationContext<TEnumerator, i, CustomDefinitions, TerminationEnumerator> >
	{ };

	template <int i, template <class TContext> class TEnumerator, class CustomDefinitions, class TerminationEnumerator>
	struct TSEnumerationCycle<i, true, TEnumerator, CustomDefinitions, TerminationEnumerator> : public TerminationEnumerator
	{ };

	template <template <class TContext> class TEnum, UInt32 i, class CustomDefinitions, class TerminationEnumerator>
	struct TSTypeListEnumerationContext : public CustomDefinitions
	{
		template <class _T>
		struct TEnumerator : public TEnum<_T>
		{

		};
		typedef TSTypeListBase<THeadNode> TTypeList;
		enum { I = i };
		typedef typename TTypeList::template TypeAt<i>::result T;
		typedef TSEnumerationCycle<i + 1, i + 1 == TTypeList::length, TEnum, CustomDefinitions, TerminationEnumerator> Next;
	};

	template <template <class TContext> class TEnumerator, class CustomDefinitions = _SNullType, class TerminationEnumerator = TEnumerator<_SNullType> >
	struct Enumerate : public TSEnumerationCycle<0, !length, TEnumerator, CustomDefinitions, TerminationEnumerator>
	{ };
};

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
		struct TSTypeList : public TSTypeListBase<
			typename _TSTypeListEraseAll<
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
		> > > > > >, _SNullType>::_result >
{

};

///////////////////////////////////////////////////////////////////////////////
// Maximum number of elements in TSTypeList
#define LE_PP_TYPELIST_LIMIT 50


	} // namespace le
} // namespace sokira
