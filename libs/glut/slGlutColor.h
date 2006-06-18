#pragma once

#include <common/types/slTCColor.h>

LE_NAMESPACE_START

#define DEFINE_GL_COLOR_ACCESSOR_FUNC(type, gltype, cast)	\
															\
inline void slColor(type r, type g, type b)					\
{															\
	glColor3##gltype ((cast)r, (cast)g, (cast)b);			\
}															\
															\
inline void slColor(type r, type g, type b, type a)			\
{															\
	glColor4##gltype((cast)r, (cast)g, (cast)b, (cast)a);	\
}															\
															\
inline void slColor(const type* vector)						\
{															\
	glColor3##gltype##v((const cast*)vector);				\
}															\
															\
inline void slColorWithAlpha(const type* vector)			\
{															\
	glColor4##gltype##v((const cast*)vector);				\
}

DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt8, b, GLbyte)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt8, ub, GLubyte)
DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt16, s, GLshort)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt16, us, GLushort)
DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt32, i, GLint)
DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt32, ui, GLuint)
DEFINE_GL_COLOR_ACCESSOR_FUNC(Float32, f, GLfloat)
DEFINE_GL_COLOR_ACCESSOR_FUNC(Float64, d, GLdouble)

#undef DEFINE_GL_COLOR_ACCESSOR_FUNC


template <typename TComponent>
inline void slColor(const TCColor<TComponent>& color)
{
	slColor(color.red(), color.green(), color.blue(), color.alpha());
}

LE_NAMESPACE_END
