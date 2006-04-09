#pragma once

#include "TCUnitTuple.h"

template <typename T, unsigned index>
struct TSDefaultTupleUnit
{
	T mValue;
};

template <bool b>
class Bool2Type
{

};

template <class TTypeList>
class TCTuple : public TCUnitTuple<TTypeList, TSDefaultTupleUnit>
{
	typedef TCUnitTuple<TTypeList, TSDefaultTupleUnit> Super;

	public:
		//////////////////////////////////////////////////////////////////////////
		// value<index>() - return a reference to the object in the tuple at index
		template <unsigned index>
		typename TTypeList::template TypeAt<index>::result& value()
		{
			return Super::template unit<index>().mValue;
		}

		//////////////////////////////////////////////////////////////////////////
		// setValueNonStrict<index>(T) - if an object at index exists, set its
		// value to T.
		template <unsigned index, typename T>
		inline void setValueNonStrict(const T& obj)
		{
			_setValueNonStrict<index, T>(obj, Bool2Type<(index >= TTypeList::length)>());
		}

	private:
		template <unsigned i, typename T>
		inline void _setValueNonStrict(const T& obj, Bool2Type<false>)
		{
			value<i>() = obj;
		}

		template<unsigned index, typename T>
		inline void _setValueNonStrict(const T&, Bool2Type<true>)
		{

		}
};
