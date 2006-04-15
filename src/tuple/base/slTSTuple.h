#pragma once

#include <config/slPrefix.h>
#include <typelist/slTSTypeList.h>

LE_NAMESPACE_START

template <class TList, template <typename, unsigned> class TUnit, unsigned i = 0> struct TSTuple;

template <unsigned i, template <typename, unsigned> class TUnit>
struct TSTuple <_SNullType, TUnit, i>
{

};

template <typename H, typename T, template <typename, unsigned> class TUnit, unsigned i>
struct TSTuple <_TSTypeListNode<H, T>, TUnit, i> :
	public TUnit<H, i>,
	public TSTuple<T, TUnit, i+1>
{

};


LE_NAMESPACE_END
