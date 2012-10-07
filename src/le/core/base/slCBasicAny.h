#if !defined SL_LE_core_base_slCBasicAny_h
#define SL_LE_core_base_slCBasicAny_h

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include <le/core/template/util/slTSCommon.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/slTCPointer.h>

namespace sokira
{
	namespace le
	{

class CBasicAny
{
	public:
		CBasicAny();

		template <typename T>
		CBasicAny(const T& value) :
			mValue(new TCAnyContainer<T>(value))
		{

		}

		CBasicAny(const CBasicAny& copy);

		template <typename T>
		static CBasicAny constRef(const T& value)
		{
			return CBasicAny((IAnyContainer*)new TCAnyContainer<const T&>(value));
		}

		template <typename T>
		static CBasicAny mutableRef(T& value)
		{
			return CBasicAny((IAnyContainer*)new TCAnyContainer<typename TSRemoveConst<T>::result&>(value));
		}

		template <typename T>
		static CBasicAny ref(T& value)
		{
			return mutableRef(value);
		}

		template <typename T>
		static CBasicAny ref(const T& value)
		{
			return constRef(value);
		}

		const CBasicAny& operator = (const CBasicAny& copy);

		template <typename T>
		const CBasicAny& operator=(typename TSRef<T>::result& value)
		{
			mValue = new TCAnyContainer<typename TSRef<T>::result>(value);
			return *this;
		}

		template <typename T>
		typename TSRef<T>::result value() const
		{
			typedef typename TSRemoveRef<typename TSRef<T>::result>::result TResult;
			if (!mValue)
			{
				throw std::bad_cast();
			}

			TResult* result = static_cast<TResult*>(mValue->get(typeid(const TResult*)));
			if (!result)
			{
				throw std::bad_cast();
			}

			return *result;
		}

		template <typename T>
		typename TSRemoveConst<typename TSRef<T>::result>::result mutableValue()
		{
			typedef typename TSRemoveRef<typename TSRef<T>::result>::result TResult;
			if (!mValue || mValue->isConst())
			{
				throw std::bad_cast();
			}

			TResult* result = static_cast<TResult*>(mValue->get(typeid(const TResult*)));
			if (!result)
			{
				throw std::bad_cast();
			}

			return const_cast<typename TSRemoveConst<typename TSRef<T>::result>::result>(*result);
		}

	private:
		class IAnyContainer : public CSimpleRefCountable
		{
			public:
				virtual IAnyContainer* copy() const = 0;
				virtual void* get(const std::type_info& type) const = 0;
				virtual bool isConst() const = 0;
		};

		template <typename T>
		class TCAnyContainer : public IAnyContainer
		{
			public:
				TCAnyContainer(const T& value) :
					mValue(value)
				{

				}

				virtual IAnyContainer* copy() const
				{
					if (TSIsRef<T>::value)
					{
						retain();
						return const_cast<IAnyContainer*>(static_cast<const IAnyContainer*>(this));
					}

					return new TCAnyContainer<T>(mValue);
				}

				virtual void* get(const std::type_info& type) const
				{
					if (!strcmp(type.name(), typeid(const typename TSRemoveRef<T>::result*).name()))
					{
						return const_cast<void*>(static_cast<const void*>(&mValue));
					}

					std::cout << "TYPES DO NOT MATCH!" << std::endl;
					std::cout << "Requested type: " << type.name() << std::endl;
					std::cout << "Actual type: " << typeid(const typename TSRemoveRef<T>::result*).name() << std::endl;

					return NULL;
				}

				virtual bool isConst() const
				{
					return TSIsConst<T>::value;
				}

			private:
				T mValue;
		};

		CBasicAny(IAnyContainer* container);
		TCPointer<IAnyContainer> mValue;
};

class CBasicReferenceAny : public CBasicAny
{
public:
	CBasicReferenceAny() {}

	template <typename T>
	CBasicReferenceAny(T& value) : CBasicAny(mutableRef(value)) {}
	template <typename T>
	CBasicReferenceAny(const T& value) : CBasicAny(constRef(value)) {}

	using CBasicAny::operator=;

	template <typename T>
	const CBasicAny& operator=(T& value)
	{
		return (*this = CBasicAny::mutableRef(value));
	}

	template <typename T>
	const CBasicAny& operator=(const T& value)
	{
		return (*this = CBasicAny::constRef(value));
	}
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_base_slCBasicAny_h
