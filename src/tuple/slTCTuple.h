#pragma once

#include <util/slTSConstToType.h>
#include "slTCUnitTuple.h"

LE_NAMESPACE_START

template <typename T, unsigned index>
struct TSDefaultTupleUnit
{
	T mValue;
};

////////////////////////////////////////////////////////////////////////////////
// Class TCTuple - allows to store objects of different types in one structure,
// and refer to them by index.
template <class TTypeList>
class TCTuple : public TCUnitTuple<TTypeList, TSDefaultTupleUnit>
{
	public:
		////////////////////////////////////////////////////////////////////////
		// value<index>() - return a reference to the object in the tuple at index
		template <unsigned index>
		typename TTypeList::template TypeAt<index>::result& value()
		{
			return TCUnitTuple<TTypeList,
							TSDefaultTupleUnit>::template unit<index>().mValue;
		}

		////////////////////////////////////////////////////////////////////////
		// setValueNonStrict<index>(T) - if an object at index exists, set its
		// value to T.
		template <unsigned index, typename T>
		inline void setValueNonStrict(const T& obj)
		{
			_setValueNonStrict<index, T>(obj,
								TSBoolToType<(index >= TTypeList::length)>());
		}


		////////////////////////////////////////////////////////////////////////
		// Implementation
		////////////////////////////////////////////////////////////////////////
	private:
		template <unsigned i, typename T>
		inline void _setValueNonStrict(const T& obj, TSBoolToType<false>)
		{
			value<i>() = obj;
		}

		template<unsigned index, typename T>
		inline void _setValueNonStrict(const T&, TSBoolToType<true>)
		{

		}
};


LE_NAMESPACE_END
