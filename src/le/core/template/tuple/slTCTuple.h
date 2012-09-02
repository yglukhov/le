#if !defined SL_LE_core_template_tuple_slTCTuple_h
#define SL_LE_core_template_tuple_slTCTuple_h

#include <new>
#include <le/core/template/util/slTSConstToType.h>
#include "slTCUnitTuple.h"

namespace sokira
{
	namespace le
	{

template <typename T>
struct TSDefaultTupleUnit
{
	T mValue;
	const T& value() const
	{
		return mValue;
	}
	
	void setValue(const T& value)
	{
		mValue = value;
	}
};

////////////////////////////////////////////////////////////////////////////////
// Class TCTuple - allows to store objects of different types in one structure,
// and refer to them by index.
template <class TTypeList>
class TCTuple : public TCUnitTuple<TTypeList, TSDefaultTupleUnit>
{
	public:
		////////////////////////////////////////////////////////////////////////
		// value<index>() - return a const reference to the object in the tuple
		// at index
		template <unsigned index>
		const typename TTypeList::template TypeAt<index>::result& value() const
		{
			return TCUnitTuple<TTypeList,
							TSDefaultTupleUnit>::template unit<index>().value();
		}

		////////////////////////////////////////////////////////////////////////
		// value<index>() - return a const reference to the object in the tuple
		// at index
		template <unsigned index>
		void setValue(typename TSConstRef<typename TTypeList::template TypeAt<index>::result>::result newValue)
		{
			TCUnitTuple<TTypeList,
					TSDefaultTupleUnit>::template unit<index>().setValue(newValue);
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
			setValue<i>(obj);
		}

		template<unsigned index, typename T>
		inline void _setValueNonStrict(const T&, TSBoolToType<true>)
		{

		}
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_tuple_slTCUnitTuple_h
