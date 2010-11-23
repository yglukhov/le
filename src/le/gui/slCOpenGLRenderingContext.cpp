#include <glut/slGlut.h>
#include <le/core/slCString.h>
#include <le/core/base/slCImageImpl.hp>
#include <le/gui/base/slCOpenGLTextureImpl.hp>
#include "slCOpenGLRenderingContext.h"
#include <le/core/slCGradient.h>

namespace sokira
{
	namespace le
	{

COpenGLRenderingContext::COpenGLRenderingContext() :
	mFontOffset(0)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	mFontOffset = makeFont();
}

COpenGLRenderingContext::~COpenGLRenderingContext()
{
	if (mFontOffset) glDeleteLists(mFontOffset, 128);
	std::cout << "~COpenGLRenderingContext" << std::endl;
}

static void processFillForPoint(const CFillMethod* fill, const CPoint2D& point)
{
	if (fill)
	{
		CColor color = fill->colorAtPoint(point);
		glColor4f(color.red(), color.green(), color.blue(), color.alpha());
	}
}

////////////////////////////////////////////////////////////////////////////////
// Set color functions

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

void COpenGLRenderingContext::drawConvexPolygon(const CPolygon& poly)
{
	const std::vector<CPoint2D>& points = poly.points();

	glBegin(GL_POLYGON);
		for (std::vector<CPoint2D>::const_iterator it = points.begin(); it != points.end(); ++it)
		{
			glVertex2f(it->x(), it->y());
		}
	glEnd();
}

void COpenGLRenderingContext::drawRect(const CRectangle& rect)
{
	glBegin(GL_QUADS);
		processFillForPoint(mFillMethod, CPoint2D(rect.x(), rect.y() + rect.height()));
		glVertex2f(rect.x(), rect.y() + rect.height());
		processFillForPoint(mFillMethod, CPoint2D(rect.x(), rect.y()));
		glVertex2f(rect.x(), rect.y());
		processFillForPoint(mFillMethod, CPoint2D(rect.x() + rect.width(), rect.y()));
		glVertex2f(rect.x() + rect.width(), rect.y());
		processFillForPoint(mFillMethod, CPoint2D(rect.x() + rect.width(), rect.y() + rect.height()));
		glVertex2f(rect.x() + rect.width(), rect.y() + rect.height());
	glEnd();
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

void COpenGLRenderingContext::drawRoundedRect(const CRectangle& rect,
	Float32 topLeftXRadius, Float32 topLeftYRadius,
	Float32 topRightXRadius, Float32 topRightYRadius,
	Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
	Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
	glBegin(GL_TRIANGLE_FAN);
		Float32 startAngle = M_PI;
		Float32 endAngle = M_PI / 2;

		Float32 step = (startAngle - endAngle) / ((topLeftXRadius + topLeftYRadius) / 4);
		for (Float32 i = startAngle; i >= endAngle; i -= step)
		{
			Float32 x = rect.x() + topLeftXRadius + topLeftXRadius * cosf(i);
			Float32 y = rect.y() + topLeftYRadius - topLeftYRadius * sinf(i);
			processFillForPoint(mFillMethod, CPoint2D(x, y));
			glVertex2f(x, y);
		}

		startAngle = endAngle;
		endAngle -= M_PI/2;
		step = (startAngle - endAngle) / ((topRightXRadius + topRightYRadius) / 4);
		for (Float32 i = startAngle; i >= endAngle; i -= step)
		{
			Float32 x = rect.x() + rect.width() - topRightXRadius + topRightXRadius * cosf(i);
			Float32 y = rect.y() + topRightYRadius - topRightYRadius * sinf(i);
			processFillForPoint(mFillMethod, CPoint2D(x, y));
			glVertex2f(x, y);
		}

		startAngle = endAngle;
		endAngle -= M_PI/2;
		step = (startAngle - endAngle) / ((bottomRightXRadius + bottomRightYRadius) / 4);
		for (Float32 i = startAngle; i >= endAngle; i -= step)
		{
			Float32 x = rect.x() + rect.width() - bottomRightXRadius + bottomRightXRadius * cosf(i);
			Float32 y = rect.y() + rect.height() - bottomRightYRadius - bottomRightYRadius * sinf(i);
			processFillForPoint(mFillMethod, CPoint2D(x, y));
			glVertex2f(x, y);
		}

		startAngle = endAngle;
		endAngle -= M_PI/2;
		step = (startAngle - endAngle) / ((bottomLeftXRadius + bottomLeftYRadius) / 4);
		for (Float32 i = startAngle; i >= endAngle; i -= step)
		{
			Float32 x = rect.x() + bottomLeftXRadius + bottomLeftXRadius * cosf(i);
			Float32 y = rect.y() + rect.height() - bottomLeftYRadius - bottomLeftYRadius * sinf(i);
			processFillForPoint(mFillMethod, CPoint2D(x, y));
			glVertex2f(x, y);
		}
	glEnd();
}

void COpenGLRenderingContext::drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	glBegin(GL_QUADS);
		glColor4f(fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha());
		glVertex2f(rect.x(), rect.y() + rect.height());
		glVertex2f(rect.x(), rect.y());
		glColor4f(toColor.red(), toColor.green(), toColor.blue(), toColor.alpha());
		glVertex2f(rect.x() + rect.width(), rect.y());
		glVertex2f(rect.x() + rect.width(), rect.y() + rect.height());
	glEnd();
}

void COpenGLRenderingContext::drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	glBegin(GL_QUADS);
		glColor4f(fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha());
		glVertex2f(rect.x(), rect.y());
		glVertex2f(rect.x() + rect.width(), rect.y());
		glColor4f(toColor.red(), toColor.green(), toColor.blue(), toColor.alpha());
		glVertex2f(rect.x() + rect.width(), rect.y() + rect.height());
		glVertex2f(rect.x(), rect.y() + rect.height());
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

		glBindTexture(GL_TEXTURE_2D, result[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		size = frame.size();
		glTexImage2D(GL_TEXTURE_2D, 0, format, (GLsizei)size.width(), (GLsizei)size.height(),
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

Bool COpenGLRenderingContext::isExtensionSupported(const char* extension) const
{
	const GLubyte *extensions = NULL;
	const GLubyte *start;

	GLubyte *where, *terminator;
	/* Extension names should not have spaces. */

	where = (GLubyte *) strchr(extension, ' ');

	if (where || *extension == '\0') return false;

	extensions = glGetString(GL_EXTENSIONS);

	/* It takes a bit of care to be fool-proof about parsing the
	OpenGL extensions string. Don't be fooled by sub-strings,
	etc. */

	start = extensions;

	for (;;)
	{
		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where) break;

		terminator = where + strlen(extension);

		if (where == start || *(where - 1) == ' ')
		{
			if (*terminator == ' ' || *terminator == '\0') return true;
		}
		start = terminator;
	}

	return false;
}

	} // namespace le
} // namespace sokira
