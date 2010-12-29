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
		template <typename TComponent> struct _max;
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
		return static_cast<Float32>(component) / 255.0f;
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

template <>
struct CColorBase::_convert<Float32, int>
{
	static inline Float32 convert(int component)
	{
		return static_cast<Float32>(component) / 255.0f;
	}
};

template <>
struct CColorBase::_convert<int, Float32>
{
	static inline int convert(Float32 component)
	{
		return static_cast<int>(component * 255.0f);
	}
};

template <typename T>
struct CColorBase::_max
{
	static inline T max()
	{
		return 255;
	}
};

template <>
struct CColorBase::_max<Float32>
{
	static inline Float32 max()
	{
		return 1.0f;
	}
};

template <>
struct CColorBase::_max<Float64>
{
	static inline Float64 max()
	{
		return 1.0;
	}
};

		} // namespace base
	} // namespace le
} // namespace sokira
