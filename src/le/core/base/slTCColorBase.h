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
		template <Bool ToTypeIsFloat, Bool FromTypeIsFloat, typename To, typename From> struct _convert;
		template <typename TComponent> struct _max;
};

template <typename To, typename From>
struct CColorBase::_convert<true, true, To, From>
{
	static inline To convert(From component)
	{
		return static_cast<To>(component);
	}
};

template <typename To, typename From>
struct CColorBase::_convert<false, false, To, From> : public CColorBase::_convert<true, true, To, From> { };

template <typename To, typename From>
struct CColorBase::_convert<true, false, To, From>
{
	static inline To convert(From component)
	{
		return static_cast<To>(component) / CColorBase::_max<From>::max();
	}
};

template <typename To, typename From>
struct CColorBase::_convert<false, true, To, From>
{
	static inline To convert(From component)
	{
		return static_cast<To>(component * CColorBase::_max<To>::max());
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
