#include <le/core/config/slCompiler.h>

#include <le/gui/slOpenGL.h>
#include <le/core/slCString.h>
#include <le/core/slCData.h>
#include <le/core/slCURL.h>
#include <le/core/slCNumber.h>
#include <le/core/slCIndexSet.h>
#include <le/core/slCCharacterSet.h>
#include <le/core/thread/slCThread.h>
#include <le/core/base/slCImageImpl.hp>
#include <le/gui/base/slCOpenGLTextureImpl.hp>
#include "slCOpenGLRenderingContext.h"
#include <le/core/slCGradient.h>

LE_DEFINE_LINK_MODULE(COpenGLRenderingContext);

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(COpenGLRenderingContext);

static CSize2D createTextureWithBitmapData(COpenGLRenderingContext* context, const CSize2D& size, const UInt8* data, EPixelFormat format, GLuint texture);

COpenGLRenderingContext::COpenGLRenderingContext() :
	mSharedBuffer(NULL),
	mSharedBufferSize(0)
{
	validateCurrentContext();
	//std::cout << "Creating COpenGLRenderingContext" << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glClearStencil(0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glStencilMask(0xFF);

	mFont.setSize(16);
}

COpenGLRenderingContext::~COpenGLRenderingContext()
{
	if (mSharedBuffer) free(mSharedBuffer);
	std::cout << "~COpenGLRenderingContext" << std::endl;
}

void COpenGLRenderingContext::beginDrawing()
{
	validateCurrentContext();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
}

void COpenGLRenderingContext::endDrawing()
{

}

//static void processFillForPoint(const CFillMethod* fill, const CPoint2D& point)
//{
//	if (fill)
//	{
//		CColor color = fill->colorAtPoint(point);
//		glColor4f(color.red(), color.green(), color.blue(), color.alpha());
//	}
//}

////////////////////////////////////////////////////////////////////////////////
// Set color functions

void COpenGLRenderingContext::setLineWidth(Float32 width)
{
	validateCurrentContext();
	glLineWidth(width);
}


////////////////////////////////////////////////////////////////////////////////
// Geometry

struct SGlyphRange : public TSRange<wchar_t, unsigned short>
{
	std::vector<std::pair<Float32, Float32> > glyphPositions;
	GLuint fontTexture;
	CSize2D textureSize;
};

class CFontData : public CObject
{
	public:
		TCIndexSet<SGlyphRange> glyphRanges;

		void generateFontDataForRangeAtIndex(UInt32 index, CFont& font, COpenGLRenderingContext* context)
		{
			SGlyphRange& range = const_cast<SGlyphRange&>(glyphRanges.indexRanges()[index]);
			range.glyphPositions = CFont::CGlyphPositions(range.length, std::make_pair(0.0f, 0.0f));
			CImage image;
			CCharacterSet charSet;
			charSet.addCharactersInRange(range.location, range.length);

			font.getGlyphDataForCharactersInRange(range.location, range.length, image, range.glyphPositions);
			glGenTextures(1, &range.fontTexture);

			CImageFrame frame = image.frameAtIndex(0);
			range.textureSize = createTextureWithBitmapData(context, frame.size(), frame.pixelData(), frame.pixelFormat(), range.fontTexture);
		}
};

static inline CFontData* fontData(COpenGLRenderingContext* context, CFont& font)
{
	CFontData* result = (CFontData*)font.rendererInfo().get();
	if (!result)
	{
		result = new CFontData();
		font.setRendererInfo(result);
	}

	return result;
}

void COpenGLRenderingContext::drawText(const CString& text, const CPoint2D& position)
{
	validateCurrentContext();
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	CFontData* fontInfo = fontData(this, mFont);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	const WChar rangeRadius = 64;

	UInt32 length = text.length();
	Float32 xOffset = 0.0f;
	TCIndexSet<SGlyphRange>& glyphRanges = fontInfo->glyphRanges;
	for (UInt32 i = 0; i < length; ++i)
	{
		WChar ch = text.characterAtIndex(i);

		SInt32 rangeIndex = glyphRanges.indexOfRangeContainingIndex(ch);
		if (rangeIndex == -1)
		{
			WChar firstChar = glyphRanges.indexLessThan(ch);
			if (firstChar == -1 || firstChar < ch - rangeRadius)
			{
				firstChar = ch - rangeRadius;
			}
			WChar lastChar = glyphRanges.indexGreaterThan(ch);
			if (lastChar == -1 || lastChar >= ch + rangeRadius)
			{
				lastChar = ch + rangeRadius;
			}
			SGlyphRange range;
			range.location = firstChar;
			range.length = lastChar - firstChar;
			glyphRanges.addIndexesInRange(range);
			rangeIndex = glyphRanges.indexOfRangeContainingIndex(ch);
			fontInfo->generateFontDataForRangeAtIndex(rangeIndex, mFont, this);
		}

		const SGlyphRange& range = glyphRanges.indexRanges()[rangeIndex];

		GLfloat glyphStart = range.glyphPositions[ch - range.location].first;
		GLfloat glyphWidth = range.glyphPositions[ch - range.location].second;

		Float32 textureWidth = range.textureSize.width();
		Float32 textureHeight = range.textureSize.height();

		GLfloat texCoords[] = {
			glyphStart / textureWidth, 0,
			(glyphStart + glyphWidth) / textureWidth, 0,
			(glyphStart + glyphWidth) / textureWidth, 1,
			glyphStart / textureWidth, 1
		};

		GLfloat vertexes[] = {
			position.x() + xOffset, position.y(),
			position.x() + xOffset + glyphWidth, position.y(),
			position.x() + xOffset + glyphWidth, position.y() + textureHeight,
			position.x() + xOffset, position.y() + textureHeight
		};

		GLuint texture = range.fontTexture;
		glBindTexture(GL_TEXTURE_2D, texture);

		xOffset += glyphWidth;
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		glVertexPointer(2, GL_FLOAT, 0, vertexes);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
}

void drawBoxWithGLPrimitive(const CBox& box, int primitive)
{
	Float32 vertexes[] =
	{
		box.x(), box.y(), box.z(),
		box.x() + box.width(), box.y(), box.z(),
		box.x() + box.width(), box.y() + box.height(), box.z(),
		box.x(), box.y() + box.height(), box.z(),

		box.x(), box.y(), box.z(),
		box.x(), box.y(), box.z() + box.depth(),
		box.x(), box.y() + box.height(), box.z() + box.depth(),
		box.x(), box.y() + box.height(), box.z(),

		box.x(), box.y(), box.z(),
		box.x(), box.y(), box.z() + box.depth(),
		box.x() + box.width(), box.y(), box.z() + box.depth(),
		box.x() + box.width(), box.y(), box.z(),

		box.x(), box.y(), box.z() + box.depth(),
		box.x() + box.width(), box.y(), box.z() + box.depth(),
		box.x() + box.width(), box.y() + box.height(), box.z() + box.depth(),
		box.x(), box.y() + box.height(), box.z() + box.depth(),

		box.x(), box.y(), box.z() + box.depth(),
		box.x(), box.y(), box.z(),
		box.x(), box.y() + box.height(), box.z(),
		box.x(), box.y() + box.height(), box.z() + box.depth(),

		box.x(), box.y() + box.height(), box.z(),
		box.x(), box.y() + box.height(), box.z() + box.depth(),
		box.x() + box.width(), box.y() + box.height(), box.z() + box.depth(),
		box.x() + box.width(), box.y() + box.height(), box.z()
	};

	glVertexPointer(3, GL_FLOAT, 0, vertexes);
	glDrawArrays(primitive, 0, sizeof(vertexes) / sizeof(vertexes[0]) / 3);
}

void COpenGLRenderingContext::drawBox(const CBox& box)
{
	validateCurrentContext();
//	drawBoxWithGLPrimitive(box, GL_QUADS);
}

void COpenGLRenderingContext::drawWireBox(const CBox& box)
{
	validateCurrentContext();
//	glPolygonMode(GL_FRONT, GL_LINE);
//	glPolygonMode(GL_BACK, GL_LINE);
	drawBox(box);
//	glPolygonMode(GL_FRONT, GL_FILL);
//	glPolygonMode(GL_BACK, GL_FILL);
}

static inline GLenum glPrimitiveFromPrimitive(EPrimitiveType primitive)
{
	switch (primitive)
	{
		case ePrimitiveTypePointList: return GL_POINTS;
		case ePrimitiveTypeTriangleList: return GL_TRIANGLES;
		case ePrimitiveTypeTriangleStrip: return GL_TRIANGLE_STRIP;
		case ePrimitiveTypeTriangleFan: return GL_TRIANGLE_FAN;
		case ePrimitiveTypeLineList: return GL_LINES;
		case ePrimitiveTypeLineStrip: return GL_LINE_STRIP;
		default:;
	}
	return 0;
}

template <typename T> struct TSTypeToGLType;
template <> struct TSTypeToGLType<GLfloat> { enum { result = GL_FLOAT }; };
template <> struct TSTypeToGLType<GLbyte> { enum { result = GL_BYTE }; };
template <> struct TSTypeToGLType<GLubyte> { enum { result = GL_UNSIGNED_BYTE }; };

void* COpenGLRenderingContext::sharedBufferOfSize(UInt32 size)
{
	if (size > mSharedBufferSize)
	{
		if (mSharedBuffer) free(mSharedBuffer);
		mSharedBuffer = malloc(size);
		mSharedBufferSize = size;
	}
	return mSharedBuffer;
}

SVertex* COpenGLRenderingContext::sharedVertexBufferOfSize(UInt32 count)
{
	return (SVertex*)sharedBufferOfSize(count * sizeof(SVertex));
}

SColoredVertex* COpenGLRenderingContext::sharedColorVertexBufferOfSize(UInt32 count)
{
	return (SColoredVertex*)sharedBufferOfSize(count * sizeof(SColoredVertex));
}

STexturedVertex* COpenGLRenderingContext::sharedTexturedVertexBufferOfSize(UInt32 count)
{
	return (STexturedVertex*)sharedBufferOfSize(count * sizeof(STexturedVertex));
}

void COpenGLRenderingContext::drawVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive)
{
	validateCurrentContext();
	glVertexPointer(3, TSTypeToGLType<SVertex::TCoord>::result, 0, mSharedBuffer);
	glDrawArrays(glPrimitiveFromPrimitive(primitive), 0, count);
}

void COpenGLRenderingContext::drawColoredVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive)
{
	validateCurrentContext();
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, TSTypeToGLType<SColoredVertex::TCoord>::result, sizeof(SColoredVertex), mSharedBuffer);
	glColorPointer(4, TSTypeToGLType<SColoredVertex::TColorComponent>::result, sizeof(SColoredVertex), ((char*)mSharedBuffer) + sizeof(SColoredVertex::TCoord) * 3);
	glDrawArrays(glPrimitiveFromPrimitive(primitive), 0, count);
	glDisableClientState(GL_COLOR_ARRAY);
}

void COpenGLRenderingContext::drawTexturedVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive)
{
	validateCurrentContext();
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, TSTypeToGLType<STexturedVertex::TCoord>::result, sizeof(STexturedVertex), mSharedBuffer);
	glTexCoordPointer(2, TSTypeToGLType<STexturedVertex::TTextureCoord>::result, sizeof(STexturedVertex), ((char*)mSharedBuffer) + sizeof(STexturedVertex::TCoord) * 3);
	glDrawArrays(glPrimitiveFromPrimitive(primitive), 0, count);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

static inline void setOpenGLColor(const TCColor<UInt8>& color)
{
	glColor4ub(color.red(), color.green(), color.blue(), color.alpha());
}

static inline void setOpenGLColor(const TCColor<Float32>& color)
{
	glColor4f(color.red(), color.green(), color.blue(), color.alpha());
}

void COpenGLRenderingContext::setFillMethod(const CFillMethod* fillMethod)
{
	if (fillMethod)
	{
		if (fillMethod->isSolid())
		{
			validateCurrentContext();
			CColor color = fillMethod->colorAtPoint(CPoint2D());
			setOpenGLColor(color);
			fillMethod = NULL;
		}
	}
	CRenderingContext::setFillMethod(fillMethod);
}

static CSize2D createTextureWithBitmapData(COpenGLRenderingContext* context, const CSize2D& size, const UInt8* data, EPixelFormat format, GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	GLsizei width = (GLsizei)size.width();
	GLsizei height = (GLsizei)size.height();

	if ((!CNumber::isPowerOf2((unsigned)width) || !CNumber::isPowerOf2((unsigned)height)) && !context->isExtensionSupported("ARB_texture_non_power_of_two"))
	{
	//	std::cout << "ERROR! Texture is not power of 2!" << std::endl;
		//LE_ASSERT(false);
	}

	GLenum destFormat = 0;
	GLenum srcFormat = 0;
	switch (format)
	{
		case ePixelFormatGrayscale:
			{
				UInt8* newData = new UInt8[width * height * 2];
				for (UInt32 i = 0; i < (UInt32)width * height; ++i)
				{
					newData[i * 2] = data[i];
					newData[i * 2 + 1] = data[i];
				}
				data = newData;
				destFormat = GL_LUMINANCE_ALPHA;
				srcFormat = GL_LUMINANCE_ALPHA;
				break;
			}
		case ePixelFormatRGBA:
			srcFormat = destFormat = GL_RGBA;
			break;
		case ePixelFormatRGB:
			srcFormat = destFormat = GL_RGB;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height,
				 0, srcFormat, GL_UNSIGNED_BYTE, data);

	if (format == ePixelFormatGrayscale) delete [] data;
	return CSize2D(width, height);
}

CTextureImpl* COpenGLRenderingContext::createTextureImpl(const CTexture* texture, const CImageImpl* image)
{
	validateCurrentContext();
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
		size = frame.size();
		createTextureWithBitmapData(this, frame.size(), frame.pixelData(), frame.pixelFormat(), result[i]);
	}
	return new COpenGLTextureImpl(result, image->frameCount(), size);
}

void COpenGLRenderingContext::setTextureImpl(const CTextureImpl* textureImpl)
{
	validateCurrentContext();
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
	validateCurrentContext();
	glDisable(GL_TEXTURE_2D);
}

void COpenGLRenderingContext::pushClippingRect(const CRectangle& rect)
{
	validateCurrentContext();

#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	GLfloat vp[4];
	glGetFloatv(GL_VIEWPORT, vp);

	glMatrixMode(GL_PROJECTION);
	glPushAttrib(GL_VIEWPORT_BIT);
	glPushMatrix();

	glViewport(rect.x(), vp[3] - (rect.y() + rect.height()), rect.width(), rect.height());
	glLoadIdentity();
	glOrtho(rect.x(), rect.x() + rect.width(), rect.y() + rect.height(), rect.y(), -1, 1);
#endif
}

void COpenGLRenderingContext::popClippingRect()
{
	validateCurrentContext();

#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
#endif
}

void COpenGLRenderingContext::beginStencil()
{
	validateCurrentContext();
	glEnable(GL_STENCIL_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_NEVER, 1, 0xFF);
	glStencilOp(GL_REPLACE, GL_KEEP, GL_KEEP);  // draw 1s on test fail (always)

	// draw stencil pattern
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);
}

void COpenGLRenderingContext::endStencil()
{
	validateCurrentContext();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0x00);

	// draw only where stencil's value is 1
	glStencilFunc(GL_EQUAL, 1, 0xFF);
}

void COpenGLRenderingContext::disableStencil()
{
	glDisable(GL_STENCIL_TEST);
}

Float32 COpenGLRenderingContext::levelOfDetail() const
{
	validateCurrentContext();
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	GLfloat r0 = m[0] + m[4] + m[8] + m[12];
	GLfloat r1 = m[1] + m[5] + m[9] + m[13];
	GLfloat r2 = m[2] + m[6] + m[10] + m[14];
	GLfloat r3 = m[3] + m[7] + m[11] + m[15];

	glGetFloatv(GL_PROJECTION_MATRIX, m);
	GLfloat n0 = m[0] * r0 + m[4] * r1 + m[8] * r2 + m[12] * r3;
	GLfloat n1 = m[1] * r0 + m[5] * r1 + m[9] * r2 + m[13] * r3;
	GLfloat n2 = m[2] * r0 + m[6] * r1 + m[10] * r2 + m[14] * r3;
	GLfloat n3 = m[3] * r0 + m[7] * r1 + m[11] * r2 + m[15] * r3;

	if (n1 > n0) n0 = n1;
	if (n2 > n0) n0 = n2;
	if (n3 > n0) n0 = n3;

	return r1;
}

void COpenGLRenderingContext::getTransform(CAffineTransform3D& transform) const
{
	validateCurrentContext();
	GLint matrixMode;
	glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
	GLenum matrix = 0;
	switch (matrixMode)
	{
		case GL_MODELVIEW:
			matrix = GL_MODELVIEW_MATRIX;
			break;
		case GL_PROJECTION:
			matrix = GL_PROJECTION_MATRIX;
			break;
		case GL_TEXTURE:
			matrix = GL_TEXTURE_MATRIX;
			break;
		default:;
	}

	glGetFloatv(matrix, reinterpret_cast<Float32*>(&transform));
}

void COpenGLRenderingContext::setTransform(const CAffineTransform3D& transform) const
{
	validateCurrentContext();
	glLoadMatrixf(reinterpret_cast<const Float32*>(&transform));
}

Bool COpenGLRenderingContext::isExtensionSupported(const char* extension) const
{
	validateCurrentContext();
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

inline void COpenGLRenderingContext::validateCurrentContext() const
{
#ifdef LE_TLS_STATIC_DEFINITION
	LE_TLS_STATIC_DEFINITION(const COpenGLRenderingContext*, currentContext = NULL);
#else
	static const COpenGLRenderingContext* currentContext = NULL;
#endif
	if (currentContext != this)
	{
		std::cout << "Switching context\n";
		makeCurrentContext();
		currentContext = this;
	}
}

void COpenGLRenderingContext::makeCurrentContext() const
{

}

	} // namespace le
} // namespace sokira
