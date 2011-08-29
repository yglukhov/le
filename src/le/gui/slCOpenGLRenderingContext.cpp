#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#define LE_USE_FREETYPE
#endif

#ifdef LE_USE_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#endif

#include <unistd.h>
#include <fcntl.h>

#include <le/gui/slOpenGL.h>
#include <le/core/slCString.h>
#include <le/core/slCData.h>
#include <le/core/slCURL.h>
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
	std::cout << "Creating COpenGLRenderingContext" << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnableClientState(GL_VERTEX_ARRAY);

	mFontOffset = makeFont();
}

COpenGLRenderingContext::~COpenGLRenderingContext()
{
#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	if (mFontOffset) glDeleteLists(mFontOffset, 128);
#endif
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
static GLuint fontTexture;
static Float32* fontTextureCoords; // 128 * 4 * 4
static UInt32 totalFontWidth = 0;

void COpenGLRenderingContext::drawText(const CString& text, const CPoint2D& position)
{
#ifdef LE_USE_FREETYPE
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, fontTexture);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	UInt32 length = text.length();
	Float32 xOffset = 0.0f;
	for (UInt32 i = 0; i < length; ++i)
	{
		NChar character = text.characterAtIndex(i);

		GLfloat* texCoords = fontTextureCoords + character * 8;

		GLfloat width = (texCoords[2] - texCoords[0]) * totalFontWidth;

		GLfloat vertexes[] = {
			position.x() + xOffset, position.y(),
			position.x() + xOffset + width, position.y(),
			position.x() + xOffset + width, position.y() + 16,
			position.x() + xOffset, position.y() + 16
		};

		xOffset += width;
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glVertexPointer(2, GL_FLOAT, 0, vertexes);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
#else
	glRasterPos2f(position.x(), position.y());
	glPushAttrib(GL_LIST_BIT);
	glListBase(mFontOffset);
	glCallLists(text.length(), GL_UNSIGNED_BYTE, (GLubyte *) text.cString());
	glPopAttrib();
#endif	
}

void COpenGLRenderingContext::drawSegment(const CSegment2D& segment)
{
	GLfloat vertexes[] = { segment.a().x(), segment.a().y(), segment.b().x(), segment.b().y() };
	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_LINES, 0, 2);
}

void COpenGLRenderingContext::drawSegment(const CSegment3D& segment)
{
	GLfloat vertexes[] = { segment.a().x(), segment.a().y(), segment.a().z(), segment.b().x(), segment.b().y(), segment.b().z() };
	glVertexPointer(3, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_LINES, 0, 2);
}

void COpenGLRenderingContext::drawConvexPolygon(const CPolygon& poly)
{
	const std::vector<CPoint2D>& points = poly.points();

	GLfloat* vertexes = new GLfloat[points.size() * 2];
	GLfloat* iVertex = vertexes;
	for (std::vector<CPoint2D>::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		*iVertex = it->x();
		++iVertex;
		*iVertex = it->y();
		++iVertex;
	}

	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_TRIANGLE_FAN, 0, points.size());
	delete [] vertexes;
}

void COpenGLRenderingContext::drawRect(const CRectangle& rect)
{
	GLfloat vertexes[] = { rect.minX(), rect.maxY(),
							rect.minX(), rect.minY(),
							rect.maxX(), rect.minY(),
							rect.maxX(), rect.maxY() };
	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void COpenGLRenderingContext::drawWireRect(const CRectangle& rect)
{
	GLfloat vertexes[] = { rect.minX(), rect.maxY(),
		rect.minX(), rect.minY(),
		rect.maxX(), rect.minY(),
		rect.maxX(), rect.maxY() };
	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void COpenGLRenderingContext::drawBox(const CBox& box)
{
//	glBegin(GL_QUADS);
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x() + box.width(), box.y(), box.z());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z());
//	glEnd();
//
//	glBegin(GL_QUADS);
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
//	glEnd();
}

void COpenGLRenderingContext::drawWireBox(const CBox& box)
{
//	glBegin(GL_QUAD_STRIP);
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x() + box.width(), box.y(), box.z());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z());
//	glEnd();
//
//	glBegin(GL_QUAD_STRIP);
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//
//		glVertex3f(box.x(), box.y(), box.z() + box.depth());
//		glVertex3f(box.x(), box.y(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//
//		glVertex3f(box.x(), box.y() + box.height(), box.z());
//		glVertex3f(box.x(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z() + box.depth());
//		glVertex3f(box.x() + box.width(), box.y() + box.height(), box.z());
//	glEnd();
}

void COpenGLRenderingContext::drawRoundedRect(const CRectangle& rect,
	Float32 topLeftXRadius, Float32 topLeftYRadius,
	Float32 topRightXRadius, Float32 topRightYRadius,
	Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
	Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
//	glBegin(GL_TRIANGLE_FAN);
//		Float32 startAngle = M_PI;
//		Float32 endAngle = M_PI / 2;
//
//		Float32 step = (startAngle - endAngle) / ((topLeftXRadius + topLeftYRadius) / 4);
//		for (Float32 i = startAngle; i >= endAngle; i -= step)
//		{
//			Float32 x = rect.x() + topLeftXRadius + topLeftXRadius * cosf(i);
//			Float32 y = rect.y() + topLeftYRadius - topLeftYRadius * sinf(i);
//			processFillForPoint(mFillMethod, CPoint2D(x, y));
//			glVertex2f(x, y);
//		}
//
//		startAngle = endAngle;
//		endAngle -= M_PI/2;
//		step = (startAngle - endAngle) / ((topRightXRadius + topRightYRadius) / 4);
//		for (Float32 i = startAngle; i >= endAngle; i -= step)
//		{
//			Float32 x = rect.x() + rect.width() - topRightXRadius + topRightXRadius * cosf(i);
//			Float32 y = rect.y() + topRightYRadius - topRightYRadius * sinf(i);
//			processFillForPoint(mFillMethod, CPoint2D(x, y));
//			glVertex2f(x, y);
//		}
//
//		startAngle = endAngle;
//		endAngle -= M_PI/2;
//		step = (startAngle - endAngle) / ((bottomRightXRadius + bottomRightYRadius) / 4);
//		for (Float32 i = startAngle; i >= endAngle; i -= step)
//		{
//			Float32 x = rect.x() + rect.width() - bottomRightXRadius + bottomRightXRadius * cosf(i);
//			Float32 y = rect.y() + rect.height() - bottomRightYRadius - bottomRightYRadius * sinf(i);
//			processFillForPoint(mFillMethod, CPoint2D(x, y));
//			glVertex2f(x, y);
//		}
//
//		startAngle = endAngle;
//		endAngle -= M_PI/2;
//		step = (startAngle - endAngle) / ((bottomLeftXRadius + bottomLeftYRadius) / 4);
//		for (Float32 i = startAngle; i >= endAngle; i -= step)
//		{
//			Float32 x = rect.x() + bottomLeftXRadius + bottomLeftXRadius * cosf(i);
//			Float32 y = rect.y() + rect.height() - bottomLeftYRadius - bottomLeftYRadius * sinf(i);
//			processFillForPoint(mFillMethod, CPoint2D(x, y));
//			glVertex2f(x, y);
//		}
//	glEnd();
}

void COpenGLRenderingContext::drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	GLfloat colors[] = {
		fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha(),
		fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha(),
		toColor.red(), toColor.green(), toColor.blue(), toColor.alpha(),
		toColor.red(), toColor.green(), toColor.blue(), toColor.alpha() };
	GLfloat vertexes[] = {
		rect.x(), rect.y() + rect.height(),
		rect.x(), rect.y(),
		rect.x() + rect.width(), rect.y(),
		rect.x() + rect.width(), rect.y() + rect.height() };

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_COLOR_ARRAY);
}

void COpenGLRenderingContext::drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	GLfloat colors[] = {
		fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha(),
		fromColor.red(), fromColor.green(), fromColor.blue(), fromColor.alpha(),
		toColor.red(), toColor.green(), toColor.blue(), toColor.alpha(),
		toColor.red(), toColor.green(), toColor.blue(), toColor.alpha() };
	GLfloat vertexes[] = {
		rect.x(), rect.y(),
		rect.x() + rect.width(), rect.y(),
		rect.x() + rect.width(), rect.y() + rect.height(),
		rect.x(), rect.y() + rect.height() };

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_COLOR_ARRAY);
}

void COpenGLRenderingContext::setFillMethod(const CFillMethod* fillMethod)
{
	if (fillMethod)
	{
		if (fillMethod->isSolid())
		{
			CColor color = fillMethod->colorAtPoint(CPoint2D());
			glColor4f(color.red(), color.green(), color.blue(), color.alpha());
			fillMethod = NULL;
		}
	}
	CRenderingContext::setFillMethod(fillMethod);
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
#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
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
#endif
}

void COpenGLRenderingContext::popClippingRect()
{
#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
#endif
}


#ifdef LE_USE_FREETYPE

static FT_Error ftCreateFace(FT_Library freeType, FT_Face* face, const CData& data, UInt32 fontHeight)
{
	if (FT_New_Memory_Face(freeType, (const FT_Byte*)data.data(), data.length(), 1, face))
	{
		std::cout << "ERROR LOADING FACE" << std::endl;
	}
	
	if (FT_Set_Char_Size(*face, fontHeight * 64, 0, 72, 72))
	{
		std::cout << "ERROR SETTING SIZE" << std::endl;
	}
	
	//	if (FT_Set_Pixel_Sizes(face, 8, 13))
	//	{
	//		std::cout << "ERROR SETTING SIZE" << std::endl;
	//	}
	return 0;
}

static UInt32 createFreeTypeFont()
{
	CString characters = CString::createWithCharacterRange('A', 26);
	characters += CString::createWithCharacterRange('a', 26);
	characters += CString::createWithCharacterRange('0', 10);
	characters += " .:;\\/|{}()[]!@#$%^&*-+=?<>'\"~";

	FT_Library freeType;
	FT_Init_FreeType(&freeType);
	FT_Face face;

	UInt32 fontHeight = 16;

	CData fontData = CData::createWithContentsOfURL(CURL("/System/Library/Fonts/LucidaGrande.ttc"));

	if (ftCreateFace(freeType, &face, fontData, fontHeight))
	{
		std::cout << "ERROR LOADING FACE" << std::endl;
	}

	UInt32 length = characters.length();
	fontTextureCoords = new GLfloat[length * 8];

	// Calculate total font width

	totalFontWidth = 0;

	int maxBitmapTop = 0;
	for (UInt32 i = 0; i < length; ++i)
	{
		FT_ULong character = characters.characterAtIndex(i);
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR LOADING CHAR: " << (char)character << std::endl;
		}

		totalFontWidth += face->glyph->advance.x / 64;
		if (face->glyph->bitmap_top > maxBitmapTop)
		{
			maxBitmapTop = face->glyph->bitmap_top;
		}
	}

	FT_Done_Face(face);
	if (ftCreateFace(freeType, &face, fontData, fontHeight))
	{
		std::cout << "ERROR LOADING FACE2" << std::endl;
	}
	
	if (totalFontWidth > 1024)
	{
		if (totalFontWidth > 2048)
		{
			std::cout << "Total font width too big" << std::endl;
		}
		else
		{
			totalFontWidth = 2048;
		}
	}
	else
	{
		totalFontWidth = 1024;
	}

	UInt32 componentCount = 2;
	GLbyte* fontTextureData = (GLbyte*)malloc(totalFontWidth * fontHeight * componentCount);
	memset(fontTextureData, 0, totalFontWidth * fontHeight * componentCount);
	UInt32 currentXOffset = 0;

	for (UInt32 i = 0; i < length; ++i)
	{
		FT_ULong character = characters.characterAtIndex(i);
		FT_Error err = FT_Load_Char(face, character, FT_LOAD_RENDER);
		if (err)
		{
			std::cout << "ERROR LOADING CHAR \"" << (char)character << "\":" << err << std::endl;
		}

		FT_GlyphSlot slot = face->glyph;
		FT_Bitmap* bitmap = &slot->bitmap;

		for (int y = 0; y < bitmap->rows; ++y)
		{
			for (int x = 0; x < bitmap->width; ++x)
			{
				UInt8 pixel = *(bitmap->buffer + y * bitmap->pitch + x);

				// Compute destination pixel coordinate
				int destX = currentXOffset + x;
				int destY = maxBitmapTop - slot->bitmap_top + y;

				// Write pixel to dest xy
				GLbyte* destPixel = fontTextureData + (destY * totalFontWidth + destX) * componentCount;
				*(destPixel) = pixel;
				*(destPixel + 1) = pixel;
			}
		}

		UInt32 glyphWidth = slot->advance.x / 64;

		*(fontTextureCoords + character * 8 + 0) = (Float32)currentXOffset / totalFontWidth;
		*(fontTextureCoords + character * 8 + 1) = 0.0f;

		*(fontTextureCoords + character * 8 + 2) = (Float32)(currentXOffset + glyphWidth) / totalFontWidth;
		*(fontTextureCoords + character * 8 + 3) = 0.0f;

		*(fontTextureCoords + character * 8 + 4) = (Float32)(currentXOffset + glyphWidth) / totalFontWidth;
		*(fontTextureCoords + character * 8 + 5) = 1.0f;

		*(fontTextureCoords + character * 8 + 6) = (Float32)currentXOffset / totalFontWidth;
		*(fontTextureCoords + character * 8 + 7) = 1.0f;

		currentXOffset += glyphWidth;
		if (currentXOffset > totalFontWidth)
		{
			std::cout << "ERROR!! Total font widths exceeded." << std::endl;
		}
	}

	glGenTextures(1, &fontTexture);
	glBindTexture(GL_TEXTURE_2D, fontTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, totalFontWidth, fontHeight,
				 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, fontTextureData);

	free(fontTextureData);

	FT_Done_Face(face);
	FT_Done_FreeType(freeType);

	return 0;
}
#else // LE_USE_FREETYPE

static UInt32 createInlineFont()
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	return 0;
#else
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	GLubyte letters[][13] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36}, 
		{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18}, 
		{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70}, 
		{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e}, 
		{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c}, 
		{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30}, 
		{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03}, 
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c}, 
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18}, 
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff}, 
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e}, 
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06}, 
		{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60}, 
		{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e}, 
		{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00}, 
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
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}, 
		{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c}, 
		{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60}, 
		{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18}, 
		{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70}, 
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03}, 
		{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e}, 
		{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00}, 
		{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00}, 
		{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0}, 
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78}, 
		{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
		{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00}, 
		{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00}, 
		{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f}, 
		{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, 
		{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0}, 
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00} 	};

	UInt32 fontOffset = glGenLists (128);
	for (GLuint i = 32; i < 127; i++)
	{
		glNewList(i + fontOffset, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i-32]);
		glEndList();
	}

	return fontOffset;
#endif
}

#endif // LE_USE_FREETYPE

UInt32 COpenGLRenderingContext::makeFont()
{
#ifdef LE_USE_FREETYPE
	return createFreeTypeFont();
#else
	return createInlineFont();
#endif
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
