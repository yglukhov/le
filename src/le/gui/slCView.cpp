#include "slCView.h"
#include "slCScreen.h"
#include <le/core/auxiliary/slStdExtensions.h>
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CView);

CView::CView(const CRectangle& rect) : CControl(rect)
{
	LE_ENTER_LOG;
}

CView::~CView()
{
	LE_ENTER_LOG;
	clearPointerContainer(mChildren);
}

void CView::addChild(CControl* child)
{
	LE_ENTER_LOG;

	if (child)
	{
		mChildren.push_back(child);

		child->setParent(this);
	}
}

void CView::removeChild(CControl* child)
{
	LE_ENTER_LOG;

	mChildren.remove(child);
	setNeedsRedraw();
}

void CView::draw(const CTheme* theme, CRenderingContext* context) const
{
	LE_ENTER_LOG;
	if (isVisible())
	{
		theme->drawWindow(this, context);
		CControlList::const_iterator end = mChildren.end();
		for (CControlList::const_iterator it = mChildren.begin(); it != end; ++it)
		{
			(*it)->draw(theme, context);
		}
	}
}

Bool CView::onMouse(EKeyCode button, EButtonState state, const CPoint2D& point)
{
	LE_ENTER_LOG;
//	std::cout << "onMouse(" << button << ", " << state << ", (" << point.x() << ", " << point.y() << "))" << std::endl; 
//	if (button == eKeyCodeMouseButtonPrimary) std::cout << "eKeyCodeMouseButtonPrimary" << std::endl;
//	if (button == eKeyCodeMouseButtonSecondary) std::cout << "eKeyCodeMouseButtonSecondary" << std::endl;
//	if (button == eKeyCodeMouseButtonOther) std::cout << "eKeyCodeMouseButtonOther" << std::endl;
//	if (button == eKeyCodeUnknown) std::cout << "eKeyCodeUnknown" << std::endl;
//	if (state == eButtonStateUp) std::cout << "eButtonStateUp" << std::endl;
//	if (state == eButtonStateDown) std::cout << "eButtonStateDown" << std::endl;
//	if (state == eButtonStateUnknown) std::cout << "eButtonStateUnknown" << std::endl;
	if (hitTest(point))
	{
//		std::cout << "hitTest!" << std::endl;
		CControlList children = mChildren;
		CControlList::iterator end = children.end();
		for (CControlList::iterator it = children.begin(); it != end; ++it)
		{
			if ((*it)->onMouse(button, state, point)) return true;
		}

		return performMouse(button, state, point);
	}

	return false;
}

Bool CView::onKeyDown(EKeyCode keyCode)
{
	CControlList children = mChildren;
	for (CControlList::reverse_iterator it = children.rbegin(); it != children.rend(); ++it)
	{
		if ((*it)->isVisible() && (*it)->onKeyDown(keyCode)) return true;
	}

	return CControl::onKeyDown(keyCode);
}

Bool CView::onKeyUp(EKeyCode keyCode)
{
	CControlList children = mChildren;
	for (CControlList::reverse_iterator it = children.rbegin(); it != children.rend(); ++it)
	{
		if ((*it)->isVisible() && (*it)->onKeyUp(keyCode)) return true;
	}

	return CControl::onKeyUp(keyCode);
}

//#define _LOG_AUTORESIZING

#ifdef _LOG_AUTORESIZING
static void logAutoresizingMask(std::ostream& ostream, UInt32 mask)
{
	if ((mask & eAutoResizingFixedMargins) == eAutoResizingFixedMargins)
	{
		std::cout << "eAutoResizingFixedMargins | ";
	}
	else
	{
		if ((mask & eAutoResizingFixedTopLeft) == eAutoResizingFixedTopLeft)
		{
			std::cout << "eAutoResizingFixedTopLeft | ";
		}
		else
		{
			if (mask & eAutoResizingFixedTop)
				std::cout << "eAutoResizingFixedTop | ";
			if (mask & eAutoResizingFixedLeft)
				std::cout << "eAutoResizingFixedLeft | ";
		}
		if (mask & eAutoResizingFixedRight)
			std::cout << "eAutoResizingFixedRight | ";
		if (mask & eAutoResizingFixedBottom)
			std::cout << "eAutoResizingFixedBottom | ";
	}

	if ((mask & eAutoResizingFixedSize) == eAutoResizingFixedSize)
	{
		std::cout << "eAutoResizingFixedSize | ";
	}
	else
	{
		if (mask & eAutoResizingFixedWidth)
			std::cout << "eAutoResizingFixedWidth | ";
		if (mask & eAutoResizingFixedHeight)
			std::cout << "eAutoResizingFixedHeight | ";
	}

}
#endif

void CView::setSize(const CSize2D& toSize)
{
	LE_ENTER_LOG;

	CSize2D fromSize = size();
	CControl::setSize(toSize);

	Float32 deltaWidth = toSize.width() - fromSize.width();
	Float32 deltaHeight = toSize.height() - fromSize.height();

	CControlList::iterator end = mChildren.end();
	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
	{
#ifdef _LOG_AUTORESIZING
		Bool bLog = false;

		if ((*it)->objectClass().name() == "CMainMenu")
		{
			bLog = true;
		}
#endif

		CPoint2D pos = (*it)->relativePosition();
		CRectangle rect = (*it)->absoluteRect();
		CSize2D newSize = rect.size();
		CPoint2D newPos = rect.position();
		UInt32 autoResizingMask = (*it)->autoResizing();

#ifdef _LOG_AUTORESIZING
		if (bLog)
		{
			std::cout << "parentResized(CSize2D(" << fromSize.width() << ", " << fromSize.height() << "), CSize2D(" << toSize.width() << ", " << toSize.height() << "))" << std::endl;
			std::cout << "mask: ";
			logAutoresizingMask(std::cout, autoResizingMask);
			std::cout << std::endl;
		}
#endif

		if (fromSize.width() > 0)
		{
			if ((autoResizingMask & eAutoResizingFixedLeft) && (autoResizingMask & eAutoResizingFixedWidth))
			{	// l + w

			}
			else if ((autoResizingMask & eAutoResizingFixedLeft) && (autoResizingMask & eAutoResizingFixedRight))
			{ // l + r
				newSize.setWidth(newSize.width() + deltaWidth);
			}
			else if ((autoResizingMask & eAutoResizingFixedWidth) && (autoResizingMask & eAutoResizingFixedRight))
			{ // w + r
				newPos.setX(rect.x() + deltaWidth);
			}
			else if (autoResizingMask & eAutoResizingFixedLeft)
			{ // l
				newSize.setWidth(toSize.width() / (fromSize.width() / rect.width()));
			}
			else if (autoResizingMask & eAutoResizingFixedWidth)
			{ // w
				Float32 oldLeftRatio = pos.x() ? (fromSize.width() - rect.width()) / pos.x() : 2.0f;
				Float32 newLeft = (toSize.width() - rect.width()) / oldLeftRatio;
				newPos.setX(rect.x() + newLeft - pos.x());
			}
			else if (autoResizingMask & eAutoResizingFixedRight)
			{ // r

			}
			else
			{ // 0

			}
		}


		if (fromSize.height() > 0)
		{
			if ((autoResizingMask & eAutoResizingFixedTop) && (autoResizingMask & eAutoResizingFixedHeight))
			{	// l + w

			}
			else if ((autoResizingMask & eAutoResizingFixedTop) && (autoResizingMask & eAutoResizingFixedBottom))
			{ // l + r
				newSize.setHeight(newSize.height() + deltaHeight);
			}
			else if ((autoResizingMask & eAutoResizingFixedHeight) && (autoResizingMask & eAutoResizingFixedBottom))
			{ // w + r
				newPos.setY(rect.y() + deltaHeight);
			}
			else if (autoResizingMask & eAutoResizingFixedTop)
			{ // l
				newSize.setHeight(toSize.height() / (fromSize.height() / rect.height()));
			}
			else if (autoResizingMask & eAutoResizingFixedHeight)
			{ // w
				Float32 oldTopRatio = pos.y() ? (fromSize.height() - rect.height()) / pos.y() : 2.0f;
				Float32 newTop = (toSize.height() - rect.height()) / oldTopRatio;
				newPos.setY(rect.y() + newTop - pos.y());
			}
			else if (autoResizingMask & eAutoResizingFixedBottom)
			{ // r

			}
			else
			{ // 0

			}
		}

		(*it)->setAbsolutePosition(newPos);
		(*it)->setSize(newSize);
	}
}

void CView::setAbsolutePosition(const CPoint2D& position)
{
	LE_ENTER_LOG;

	CPoint2D prevPos = mRect.position();
	CControl::setAbsolutePosition(position);
	CSize2D delta(position.x() - prevPos.x(), position.y() - prevPos.y());

	CControlList::iterator end = mChildren.end();
	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
	{
		CPoint2D prevPos = (*it)->absolutePosition();
		(*it)->setAbsolutePosition(
			CPoint2D(prevPos.x() + delta.width(), prevPos.y() + delta.height())
				);
	}
}

Bool CView::childBecomesFirstResponder(CControl* child, CView* parent)
{
	if (mParent)
	{
		if (mParent->childBecomesFirstResponder(child, this))
		{
			CControl* controlToMove = (parent)?(parent):(child);

			mChildren.remove(controlToMove);
			mChildren.push_back(controlToMove);
			return true;
		}
	}

	return false;
}

Bool CView::isChildFirstResponder(const CControl* child) const
{
	return mParent && mParent->isChildFirstResponder(child);
}


	} // namespace le
} // namespace sokira
