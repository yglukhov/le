#pragma once

#include <template/util/slTSConstRef.h>
#include <memory>
#include "base/slCVariantBase.h"

LE_NAMESPACE_START

class CVariant : public _CVariantBase
{
	public:
		CVariant();
		CVariant(const CVariant& copy);

		template <typename T>
		CVariant(const T& copy) :
			mImpl(new TCVariantImpl<T>(copy))
		{

		}

		template <typename T>
		bool castsTo() const
		{
			return (mImpl.get())?(mImpl->castsTo<T>()):(false);
		}

		template <typename T>
		T value() const
		{
			return (mImpl.get())?(mImpl->value<T>()):(T());
		}

		bool operator == (const CVariant& rhs) const;

		template <typename T>
		bool operator == (const T& rhs) const
		{
			return (mImpl.get())?(mImpl->value<T>() == rhs):(rhs == T());
		}

		const CVariant& operator = (const CVariant& copy);

		template <typename T>
		const CVariant& operator = (typename TSConstRef<T>::result copy)
		{
			mImpl.reset(new TCVariantImpl<T>(copy));
			return *this;
		}

	private:
		std::auto_ptr<IVariantImpl> mImpl;
};

LE_NAMESPACE_END
