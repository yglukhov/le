#if !defined SL_LE_core_template_tuple_slTCTuple_h
#define SL_LE_core_template_tuple_slTCTuple_h

#include <new>
#include <le/core/template/util/slTSConstToType.h>
#include "slTCUnitTuple.h"

namespace sokira
{
	namespace le
	{

template <typename T, bool hasConstructor>
struct _TSUnitTuple
{
	typename TSRemoveConst<typename TSRemoveRef<T>::result>::result mValue;
	const T& value() const
	{
		return mValue;
	}

	void setValue(const T& value)
	{
		mValue = value;
	}
};

template <typename T>
struct _TSUnitTuple<T, false>
{
	typedef typename TSRemoveConst<typename TSRemoveRef<T>::result>::result TRawType;
	char mValue[sizeof(TRawType)];
	bool inited;

	_TSUnitTuple():
		inited(false)
	{
		
	}

	~_TSUnitTuple()
	{
		if (inited)
		{
			reinterpret_cast<TRawType*>(mValue)->TRawType::~TRawType();
		}
	}

	const TRawType& value() const
	{
		return *reinterpret_cast<const TRawType*>(mValue);
	}

	void setValue(const TRawType& value)
	{
		if (inited)
		{
			reinterpret_cast<TRawType*>(mValue)->TRawType::~TRawType();
		}
		new (mValue) TRawType(value);
		inited = true;
	}
};


template <typename T>
struct TSDefaultTupleUnit : _TSUnitTuple<T, true>
{

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
