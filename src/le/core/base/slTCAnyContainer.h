#if !defined SL_LE_core_base_slTCAnyContainer_h
#define SL_LE_core_base_slTCAnyContainer_h

////////////////////////////////////////////////////////////////////////////////
// Includes
#include <typeinfo>

namespace sokira
{
	namespace le
	{

class IAnyContainer
{
	public:
		virtual IAnyContainer* copy() const = 0;
		virtual void* get(const std::type_info& type) const = 0;
		virtual ~IAnyContainer(); // defined in ../slCAny.cpp
};

template <typename T>
class TCAnyContainer : public IAnyContainer
{
	public:
		TCAnyContainer(T value) :
			mValue(value)
		{

		}

		virtual IAnyContainer* copy() const
		{
			return new TCAnyContainer<T>(mValue);
		}

		virtual void* get(const std::type_info& type) const
		{
			std::cout << "Requested type: " << type.name() << std::endl;
			std::cout << "Actual type: " << typeid(TSRemoveRef<T>::result).name() << std::endl;
			return (type == typeid(TSRemoveRef<T>::result))?(const_cast<void*>(static_cast<const void*>(&mValue))):(NULL);
		}
	private:
		T mValue;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_base_slTCAnyContainer_h

