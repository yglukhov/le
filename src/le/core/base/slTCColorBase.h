#pragma once

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{
		namespace base
		{

class CColorBase
{
	protected:
		template <typename To, typename From> struct _convert;
};

template <typename T>
struct CColorBase::_convert<T, T>
{
	static inline T convert(T component)
	{
		return component;
	}
};

template <>
struct CColorBase::_convert<Float32, UInt8>
{
	static inline Float32 convert(UInt8 component)
	{
		return static_cast<Float32>(component)/(255.0f);
	}
};

template <>
struct CColorBase::_convert<UInt8, Float32>
{
	static inline UInt8 convert(Float32 component)
	{
		return static_cast<UInt8>(component * 255.0f);
	}
};

		} // namespace base
	} // namespace le
} // namespace sokira
