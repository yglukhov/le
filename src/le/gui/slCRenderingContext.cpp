#include "slCRenderingContext.h"

namespace sokira
{
	namespace le
	{		

CRenderingContext::~CRenderingContext() { }

////////////////////////////////////////////////////////////////////////////////
// Set color functions
void CRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b) { }
void CRenderingContext::setColor(SInt8 r, SInt8 g, SInt8 b, SInt8 a) { }
void CRenderingContext::setColor(const SInt8* vector) { }
void CRenderingContext::setColorWithAlpha(const SInt8* vector) { }
void CRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b) { }
void CRenderingContext::setColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { }
void CRenderingContext::setColor(const UInt8* vector) { }
void CRenderingContext::setColorWithAlpha(const UInt8* vector) { }
void CRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b) { }
void CRenderingContext::setColor(SInt16 r, SInt16 g, SInt16 b, SInt16 a) { }
void CRenderingContext::setColor(const SInt16* vector) { }
void CRenderingContext::setColorWithAlpha(const SInt16* vector) { }
void CRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b) { }
void CRenderingContext::setColor(UInt16 r, UInt16 g, UInt16 b, UInt16 a) { }
void CRenderingContext::setColor(const UInt16* vector) { }
void CRenderingContext::setColorWithAlpha(const UInt16* vector) { }
void CRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b) { }
void CRenderingContext::setColor(SInt32 r, SInt32 g, SInt32 b, SInt32 a) { }
void CRenderingContext::setColor(const SInt32* vector) { }
void CRenderingContext::setColorWithAlpha(const SInt32* vector) { }
void CRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b) { }
void CRenderingContext::setColor(UInt32 r, UInt32 g, UInt32 b, UInt32 a) { }
void CRenderingContext::setColor(const UInt32* vector) { }
void CRenderingContext::setColorWithAlpha(const UInt32* vector) { }
void CRenderingContext::setColor(Float32 r, Float32 g, Float32 b) { }
void CRenderingContext::setColor(Float32 r, Float32 g, Float32 b, Float32 a) { }
void CRenderingContext::setColor(const Float32* vector) { }
void CRenderingContext::setColorWithAlpha(const Float32* vector) { }
void CRenderingContext::setColor(Float64 r, Float64 g, Float64 b) { }
void CRenderingContext::setColor(Float64 r, Float64 g, Float64 b, Float64 a) { }
void CRenderingContext::setColor(const Float64* vector) { }
void CRenderingContext::setColorWithAlpha(const Float64* vector) { }

void CRenderingContext::setLineWidth(Float32 width) { }


////////////////////////////////////////////////////////////////////////////////
// Geometry
void CRenderingContext::drawText(const CString& text, const CPoint2D& position) { }
void CRenderingContext::drawSegment(const CSegment2D& segment) { }
void CRenderingContext::drawSegment(const CSegment3D& segment) { }
void CRenderingContext::drawRect(const CRectangle& rect) { }
void CRenderingContext::drawWireRect(const CRectangle& rect) { }
void CRenderingContext::drawBox(const CBox& box) { }
void CRenderingContext::drawWireBox(const CBox& box) { }

	} // namespace le
} // namespace sokira
