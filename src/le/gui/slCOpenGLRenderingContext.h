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

		virtual void setLineWidth(Float32 width);

		virtual void unsetTexture();

		virtual void pushClippingRect(const CRectangle& rect);
		virtual void popClippingRect();

		// Geometry
		virtual void drawText(const CString& text, const CPoint2D& position);
		virtual void drawSegment(const CSegment2D& segment);
		virtual void drawSegment(const CSegment3D& segment);
		virtual void drawConvexPolygon(const CPolygon& poly);
		virtual void drawRect(const CRectangle& rect);
		virtual void drawWireRect(const CRectangle& rect);
		virtual void drawBox(const CBox& box);
		virtual void drawWireBox(const CBox& box);

		virtual void drawRoundedRect(const CRectangle& rect,
			Float32 topLeftXRadius, Float32 topLeftYRadius,
			Float32 topRightXRadius, Float32 topRightYRadius,
			Float32 bottomLeftXRadius, Float32 bottomLeftYRadius,
			Float32 bottomRightXRadius, Float32 bottomRightYRadius);

		virtual void drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect);
		virtual void drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect);

		Bool isExtensionSupported(const char* extensionName) const;

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
