#if !defined SL_LE_core_slCGradient_hp
#define SL_LE_core_slCGradient_hp

#include <vector>
#include <le/core/geometry/slTCRectangle.h>
#include "slCColor.h"

class CTexture;

namespace sokira
{
	namespace le
	{

class CFillMethod : public CObject
{
	public:
		virtual CColor colorAtPoint(const CPoint2D& point) const;
		virtual Bool isSolid() const;
		virtual Bool isTextured() const;
//		virtual CTexture texture() const;
		virtual CPoint2D uvForPoint(const CPoint2D& point) const;
};

class CColorFill : public CFillMethod
{
	public:
		CColorFill(const CColor& color);
		virtual CColor colorAtPoint(const CPoint2D& point) const;

	private:
		CColor mColor;
};

class CGradient : public CFillMethod
{
	public:
		CGradient();
		CGradient(const CColor& startColor, const CColor& endColor);

		void addColor(const CColor& color, Float32 position);

		virtual CColor colorAtPoint(const CPoint2D& point) const;
		virtual Bool isSolid() const;

	protected:
		typedef std::vector<std::pair<Float32, CColor> > TColors;

		TColors mColors;
};

class CLinearGradient : public CGradient
{
	public:
		CLinearGradient();
		CLinearGradient(const CColor& startColor, const CColor& endColor);

		void setRectangle(const CRectangle& rect);
		virtual CColor colorAtPoint(const CPoint2D& point) const;

		void setDirection(Float32 degrees);

	private:
		CRectangle mRect;
		Float32 mDirection;
};

class CRadialGradient : public CGradient
{
	public:
		CRadialGradient();
		CRadialGradient(const CColor& startColor, const CColor& endColor);

		void setCenter(const CPoint2D& point);
		void setRadius(Float32 radius);

		virtual CColor colorAtPoint(const CPoint2D& point) const;

	private:
		CPoint2D mCenter;
		Float32 mRadius;
};



	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCGradient_hp
