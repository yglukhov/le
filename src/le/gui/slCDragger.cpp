#if 0

#include "slCDragger.h"
#include "slCControl.h"
#include "slCView.h"

namespace sokira
{
	namespace le
	{

CDragger::CDragger(CControl* controlToDrag, CControl* dragHandler) :
	mControl(controlToDrag), mHandler(dragHandler)
{

}

void CDragger::startDrag(const CPoint& point)
{
	float border = mControl->borderWidth();
	mDragPoint = CPoint(point.x() + border, point.y() + border);
	_currentDragger = this;
}

void CDragger::drag(const CPoint& point)
{
	// new relative coordinates
	CRectangle pRect = mControl->parent()->absoluteRect();
	float x = point.x() - mDragPoint.x() - pRect.x();
	float y = point.y() - mDragPoint.y() - pRect.y();

	// limits, where the child can be placed
	CSize2D mySize = mControl->size();
	float width = pRect.width() - mySize.width();
	float height = pRect.height() - mySize.height();

	// correction of x coord
	if (x < 0)
	{
		x = 0;
	}
	else if (x > width)
	{
		x = width;
	}

	// correction of y coord
	if (y < 0)
	{
		y = 0;
	}
	else if (y > height)
	{
		y = height;
	}

	mControl->setRelativePosition(CPoint(x,y));
}

void CDragger::endDrag()
{
	_currentDragger = NULL;
}

CControl* CDragger::handler()
{
	return mHandler;
}

	} // namespace le
} // namespace sokira

#endif
