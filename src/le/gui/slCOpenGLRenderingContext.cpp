#include <glut/slGlut.h>
#include <le/core/slCString.h>
#include <le/core/base/slCImageImpl.hp>
#include <le/gui/base/slCOpenGLTextureImpl.hp>
#include "slCOpenGLRenderingContext.h"

namespace sokira
{
	namespace le
	{

COpenGLRenderingContext::COpenGLRenderingContext() :
	mFontOffset(0)
{
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	mFontOffset = makeFont();
}

COpenGLRenderingContext::~COpenGLRenderingContext()
{
	if (mFontOffset) glDeleteLists(mFontOffset, 128);
	std::cout << "~COpenGLRenderingContext" << std::endl;
}


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

void COpenGLRenderingContext::setLineWidth(Float32 width)
{
	glLineWidth(width);
}


////////////////////////////////////////////////////////////////////////////////
// Geometry
void COpenGLRenderingContext::drawText(const CString& text, const CPoint2D& position)
{
	glRasterPos2f(position.x(), position.y());
	glPushAttrib(GL_LIST_BIT);
	glListBase(mFontOffset);
	glCallLists(text.length(), GL_UNSIGNED_BYTE, (GLubyte *) text.cString());
	glPopAttrib();
}

void COpenGLRenderingContext::drawSegment(const CSegment2D& segment)
{
	glBegin(GL_LINES);
		glVertex2f(segment.a().x(), segment.a().y());
		glVertex2f(segment.b().x(), segment.b().y());
	glEnd();
}

void COpenGLRenderingContext::drawSegment(const CSegment3D& segment)
{
	glBegin(GL_LINES);
		glVertex3f(segment.a().x(), segment.a().y(), segment.a().z());
		glVertex3f(segment.b().x(), segment.b().y(), segment.b().z());
	glEnd();
}

void COpenGLRenderingContext::drawRect(const CRectangle& rect)
{
//	std::cout << "Drawing rect(" << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << ")" << std::endl;
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

CTextureImpl* COpenGLRenderingContext::createTextureImpl(const CTexture* texture, const CImageImpl* image)
{
	if (image->frameCount() == 0)
	{
		std::cout << "FRAME_COUNT 0 in COpenGLRenderingContext::createTextureImpl!!" << std::endl;
		return NULL;
	}

	GLuint* result = new GLuint[image->frameCount()];
	glGenTextures(image->frameCount(), result);

	CSize2D size;
	for (UInt32 i = 0; i < image->frameCount(); ++i)
	{
		CImageFrame frame = image->frameAtIndex(i);

		GLenum format = 0;
		switch (frame.pixelFormat())
		{
			case ePixelFormatRGBA:
				format = GL_RGBA;
				break;
			case ePixelFormatRGB:
				format = GL_RGB;
				break;
			default:
				continue;
		}

//		GLuint result;
//		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		size = frame.size();
		glTexImage2D(GL_TEXTURE_2D, 0, format, size.width(), size.height(),
			0, format, GL_UNSIGNED_BYTE, frame.pixelData());
	}
	return new COpenGLTextureImpl(result, image->frameCount(), size);
}

void COpenGLRenderingContext::setTextureImpl(const CTextureImpl* textureImpl)
{
	const COpenGLTextureImpl* tex = dynamic_cast<const COpenGLTextureImpl*>(textureImpl);
	clock_t curTime = clock();
//	time(&curTime);
//	std::cout << "CLOCK: " << curTime << std::endl;
	clock_t timeDiff = curTime - tex->mCurTextureTime;
//	std::cout << "timediff: " << std::dec << (int)timeDiff << std::endl;
//	std::cout << "time dif in secs: " << (double)timeDiff / (double)CLOCKS_PER_SEC << std::endl;
	if ((double)timeDiff / (double)CLOCKS_PER_SEC * (double)100 > 1)
	{
		++tex->i;
		if (tex->mFrameCount <= tex->i) tex->i = 0;
		tex->mCurTextureTime = curTime;
	}
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, tex->mTextures[tex->i]);
}

void COpenGLRenderingContext::unsetTexture()
{
	glDisable(GL_TEXTURE_2D);
}

void COpenGLRenderingContext::pushClippingRect(const CRectangle& rect)
{
	GLfloat vp[4];
	glGetFloatv(GL_VIEWPORT, vp);

	glMatrixMode(GL_PROJECTION);
	glPushAttrib(GL_VIEWPORT_BIT);
	glPushMatrix();

//	CRectangle rect = absoluteRect();

//			CRectangle clipSize(rect.width() - LE_SCROLL_BAR_WIDTH, rect.height() - LE_SCROLL_BAR_WIDTH);
//	rect.width(rect.width() - LE_SCROLL_BAR_WIDTH);
//	rect.height(rect.height() - LE_SCROLL_BAR_WIDTH);
//	context->pushClippingRect(rect);

	glViewport(rect.x(), vp[3] - (rect.y() + rect.height()), rect.width(), rect.height());
	glLoadIdentity();
	glOrtho(rect.x(), rect.x() + rect.width(), rect.y() + rect.height(), rect.y(), -1, 1);
}

void COpenGLRenderingContext::popClippingRect()
{
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
}

UInt32 COpenGLRenderingContext::makeFont()
{
	GLuint i, j;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLubyte space[] =
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	GLubyte dot[] =
		{0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	GLubyte letters[][13] = {
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
		{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
		{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
		{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
	};


/*
00000000
00000000
00111100
01100110
11000011
11000011
11000011
11000011
11000011
11000011
11000011
01100110
00111100

00000000
00000000
00111100
00011000
00011000
00011000
00011000
00011000
00011000
00011000
00011000
00111000
00011000

00000000
00000000
11111111 FF
11000000
01100000
00110000
00011000
00001100
00000110
00000011
11000011
01100110
00111100 3C

00000000
00000000
00111100 3C
01100110 66
11000011 C3
00000011 03
00000110 06
00011100 1C
00000110 06
00000011 03
11000011 C3
01100110 66
00111100 3C

00000000
00000000
00000110 06
00000110 06
11111111 FF
11000110 C6
01100110 66
01100110 66
00110110 36
00110110 36
00011110 1E
00001110 0E
00000110 06

00000000
00000000
00111100 3C
01100110 66
11000011 C3
00000011 03
00000011 03
00000011 03
11100110 E6
11111100 FC
11000000 C0
11000000 C0
11111110 FE

00000000
00000000
00111100 3C
01100110 66
11000011 C3
11000011 C3
11000011 C3
11000011 C3
11100110 E6
11011100 DC
11000000 C0
01100011 63
00111110 3E


00000000
00000000
01100000 60
01100000 60
00110000 30
00110000 30
00011000 18
00111100 3C
00011000 18
00001100 0C
00000110 06
00000011 03
11111111 FF

00000000
00000000
00111100 3C
01100110 66
11000011 C3
11000011 C3
01100110 66
00111100 3C
01100110 66
11000011 C3
11000011 C3
01100110 66
00111100 3C

00000000
00000000
00111100 3C
01100110 66
11000011 C3
00000011 03
00000011 03
00111111 3F
01100111 67
11000011 C3
11000011 C3
01100110 66
00111100 3C



*/

	GLubyte digits[][13] = {
		{0x00, 0x00, 0x3C, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3C},
		{0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x38, 0x18},
		{0x00, 0x00, 0xFF, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0xC3, 0x66, 0x3C},
		{0x00, 0x00, 0x3C, 0x66, 0xC3, 0x03, 0x06, 0x1C, 0x06, 0x03, 0xC3, 0x66, 0x3C},
		{0x00, 0x00, 0x06, 0x06, 0xFF, 0xC6, 0x66, 0x66, 0x36, 0x36, 0x1E, 0x0E, 0x06},
		{0x00, 0x00, 0x3C, 0x66, 0xC3, 0x03, 0x03, 0x03, 0xE6, 0xFC, 0xC0, 0xC0, 0xFE},
		{0x00, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0xC3, 0xC3, 0xE6, 0xDC, 0xC0, 0x63, 0x3E},
		{0x00, 0x00, 0x60, 0x60, 0x30, 0x30, 0x10, 0x3C, 0x18, 0x0C, 0x06, 0x03, 0xFF},
		{0x00, 0x00, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C, 0x66, 0xC3, 0xC3, 0x66, 0x3C},
		{0x00, 0x00, 0x3C, 0x66, 0xC3, 0x03, 0x03, 0x3F, 0x67, 0xC3, 0xC3, 0x66, 0x3C}
	};



	UInt32 fontOffset = glGenLists (128);
	for (i = 0,j = 'A'; i < 26; i++,j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
		glEndList();
	}

	for (i = 0,j = '0'; i < 10; i++,j++)
	{
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, digits[i]);
		glEndList();
	}

	glNewList(fontOffset + ' ', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
	glEndList();

	glNewList(fontOffset + '.', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, dot);
	glEndList();

	return fontOffset;
}


	} // namespace le
} // namespace sokira
