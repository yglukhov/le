#if !defined SL_LE_core_template_tuple_slTCTuple_h
#define SL_LE_core_template_tuple_slTCTuple_h

#include <new>
#include <iostream>
#include <le/core/template/util/slTSConstToType.h>
#include "slTCUnitTuple.h"

namespace sokira
{
	namespace le
	{

template <typename T>
struct _TSUnitTupleForNoConstructor
{
	typedef typename TSRemoveConst<typename TSRemoveRef<T>::result>::result TRawType;
	char mValue[sizeof(TRawType)];
	bool inited;

	_TSUnitTupleForNoConstructor():
		inited(false)
	{
		
	}

	~_TSUnitTupleForNoConstructor()
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
struct TSDefaultTupleUnit
{
	typename TSRemoveConst<typename TSRemoveRef<T>::result>::result mValue;

	T& value() const
	{
		return const_cast<T&>(mValue);
	}
	
	void setValue(const T& value)
	{
		mValue = value;
	}
};

template <typename T>
struct TSDefaultTupleUnit<T&>
{
	T* mValue;
	T& value() const
	{
		return *mValue;
	}
	
	void setValue(const T& value)
	{
		mValue = const_cast<T*>(&value);
	}
};

template <typename T>
struct TSDefaultTupleUnit<const T&>
{
	const T* mValue;
	/*const */T& value() const
	{
		return const_cast<T&>(*mValue);
	}
	
	void setValue(const T& value)
	{
		mValue = &value;
	}
};

////////////////////////////////////////////////////////////////////////////////
// Class TCTuple - allows to store objects of different types in one structure,
// and refer to them by index.
template <class TTypeList, template <typename T> class TUnit = TSDefaultTupleUnit>
class TCTuple : public TCUnitTuple<TTypeList, TUnit>
{
	public:
		////////////////////////////////////////////////////////////////////////
		// value<index>() - return a const reference to the object in the tuple
		// at index
		template <unsigned index>
		typename TSRef<typename TTypeList::template TypeAt<index>::result>::result value() const
		{
			return TCUnitTuple<TTypeList, TUnit>::template unit<index>().value();
		}

		////////////////////////////////////////////////////////////////////////
		// value<index>() - return a const reference to the object in the tuple
		// at index
		template <unsigned index, typename T>
		void setValue(/*typename TSConstRef<typename TTypeList::template TypeAt<index>::result>::result*/const T& newValue)
		{
			TCUnitTuple<TTypeList, TUnit>::template unit<index>().setValue(newValue);
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

		void dump(std::ostream& stream) const
		{
			TTypeList::template Enumerate<TSTupleDumper, _SNullType, TSTupleDumperTerminator>::dump(stream, this);
		}

		////////////////////////////////////////////////////////////////////////
		// Implementation
		////////////////////////////////////////////////////////////////////////
	private:
		template <class TContext>
		struct TSTupleDumper
		{
			template <class Tuple>
			static inline void dump(std::ostream& s, const Tuple* t)
			{
				s << TContext::I << ": " << t->template value<TContext::I>() << "\n";
				TContext::Next::dump(s, t);
			}
		};

		struct TSTupleDumperTerminator
		{
			template <class Tuple>
			static inline void dump(std::ostream& s, const Tuple* t)
			{

			}
		};

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

		template <class TTypeList>
		class TCReferenceTuple : public TCTuple<TTypeList>
		{
			
		};
		
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_tuple_slTCUnitTuple_h
