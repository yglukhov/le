#pragma once

#include <template/util/slTSConstRef.h>
#include "slCCastPolicyRegistry.h"

LE_NAMESPACE_START

class _CVariantBase
{
	protected:
		class IVariantImpl
		{
			public:
				virtual ~IVariantImpl() {};

				template <typename T>
				inline bool castsTo() const
				{
					return (isA<T>()) ||
						(CCastPolicyRegistry::instance()->castAvailable(stdTypeInfoName(), typeid(T).name()));
				}

				template <typename T>
				inline T value() const
				{
					return (isA<T>())
								?
							(T(*static_cast<const T*>(data())))
								:
							(CCastPolicyRegistry::instance()->performCast<T>(data(), stdTypeInfoName()));
				}

				template <typename T>
				inline bool isA() const
				{
					return !strcmp(typeid(T).name(), stdTypeInfoName());
				}

				virtual IVariantImpl* copy() const = 0;
				virtual bool compare(const IVariantImpl* rhs) const = 0;
			protected:
				virtual const NChar* stdTypeInfoName() const = 0;
				virtual const void* data() const = 0;
		};

		template <typename T>
		class TCVariantImpl : public IVariantImpl
		{
			public:
				TCVariantImpl(typename TSConstRef<T>::result copy) : mObj(copy)
				{
				}

				virtual const NChar* stdTypeInfoName() const
				{
					return typeid(T).name();
				}

				virtual const void* data() const
				{
					return static_cast<const void*>(&mObj);
				}

				virtual IVariantImpl* copy() const
				{
					return new TCVariantImpl<T>(mObj);
				}

				virtual bool compare(const IVariantImpl* rhs) const
				{
					return (rhs)?(mObj == rhs->value<T>()):(mObj == T());
				}

			private:
				T mObj;
		};
};

LE_NAMESPACE_END
