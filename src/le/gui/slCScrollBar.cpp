#include "slCScrollBar.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScrollBar);

CScrollBar::CScrollBar() :
	mHorizontal(true),
	mPosition(0)
{

}

CScrollBar::CScrollBar(const CRectangle& rect, Bool horizontal) :
	CControl(rect),
	mHorizontal(horizontal),
	mPosition(0)
{

}

void CScrollBar::setHorizontal()
{
	mHorizontal = true;
}

void CScrollBar::setVertical()
{
	mHorizontal = false;
}

Bool CScrollBar::isHorizontal() const
{
	return mHorizontal;
}

Float32 CScrollBar::position() const
{
	return mPosition;
}

void CScrollBar::setOnPositionChanged(TOnPositionChanged& function)
{
	mOnPositionChanged = function;
}

Bool CScrollBar::onMouseDown(EMouseButton button, const CPoint2D& point)
{
	if (button == eMouseButtonLeft)
	{
		if (isHorizontal())
		{
	//		CRectangle rect1 = CRectangle(absolutePosition(), size().height(), size().height());
		}
		else
		{
			CRectangle rect1 = CRectangle(absolutePosition().x(), absolutePosition().y(), size().width(), size().width());
			CRectangle rect2 = CRectangle(absolutePosition().x(), absolutePosition().y() + size().height() - size().width(), size().height(), size().height());
			if (rect1.containsPoint(point))
			{
				mPosition -= 0.06;
			}
			else if (rect2.containsPoint(point))
			{
				mPosition += 0.06;
			}
			else
			{
				return false;
			}
		}

		if (mPosition < 0)
			mPosition = 0;
		else if (mPosition > 1)
			mPosition = 1;
		onPositionChanged();
		setNeedsRedraw();
		return true;
	}
	return false;
}

void CScrollBar::draw(const CTheme* theme, CRenderingContext* context) const
{
	theme->drawScrollBar(this, context);
}

void CScrollBar::onPositionChanged()
{
	if (mOnPositionChanged) mOnPositionChanged(this);
}


	} // namespace le
} // namespace sokira
