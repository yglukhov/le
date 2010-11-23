#include <le/core/base/slCImageImpl.hp>
#include <le/core/slCGradient.h>

#include "slCRenderingContext.h"
#include "slCTexture.h"

namespace sokira
{
	namespace le
	{

CRenderingContext::CRenderingContext() :
	mFillMethod(NULL)
{

}

CRenderingContext::~CRenderingContext()
{
	if (mFillMethod) mFillMethod->release();
}

////////////////////////////////////////////////////////////////////////////////
// Set color functions
//void CRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b) { }
//void CRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b, SInt8 a) { }
//void CRenderingContext::setColor(const SInt8* vector) { }
//void CRenderingContext::setColorWithAlpha(const SInt8* vector) { }
//void CRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b) { }
//void CRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { }
//void CRenderingContext::setColor(const UInt8* vector) { }
//void CRenderingContext::setColorWithAlpha(const UInt8* vector) { }
//void CRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b) { }
//void CRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b, SInt16 a) { }
//void CRenderingContext::setColor(const SInt16* vector) { }
//void CRenderingContext::setColorWithAlpha(const SInt16* vector) { }
//void CRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b) { }
//void CRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b, UInt16 a) { }
//void CRenderingContext::setColor(const UInt16* vector) { }
//void CRenderingContext::setColorWithAlpha(const UInt16* vector) { }
//void CRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b) { }
//void CRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b, SInt32 a) { }
//void CRenderingContext::setColor(const SInt32* vector) { }
//void CRenderingContext::setColorWithAlpha(const SInt32* vector) { }
//void CRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b) { }
//void CRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b, UInt32 a) { }
//void CRenderingContext::setColor(const UInt32* vector) { }
//void CRenderingContext::setColorWithAlpha(const UInt32* vector) { }
//void CRenderingContext::setColor(Float32 r, Float32 g, Float32 b) { }
//void CRenderingContext::setColor(Float32 r, Float32 g, Float32 b, Float32 a) { }
//void CRenderingContext::setColor(const Float32* vector) { }
//void CRenderingContext::setColorWithAlpha(const Float32* vector) { }
//void CRenderingContext::setColor(Float64 r, Float64 g, Float64 b) { }
//void CRenderingContext::setColor(Float64 r, Float64 g, Float64 b, Float64 a) { }
//void CRenderingContext::setColor(const Float64* vector) { }
//void CRenderingContext::setColorWithAlpha(const Float64* vector) { }

void CRenderingContext::setFillMethod(const CFillMethod* fillMethod)
{
	if (mFillMethod) mFillMethod->release();
	mFillMethod = fillMethod;
	if (mFillMethod) mFillMethod->retain();
}

void CRenderingContext::setColor(const CColor& color)
{
	CColorFill* colorFill = new CColorFill(color);
	setFillMethod(colorFill);
	colorFill->release();
}

void CRenderingContext::setLineWidth(Float32 width) { }
void CRenderingContext::setTexture(const CTexture& texture)
{
	if (texture.mImageImpl && !texture.mImpl)
	{
		texture.mImpl = createTextureImpl(&texture, texture.mImageImpl);
		texture.mImageImpl->release();
		texture.mImageImpl = NULL;
	}
	if (texture.mImpl) setTextureImpl(texture.mImpl);
}

void CRenderingContext::unsetTexture() { }

void CRenderingContext::pushClippingRect(const CRectangle& rect) { }
void CRenderingContext::popClippingRect() { }


////////////////////////////////////////////////////////////////////////////////
// Geometry
void CRenderingContext::drawText(const CString& text, const CPoint2D& position) { }
void CRenderingContext::drawSegment(const CSegment2D& segment) { }
void CRenderingContext::drawSegment(const CSegment3D& segment) { }
void CRenderingContext::drawConvexPolygon(const CPolygon& poly) { }
void CRenderingContext::drawRect(const CRectangle& rect) { }
void CRenderingContext::drawWireRect(const CRectangle& rect) { }
void CRenderingContext::drawBox(const CBox& box) { }
void CRenderingContext::drawWireBox(const CBox& box) { }

void CRenderingContext::drawRoundedRect(const CRectangle& rect,
	Float32 topLeftXRadius, Float32 topLeftYRadius,
	Float32 topRightXRadius, Float32 topRightYRadius,
	Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
	Float32 bottomRightXRadius, Float32 bottomRightYRadius) { }

void CRenderingContext::drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect) { }
void CRenderingContext::drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect) { }

CTextureImpl* CRenderingContext::createTextureImpl(const CTexture* texture, const CImageImpl* imageImpl) { return NULL; }
void CRenderingContext::setTextureImpl(const CTextureImpl* textureImpl) { }

	} // namespace le
} // namespace sokira
