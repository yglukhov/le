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
		struct _TCColorBase::_convert<Float32, UInt8>
		{
			static inline Float32 convert(UInt8 component)
			{
				return static_cast<Float32>(component)/(255.0f);
			}
		};

		template <>
		struct _TCColorBase::_convert<UInt8, Float32>
		{
			static inline UInt8 convert(Float32 component)
			{
				return static_cast<UInt8>(component * 255.0f);
			}
		};


LE_NAMESPACE_END
