#pragma once

#include <le/core/config/slPrefix.h>
#include <le/core/template/typelist/slTSTypeList.h>

LE_NAMESPACE_START

template <unsigned i, class T>
struct _TSTupleUnit : public T
{

};

template <class TList, template <typename> class TUnit, unsigned i = 0>
struct TSTuple :
	public _TSTupleUnit<i, TUnit<typename TList::Front> >,
	public TSTuple<typename TList::PopFront, TUnit, i+1>
{

};

template <template <typename> class TUnit, unsigned i>
struct TSTuple <TSTypeList<>, TUnit, i>
{

};
//
//template <typename H, typename T, template <typename, unsigned> class TUnit, unsigned i>
//struct TSTuple <_TSTypeListNode<H, T>, TUnit, i> :
//	public TUnit<H, i>,
//	public TSTuple<T, TUnit, i+1>
//{
//
//};


LE_NAMESPACE_END
