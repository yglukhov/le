#include "slCGradient.h"


namespace sokira
{
	namespace le
	{


CColor CFillMethod::colorAtPoint(const CPoint2D& point) const
{
	return CColor();
}

Bool CFillMethod::isSolid() const
{
	return true;
}

Bool CFillMethod::isTextured() const
{
	return false;
}
//
//CTexture CFillMethod::texture() const
//{
//	return CTexture();
//}

CColorFill::CColorFill(const CColor& color) :
	mColor(color)
{

}

CColor CColorFill::colorAtPoint(const CPoint2D& point) const
{
	return mColor;
}

CPoint2D CFillMethod::uvForPoint(const CPoint2D& point) const
{
	return CPoint2D();
}

CGradient::CGradient()
{

}

CGradient::CGradient(const CColor& startColor, const CColor& endColor)
{
	addColor(startColor, 0.0f);
	addColor(endColor, 1.0f);
}

void CGradient::addColor(const CColor& color, Float32 position)
{
	if (position <= 1.0f)
	{
		TColors::iterator it = mColors.begin();
		for (; it != mColors.end(); ++it)
		{
			if (it->first > position) break;
		}

		mColors.insert(it, std::make_pair(position, color));
	}
}

CColor CGradient::colorAtPoint(const CPoint2D& point) const
{
	return CColor();
}

Bool CGradient::isSolid() const
{
	return mColors.size() > 1;
}

CLinearGradient::CLinearGradient() :
	mDirection(0.0f)
{

}

CLinearGradient::CLinearGradient(const CColor& startColor, const CColor& endColor) :
	CGradient(startColor, endColor),
	mDirection(0.0f)
{

}

void CLinearGradient::setRectangle(const CRectangle& rect)
{
	mRect = rect;
}

void CLinearGradient::setDirection(Float32 degrees)
{
	mDirection = degrees;
}

CColor CLinearGradient::colorAtPoint(const CPoint2D& point) const
{
	return CColor();
}

CRadialGradient::CRadialGradient() :
	mRadius(1.0f)
{

}

CRadialGradient::CRadialGradient(const CColor& startColor, const CColor& endColor) :
	CGradient(startColor, endColor),
	mRadius(1.0f)
{

}

void CRadialGradient::setCenter(const CPoint2D& point)
{
	mCenter = point;
}

void CRadialGradient::setRadius(Float32 radius)
{
	mRadius = radius;
}

CColor CRadialGradient::colorAtPoint(const CPoint2D& point) const
{
	return CColor();
}

	} // namespace le
} // namespace sokira
