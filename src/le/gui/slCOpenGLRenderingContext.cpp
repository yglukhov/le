#include <glut/slGlut.h>
#include "slCOpenGLRenderingContext.h"

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// Set color functions

void COpenGLRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b)
{
	glColor3b ((GLbyte)r, (GLbyte)g, (GLbyte)b);
}

void COpenGLRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b, SInt8 a)
{
	glColor4b((GLbyte)r, (GLbyte)g, (GLbyte)b, (GLbyte)a);
}

void COpenGLRenderingContext::setColor(const SInt8* vector)
{
	glColor3bv((const GLbyte*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const SInt8* vector)
{
	glColor4bv((const GLbyte*)vector);
}

void COpenGLRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b)
{
	glColor3ub ((GLubyte)r, (GLubyte)g, (GLubyte)b);
}

void COpenGLRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a)
{
	glColor4ub((GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a);
}

void COpenGLRenderingContext::setColor(const UInt8* vector)
{
	glColor3ubv((const GLubyte*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const UInt8* vector)
{
	glColor4ubv((const GLubyte*)vector);
}

void COpenGLRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b)
{
	glColor3s ((GLshort)r, (GLshort)g, (GLshort)b);
}

void COpenGLRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b, SInt16 a)
{
	glColor4s((GLshort)r, (GLshort)g, (GLshort)b, (GLshort)a);
}

void COpenGLRenderingContext::setColor(const SInt16* vector)
{
	glColor3sv((const GLshort*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const SInt16* vector)
{
	glColor4sv((const GLshort*)vector);
}

void COpenGLRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b)
{
	glColor3us ((GLushort)r, (GLushort)g, (GLushort)b);
}

void COpenGLRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b, UInt16 a)
{
	glColor4us((GLushort)r, (GLushort)g, (GLushort)b, (GLushort)a);
}

void COpenGLRenderingContext::setColor(const UInt16* vector)
{
	glColor3usv((const GLushort*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const UInt16* vector)
{
	glColor4usv((const GLushort*)vector);
}

void COpenGLRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b)
{
	glColor3i ((GLint)r, (GLint)g, (GLint)b);
}

void COpenGLRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b, SInt32 a)
{
	glColor4i((GLint)r, (GLint)g, (GLint)b, (GLint)a);
}

void COpenGLRenderingContext::setColor(const SInt32* vector)
{
	glColor3iv((const GLint*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const SInt32* vector)
{
	glColor4iv((const GLint*)vector);
}

void COpenGLRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b)
{
	glColor3ui ((GLuint)r, (GLuint)g, (GLuint)b);
}

void COpenGLRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b, UInt32 a)
{
	glColor4ui((GLuint)r, (GLuint)g, (GLuint)b, (GLuint)a);
}

void COpenGLRenderingContext::setColor(const UInt32* vector)
{
	glColor3uiv((const GLuint*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const UInt32* vector)
{
	glColor4uiv((const GLuint*)vector);
}

void COpenGLRenderingContext::setColor(Float32 r, Float32 g, Float32 b)
{
	glColor3f ((GLfloat)r, (GLfloat)g, (GLfloat)b);
}

void COpenGLRenderingContext::setColor(Float32 r, Float32 g, Float32 b, Float32 a)
{
	glColor4f((GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
}

void COpenGLRenderingContext::setColor(const Float32* vector)
{
	glColor3fv((const GLfloat*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const Float32* vector)
{
	glColor4fv((const GLfloat*)vector);
}

void COpenGLRenderingContext::setColor(Float64 r, Float64 g, Float64 b)
{
	glColor3d ((GLdouble)r, (GLdouble)g, (GLdouble)b);
}

void COpenGLRenderingContext::setColor(Float64 r, Float64 g, Float64 b, Float64 a)
{
	glColor4d((GLdouble)r, (GLdouble)g, (GLdouble)b, (GLdouble)a);
}

void COpenGLRenderingContext::setColor(const Float64* vector)
{
	glColor3dv((const GLdouble*)vector);
}

void COpenGLRenderingContext::setColorWithAlpha(const Float64* vector)
{
	glColor4dv((const GLdouble*)vector);
}

////////////////////////////////////////////////////////////////////////////////
// Geometry

void COpenGLRenderingContext::drawLine(const CPoint& a, const CPoint& b)
{
	glBegin(GL_LINES);
		glVertex3f(a.x(), a.y(), a.z());
		glVertex3f(b.x(), b.y(), b.z());
	glEnd();
}

void COpenGLRenderingContext::drawRect(const CRectangle& rect)
{
	glRectf(rect.x(), rect.y(), rect.x() + rect.width(), rect.y() + rect.height());
}

void COpenGLRenderingContext::drawWireRect(const CRectangle& rect)
{
	glBegin(GL_LINE_STRIP);
		glVertex2f(rect.x(), rect.y());
		glVertex2f(rect.x() + rect.width(), rect.y());
		glVertex2f(rect.x() + rect.width(), rect.y() + rect.height());
		glVertex2f(rect.x(), rect.y() + rect.height());
		glVertex2f(rect.x(), rect.y());
	glEnd();	
}


void COpenGLRenderingContext::drawBox(const CBox& box)
{
	glBegin(GL_QUADS);
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x() + box.width(), box.y(), box.z());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z());
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		
		
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
	glEnd();	
}

void COpenGLRenderingContext::drawWireBox(const CBox& box)
{
	glBegin(GL_QUAD_STRIP);
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x() + box.width(), box.y(), box.z());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z());
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		
		glVertex3f(box.x(), box.y(), box.z() + box.depth());
		glVertex3f(box.x(), box.y(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		
		
		glVertex3f(box.x(), box.y() + box.height(), box.z());
		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
	glEnd();
}

	} // namespace le
} // namespace sokira
