#if !defined SL_LE_core_base_slCBasicAny_h
#define SL_LE_core_base_slCBasicAny_h

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>
#include <le/core/template/util/slTSCommon.h>

namespace sokira
{
	namespace le
	{

class CBasicAny
{
	public:
		CBasicAny();

		template <typename T>
		CBasicAny(T value) :
			mValue(new TCAnyContainer<T>(value))
		{

		}

		CBasicAny(const CBasicAny& copy);
		virtual ~CBasicAny();

		template <typename T>
		static CBasicAny constRef(const T& value)
		{
			return CBasicAny((IAnyContainer*)new TCAnyContainer<const T&>(value));
		}

		template <typename T>
		static CBasicAny ref(T& value)
		{
			return CBasicAny((IAnyContainer*)new TCAnyContainer<typename TSRemoveConst<T>::result&>(value));
		}

		const CBasicAny& operator = (const CBasicAny& copy);

		template <typename T>
		const CBasicAny& operator=(typename TSRef<T>::result& value)
		{
			delete mValue;
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

	private:
		class IAnyContainer
		{
			public:
				virtual IAnyContainer* copy() const = 0;
				virtual void* get(const std::type_info& type) const = 0;
				virtual ~IAnyContainer();
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
			private:
				T mValue;
		};

		CBasicAny(IAnyContainer* container);
		IAnyContainer* mValue;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_base_slCBasicAny_h
