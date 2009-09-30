#if !defined SL_LE_gui_slCOpenGLRenderingContext_h
#define SL_LE_gui_slCOpenGLRenderingContext_h

#include "slCRenderingContext.h"

namespace sokira
{
	namespace le
	{
		
class COpenGLRenderingContext : public CRenderingContext
{
	public:
		COpenGLRenderingContext();
		~COpenGLRenderingContext();

		virtual void setColor(SInt8 r, SInt8 g, SInt8 b);
		virtual void setColor(SInt8 r, SInt8 g, SInt8 b, SInt8 a);
		virtual void setColor(const SInt8* vector);
		virtual void setColorWithAlpha(const SInt8* vector);
		virtual void setColor(UInt8 r, UInt8 g, UInt8 b);
		virtual void setColor(UInt8 r, UInt8 g, UInt8 b, UInt8 a);
		virtual void setColor(const UInt8* vector);
		virtual void setColorWithAlpha(const UInt8* vector);
		virtual void setColor(SInt16 r, SInt16 g, SInt16 b);
		virtual void setColor(SInt16 r, SInt16 g, SInt16 b, SInt16 a);
		virtual void setColor(const SInt16* vector);
		virtual void setColorWithAlpha(const SInt16* vector);
		virtual void setColor(UInt16 r, UInt16 g, UInt16 b);
		virtual void setColor(UInt16 r, UInt16 g, UInt16 b, UInt16 a);
		virtual void setColor(const UInt16* vector);
		virtual void setColorWithAlpha(const UInt16* vector);
		virtual void setColor(SInt32 r, SInt32 g, SInt32 b);
		virtual void setColor(SInt32 r, SInt32 g, SInt32 b, SInt32 a);
		virtual void setColor(const SInt32* vector);
		virtual void setColorWithAlpha(const SInt32* vector);
		virtual void setColor(UInt32 r, UInt32 g, UInt32 b);
		virtual void setColor(UInt32 r, UInt32 g, UInt32 b, UInt32 a);
		virtual void setColor(const UInt32* vector);
		virtual void setColorWithAlpha(const UInt32* vector);
		virtual void setColor(Float32 r, Float32 g, Float32 b);
		virtual void setColor(Float32 r, Float32 g, Float32 b, Float32 a);
		virtual void setColor(const Float32* vector);
		virtual void setColorWithAlpha(const Float32* vector);
		virtual void setColor(Float64 r, Float64 g, Float64 b);
		virtual void setColor(Float64 r, Float64 g, Float64 b, Float64 a);
		virtual void setColor(const Float64* vector);
		virtual void setColorWithAlpha(const Float64* vector);

		virtual void setLineWidth(Float32 width);

		virtual void unsetTexture();

		// Geometry
		virtual void drawText(const CString& text, const CPoint2D& position);
		virtual void drawSegment(const CSegment2D& segment);
		virtual void drawSegment(const CSegment3D& segment);
		virtual void drawRect(const CRectangle& rect);
		virtual void drawWireRect(const CRectangle& rect);
		virtual void drawBox(const CBox& box);
		virtual void drawWireBox(const CBox& box);

	protected:
		virtual CTextureImpl* createTextureImpl(const CTexture* texture, const CImageImpl* imageImpl);
		virtual void setTextureImpl(const CTextureImpl* textureImpl);

	private:
		UInt32 makeFont();
		UInt32 mFontOffset;
};
		
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCOpenGLRenderingContext_h
