#if !defined SL_LE_gui_slCRenderingContext_h
#define SL_LE_gui_slCRenderingContext_h

//#include <le/gui/slConstants.h>
#include <le/core/slCString.h>
#include <le/core/geometry/slTCSegment2D.h>
#include <le/core/geometry/slTCSegment3D.h>
#include <le/core/geometry/slTCRectangle.h>
#include <le/core/slCColor.h>
#include <le/gui/slTypes.h>


namespace sokira
{
	namespace le
	{

class CTexture;
class CTextureImpl;
class CImageImpl;

class CRenderingContext
{
	public:
		virtual ~CRenderingContext();

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

		template <typename TComponent>
		inline void setColor(const TCColor<TComponent>& color)
		{
			setColor(color.red(), color.green(), color.blue(), color.alpha());
		}

		virtual void setLineWidth(Float32 width);

		void setTexture(const CTexture& texture);
		virtual void unsetTexture();

		virtual void pushClippingRect(const CRectangle& rect);
		virtual void popClippingRect();

		// Geometry
		virtual void drawText(const CString& text, const CPoint2D& position);
		virtual void drawSegment(const CSegment2D& segment);
		virtual void drawSegment(const CSegment3D& segment);
		virtual void drawRect(const CRectangle& rect);
		virtual void drawWireRect(const CRectangle& rect);
		virtual void drawBox(const CBox& box);
		virtual void drawWireBox(const CBox& box);

		virtual void drawHorizontalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect);
		virtual void drawVerticalGradient(const CColor& fromColor, const CColor& toColor, const CRectangle& rect);

	protected:
		virtual CTextureImpl* createTextureImpl(const CTexture* texture, const CImageImpl* imageImpl);
		virtual void setTextureImpl(const CTextureImpl* textureImpl);
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCRenderingContext_h
