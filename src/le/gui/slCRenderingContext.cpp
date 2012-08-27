#include <le/core/base/slCImageImpl.hp>
#include <le/core/slCGradient.h>

#include "slCRenderingContext.h"
#include "slCTexture.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CRenderingContext);

CRenderingContext::CRenderingContext() :
	mFillMethod(NULL)
{

}

CRenderingContext::~CRenderingContext()
{
	if (mFillMethod) mFillMethod->release();
}

void CRenderingContext::beginDrawing() { }
void CRenderingContext::endDrawing() { }

		
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
void CRenderingContext::drawSegment(const CSegment2D& segment)
{
	SVertex* vertexes = sharedVertexBufferOfSize(2);
	vertexes[0].setPoint(segment.a()); vertexes[1].setPoint(segment.b());
	drawVertexesInSharedBuffer(2, ePrimitiveTypeLineList);
}

void CRenderingContext::drawSegment(const CSegment3D& segment)
{
	SVertex* vertexes = sharedVertexBufferOfSize(2);
	vertexes[0].setPoint(segment.a()); vertexes[1].setPoint(segment.b());
	drawVertexesInSharedBuffer(2, ePrimitiveTypeLineList);
}

void CRenderingContext::drawConvexPolygon(const CPolygon& poly)
{
	const CPolygon::TPoints& points = poly.points();
	SVertex* vertexes = sharedVertexBufferOfSize(points.size());
	SVertex* pV = vertexes;

	for (CPolygon::TPoints::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		pV->setPoint(*it);
		++pV;
	}

	drawVertexesInSharedBuffer(points.size(), ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawRect(const CRectangle& rect)
{
	SVertex* vertexes = sharedVertexBufferOfSize(4);
	vertexes[0].setPoint(rect.bottomLeft());
	vertexes[1].setPoint(rect.topLeft());
	vertexes[2].setPoint(rect.topRight());
	vertexes[3].setPoint(rect.bottomRight());
	drawVertexesInSharedBuffer(4, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawWireRect(const CRectangle& rect)
{
	SVertex* vertexes = sharedVertexBufferOfSize(5);
	vertexes[0].setPoint(rect.bottomLeft());
	vertexes[1].setPoint(rect.topLeft());
	vertexes[2].setPoint(rect.topRight());
	vertexes[3].setPoint(rect.bottomRight());
	vertexes[4].setPoint(rect.bottomLeft());
	drawVertexesInSharedBuffer(5, ePrimitiveTypeLineStrip);
}

void CRenderingContext::drawBox(const CBox& box) { }
void CRenderingContext::drawWireBox(const CBox& box) { }

static UInt32 vertexCountForRoundRect(Float32 topLeftXRadius, Float32 topLeftYRadius,
									  Float32 topRightXRadius, Float32 topRightYRadius,
									  Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
									  Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
	Float32 startAngle = M_PI;
	Float32 endAngle = M_PI / 2;

	UInt32 result = 0;

	Float32 step = (startAngle - endAngle) / ((topLeftXRadius + topLeftYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		++result;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((topRightXRadius + topRightYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		++result;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((bottomRightXRadius + bottomRightYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		++result;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((bottomLeftXRadius + bottomLeftYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		++result;
	}

	return result;
}

static void fillVertexArrayForRoundedRect(SVertex* vertexes, const CRectangle& rect,
								   Float32 topLeftXRadius, Float32 topLeftYRadius,
								   Float32 topRightXRadius, Float32 topRightYRadius,
								   Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
								   Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
	SVertex* pV = vertexes;
	Float32 startAngle = M_PI;
	Float32 endAngle = M_PI / 2;

	Float32 step = (startAngle - endAngle) / ((topLeftXRadius + topLeftYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		pV->x = rect.x() + topLeftXRadius + topLeftXRadius * cosf(i);
		pV->y = rect.y() + topLeftYRadius - topLeftYRadius * sinf(i);
		pV->z = 0;
		++pV;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((topRightXRadius + topRightYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		pV->x = rect.x() + rect.width() - topRightXRadius + topRightXRadius * cosf(i);
		pV->y = rect.y() + topRightYRadius - topRightYRadius * sinf(i);
		pV->z = 0;
		++pV;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((bottomRightXRadius + bottomRightYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		pV->x = rect.x() + rect.width() - bottomRightXRadius + bottomRightXRadius * cosf(i);
		pV->y = rect.y() + rect.height() - bottomRightYRadius - bottomRightYRadius * sinf(i);
		pV->z = 0;
		++pV;
	}

	startAngle = endAngle;
	endAngle -= M_PI/2;
	step = (startAngle - endAngle) / ((bottomLeftXRadius + bottomLeftYRadius) / 4);
	for (Float32 i = startAngle; i >= endAngle; i -= step)
	{
		pV->x = rect.x() + bottomLeftXRadius + bottomLeftXRadius * cosf(i);
		pV->y = rect.y() + rect.height() - bottomLeftYRadius - bottomLeftYRadius * sinf(i);
		pV->z = 0;
		++pV;
	}
}

void CRenderingContext::drawRoundedRect(const CRectangle& rect,
	Float32 topLeftXRadius, Float32 topLeftYRadius,
	Float32 topRightXRadius, Float32 topRightYRadius,
	Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
	Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
	UInt32 vertexCount = vertexCountForRoundRect(topLeftXRadius, topLeftYRadius,
		topRightXRadius, topRightYRadius, bottomLeftXRadius, bottomLeftYRadius,
		bottomRightXRadius, bottomRightYRadius);
	SVertex* vertexes = sharedVertexBufferOfSize(vertexCount);
	fillVertexArrayForRoundedRect(vertexes, rect, topLeftXRadius, topLeftYRadius,
		topRightXRadius, topRightYRadius, bottomLeftXRadius, bottomLeftYRadius,
		bottomRightXRadius, bottomRightYRadius);
	drawVertexesInSharedBuffer(vertexCount, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawWireRoundedRect(const CRectangle& rect,
	Float32 topLeftXRadius, Float32 topLeftYRadius,
	Float32 topRightXRadius, Float32 topRightYRadius,
	Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
	Float32 bottomRightXRadius, Float32 bottomRightYRadius)
{
	UInt32 vertexCount = vertexCountForRoundRect(topLeftXRadius, topLeftYRadius,
		topRightXRadius, topRightYRadius, bottomLeftXRadius, bottomLeftYRadius,
		bottomRightXRadius, bottomRightYRadius) + 1;
	SVertex* vertexes = sharedVertexBufferOfSize(vertexCount);
	fillVertexArrayForRoundedRect(vertexes, rect, topLeftXRadius, topLeftYRadius,
		topRightXRadius, topRightYRadius, bottomLeftXRadius, bottomLeftYRadius,
		bottomRightXRadius, bottomRightYRadius);
	vertexes[vertexCount - 1] = vertexes[0];
	drawVertexesInSharedBuffer(vertexCount, ePrimitiveTypeLineStrip);
}

void CRenderingContext::drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	SColoredVertex* vertexes = sharedColorVertexBufferOfSize(4);
	vertexes[0].setPoint(rect.bottomLeft()); vertexes[0].setColor(fromColor);
	vertexes[1].setPoint(rect.topLeft()); vertexes[1].setColor(fromColor);
	vertexes[2].setPoint(rect.topRight()); vertexes[2].setColor(toColor);
	vertexes[3].setPoint(rect.bottomRight()); vertexes[3].setColor(toColor);
	drawColoredVertexesInSharedBuffer(4, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect)
{
	SColoredVertex* vertexes = sharedColorVertexBufferOfSize(4);
	vertexes[0].setPoint(rect.topLeft()); vertexes[0].setColor(fromColor);
	vertexes[1].setPoint(rect.topRight()); vertexes[1].setColor(fromColor);
	vertexes[2].setPoint(rect.bottomRight()); vertexes[2].setColor(toColor);
	vertexes[3].setPoint(rect.bottomLeft()); vertexes[3].setColor(toColor);
	drawColoredVertexesInSharedBuffer(4, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawRadialGradient(const CColor& fromColor, const CColor& toColor, const CPoint2D& center, Float32 radius)
{
	UInt32 numberOfExternalVertexes = numberOfVertexesInArc(2 * M_PI, radius);
	UInt32 numberOfVertexes = numberOfExternalVertexes + 1;
	SColoredVertex* vertexes = sharedColorVertexBufferOfSize(numberOfVertexes);
	SColoredVertex* pV = vertexes;

	pV->setPoint(center);
	pV->setColor(fromColor);

	++pV;

	for (UInt32 i = 0; i < numberOfExternalVertexes; ++i)
	{
		SVertex::TCoord angle = i * 2 * M_PI / (numberOfExternalVertexes - 1);
		pV->x = center.x() + radius * cosf(angle);
		pV->y = center.y() + radius * sinf(angle);
		pV->z = 0;
		pV->setColor(toColor);
		++pV;
	}

	drawColoredVertexesInSharedBuffer(numberOfVertexes, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawRingGradient(const CColor& fromColor, const CColor& toColor, const CPoint2D& center, Float32 innerRadius, Float32 outerRadius)
{
	UInt32 numberOfExternalVertexes = numberOfVertexesInArc(2 * M_PI, outerRadius);
	UInt32 numberOfVertexes = numberOfExternalVertexes * 2;
	SColoredVertex* vertexes = sharedColorVertexBufferOfSize(numberOfVertexes);
	SColoredVertex* pV = vertexes;

	typedef SVertex::TCoord TCoord;
	TCoord angleStep = 2 * M_PI / (numberOfExternalVertexes - 1);

	for (UInt32 i = 0; i < numberOfExternalVertexes; ++i)
	{
		TCoord angle = i * angleStep;
		TCoord cosinus = cosf(angle);
		TCoord sinus = sinf(angle);
		pV->x = center.x() + innerRadius * cosinus;
		pV->y = center.y() + innerRadius * sinus;
		pV->z = 0.0f;

		pV->setColor(fromColor);
		++pV;

		pV->x = center.x() + outerRadius * cosinus;
		pV->y = center.y() + outerRadius * sinus;
		pV->z = 0.0f;

		pV->setColor(toColor);
		++pV;
	}
	drawColoredVertexesInSharedBuffer(numberOfVertexes, ePrimitiveTypeTriangleStrip);
}


void CRenderingContext::drawCircle(const CPoint2D& center, Float32 radius)
{
	UInt32 numberOfVertexes = numberOfVertexesInArc(2 * M_PI, radius);
	SVertex* vertexes = sharedVertexBufferOfSize(numberOfVertexes);
	SVertex* pV = vertexes;

	SVertex::TCoord angleStep = 2 * M_PI / numberOfVertexes;
	
	for (UInt32 i = 0; i < numberOfVertexes; ++i)
	{
		SVertex::TCoord angle = i * angleStep;
		pV->x = center.x() + radius * cosf(angle);
		pV->y = center.y() + radius * sinf(angle);
		pV->z = 0;
		++pV;
	}

	drawVertexesInSharedBuffer(numberOfVertexes, ePrimitiveTypeTriangleFan);
}

void CRenderingContext::drawCircularSector(const CPoint2D& center, Float32 radius, Float32 startAngle, Float32 endAngle)
{

}

SVertex* CRenderingContext::sharedVertexBufferOfSize(UInt32 count) { return NULL; }
SColoredVertex* CRenderingContext::sharedColorVertexBufferOfSize(UInt32 count) { return NULL; }

void CRenderingContext::drawVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive) { }
void CRenderingContext::drawColoredVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive) { }

void CRenderingContext::beginStencil() { }
void CRenderingContext::endStencil() { }
void CRenderingContext::disableStencil() { }

Float32 CRenderingContext::levelOfDetail() const
{
	return 1.0f;
}

UInt32 CRenderingContext::numberOfVertexesInArc(Float32 angle, Float32 radius) const
{
	const Float32 pixelsPerSegment = 8;
	return angle * radius / pixelsPerSegment * levelOfDetail();
}

CTextureImpl* CRenderingContext::createTextureImpl(const CTexture* texture, const CImageImpl* imageImpl) { return NULL; }
void CRenderingContext::setTextureImpl(const CTextureImpl* textureImpl) { }

	} // namespace le
} // namespace sokira
