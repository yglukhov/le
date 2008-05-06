#pragma once

#include <le/core/slTCColor.h>

namespace sokira
{
	namespace le
	{

#define _LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(type, gltype, cast)	\
																\
inline void slSetColor(type r, type g, type b)					\
{																\
	glColor3##gltype ((cast)r, (cast)g, (cast)b);				\
}																\
																\
inline void slSetColor(type r, type g, type b, type a)			\
{																\
	glColor4##gltype((cast)r, (cast)g, (cast)b, (cast)a);		\
}																\
																\
inline void slSetColor(const type* vector)						\
{																\
	glColor3##gltype##v((const cast*)vector);					\
}																\
																\
inline void slSetColorWithAlpha(const type* vector)				\
{																\
	glColor4##gltype##v((const cast*)vector);					\
}

_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt8, b, GLbyte)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt8, ub, GLubyte)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt16, s, GLshort)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt16, us, GLushort)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(SInt32, i, GLint)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(UInt32, ui, GLuint)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(Float32, f, GLfloat)
_LE_DEFINE_GL_COLOR_ACCESSOR_FUNC(Float64, d, GLdouble)

#undef _LE_DEFINE_GL_COLOR_ACCESSOR_FUNC


template <typename TComponent>
inline void slSetColor(const TCColor<TComponent>& color)
{
	slSetColor(color.red(), color.green(), color.blue(), color.alpha());
}

	} // namespace le
} // namespace sokira
