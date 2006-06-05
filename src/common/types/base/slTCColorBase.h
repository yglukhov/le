#pragma once

#include <common/types/slBasic.h>

LE_NAMESPACE_START

class _TCColorBase
{
	protected:
		template <typename To, typename From>
		struct _convert
		{
			
		};

};

		template <typename T>
		struct _TCColorBase::_convert<T, T>
		{
			static inline T convert(T component)
			{
				return component;
			}
		};

		template <>
		struct _TCColorBase::_convert<Float4, UInt1>
		{
			static inline Float4 convert(UInt1 component)
			{
				return static_cast<Float4>(component)/(255.0f);
			}
		};

		template <>
		struct _TCColorBase::_convert<UInt1, Float4>
		{
			static inline UInt1 convert(Float4 component)
			{
				return static_cast<UInt1>(component * 255.0f);
			}
		};


LE_NAMESPACE_END
