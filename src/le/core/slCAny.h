#if !defined SL_LE_core_slCAny_h
#define SL_LE_core_slCAny_h

#include "slCObject.h"
#include "base/slTCAnyContainer.h"


namespace sokira
{
	namespace le
	{

class CAny : public CObject
{
	public:
		CAny();

		template <typename T>
		CAny(T value) :
			mValue(new TCAnyContainer<typename TSConstRef<T>::result>(value))
		{
			std::cout << "value constructor\n";
		}

		CAny(const CAny& copy);
		virtual ~CAny();

		template <typename T>
		static CAny constRef(const T& value)
		{
			return CAny((IAnyContainer*)new TCAnyContainer<const T&>(value));
		}

		template <typename T>
		static CAny ref(T& value)
		{
			return CAny((IAnyContainer*)new TCAnyContainer<TSRemoveConst<T>::result&>(value));
		}

		const CAny& operator = (const CAny& copy);

		template <typename T>
		const CAny& operator=(typename TSRef<T>::result& value)
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
				std::cout << "mValue NULL\n";
				throw std::bad_cast();
			}

			TResult* result = static_cast<TResult*>(mValue->get(typeid(TResult)));
			if (!result)
			{
				std::cout << "Result NULL\n";
				throw std::bad_cast();
			}

			return *result;
		}

	private:
		CAny(IAnyContainer* container);
		IAnyContainer* mValue;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCAny_h
