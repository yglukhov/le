#pragma once

#include <common/types/slTCColor.h>

LE_NAMESPACE_START

#define DEFINE_GL_COLOR_ACCESSOR_FUNC(type, gltype)			\
															\
inline void slColor(type r, type g, type b)					\
{															\
	glColor3##gltype (r, g, b);								\
}															\
															\
inline void slColor(type r, type g, type b, type a)			\
{															\
	glColor4##gltype(r, g, b, a);							\
}															\
															\
inline void slColor(type* vector)							\
{															\
	glColor3##gltype##v(vector);							\
}															\
															\
inline void slColorWithAlpha(type* vector)					\
{															\
	glColor4##gltype##v(vector);							\
}

DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt8, b)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt8, ub)
DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt16, s)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt16, us)
DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt32, i)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt32, ui)
DEFINE_GL_COLOR_ACCESSOR_FUNC(Float32, f)
DEFINE_GL_COLOR_ACCESSOR_FUNC(Float64, d)

#undef DEFINE_GL_COLOR_ACCESSOR_FUNC


template <typename TComponent>
inline void slColor(const TCColor<TComponent>& color)
{
	slColor(color.red(), color.green(), color.blue(), color.alpha());
}

LE_NAMESPACE_END
