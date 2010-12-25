#include "slCControl.h"

#include <le/core/debug/slDebug.h>
#include "slCWindow.h"
#include "slCControlDelegate.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CControl);


CControl::CControl() :
	mParent(NULL),
	mDelegate(NULL),
	mAutoResizingMask(eAutoResizingFixedTopLeft),
	mBorderWidth(1.0f),
	mVisible(true)
{
	LE_ENTER_LOG;
}

CControl::CControl(const CRectangle& rect) :
	mParent(NULL),
	mDelegate(NULL),
	mAutoResizingMask(eAutoResizingFixedTopLeft),
	mBorderWidth(1.0f),
	mVisible(true),
	mRect(rect)
{
	LE_ENTER_LOG;
}

CControl::~CControl()
{
	LE_ENTER_LOG;
}

//void CControl::destroy()
//{
//	LE_ENTER_LOG;
//
//	if(mParent)
//		mParent->removeChild(this);
//}

CRectangle CControl::absoluteRect() const
{
	LE_ENTER_LOG;
	return CRectangle(absolutePosition(), size());
}

CRectangle CControl::relativeRect() const
{
	LE_ENTER_LOG;
	return CRectangle(relativePosition(), size());
}

CSize2D CControl::size() const
{
	LE_ENTER_LOG;
	return mRect.size();
}

void CControl::setSize(const CSize2D& size)
{
	LE_ENTER_LOG;

	if(mRect.size() != size)
	{
		mRect.setSize(size);

		if (mDelegate) mDelegate->onResize(this);

		setNeedsRedraw();
	}
}

CPoint2D CControl::absolutePosition() const
{
	LE_ENTER_LOG;
	return mRect.position();
}

void CControl::setAbsolutePosition(const CPoint2D& position)
{
	LE_ENTER_LOG;
	mRect.setPosition(position);
	if (mDelegate) mDelegate->onMove(this);
}

CPoint2D CControl::relativePosition() const
{
	LE_ENTER_LOG;

	if (mParent)
	{
		CPoint2D myPos = mRect.position();
		CPoint2D parentPos = mParent->absolutePosition();
		return CPoint2D(myPos.x() - parentPos.x(), myPos.y() - parentPos.y());
	}
	return absolutePosition();
}

void CControl::setRelativePosition(const CPoint2D& point)
{
	LE_ENTER_LOG;

	CPoint2D parentPosition = (mParent)?(mParent->absolutePosition()):(CPoint2D());
	setAbsolutePosition(CPoint2D(parentPosition.x() + point.x(), parentPosition.y() + point.y()));
}

void CControl::delegate(CControlDelegate* Delegate)
{
	LE_ENTER_LOG;
	mDelegate = Delegate;
}

CControlDelegate* CControl::delegate()
{
	LE_ENTER_LOG;
	return mDelegate;
}

float CControl::borderWidth() const
{
	LE_ENTER_LOG;
	return mBorderWidth;
}

void CControl::borderWidth(float width)
{
	LE_ENTER_LOG;
	mBorderWidth = width;
}

Bool CControl::onMouseDown(EKeyCode button, const CPoint2D& point)
{
	return false;
}

Bool CControl::onMouseUp(EKeyCode button, const CPoint2D& point)
{
	return false;
}

Bool CControl::onMouseHover(const CPoint2D& point)
{
	return false;
}

Bool CControl::onMouseOut(const CPoint2D& point)
{
	return false;
}

Bool CControl::onMouseIn(const CPoint2D& point)
{
	return false;
}

Bool CControl::onMouse(EKeyCode button, EButtonState state, const CPoint2D& point)
{
	LE_ENTER_LOG;
	return hitTest(point) && performMouse(button, state, point);
}

Bool CControl::hitTest(const CPoint2D& point) const
{
	LE_ENTER_LOG;
	return isVisible() && (isFirstResponder() || absoluteRect().containsPoint(point));
}

Bool CControl::performMouse(EKeyCode button, EButtonState state, const CPoint2D& point)
{
	LE_ENTER_LOG;
	switch (state)
	{
		case eButtonStateDown:
//			becomeFirstResponder();
			return onMouseDown(button, point);
		case eButtonStateUp:
			return onMouseUp(button, point);
		default: ;
	}

	return onMouseHover(point);
}


//Bool CControl::mouseButtonPressed(EKeyCode button, const CPoint& point, const CTheme* theme)
//{
//	return onMouseDown(button, point);
//}
//
//Bool CControl::mouseButtonReleased(EKeyCode button, const CPoint& point, const CTheme* theme)
//{
//	return onMouseUp(button, point);
//}
//
//Bool CControl::mouseHovered(const CPoint& point, const CTheme* theme)
//{
//	return onMouseHover(point);
//}
//
//Bool CControl::mouseExited(const CPoint& point, const CTheme* theme)
//{
//	return onMouseOut(point);
//}
//
//Bool CControl::mouseEntered(const CPoint& point, const CTheme* theme)
//{
//	return onMouseOut(point);
//}

Bool CControl::onKeyDown(EKeyCode keyCode)
{
	return false;
}

Bool CControl::onKeyUp(EKeyCode keyCode)
{
	return false;
}

void CControl::setAutoResizing(unsigned mask)
{
	LE_ENTER_LOG;
	mAutoResizingMask = mask;
}

unsigned CControl::autoResizing() const
{
	LE_ENTER_LOG;
	return mAutoResizingMask;
}

CView* CControl::parent() const
{
	LE_ENTER_LOG;
	return mParent;
}

void CControl::setVisible(Bool visible)
{
	mVisible = visible;
	setNeedsRedraw();
}

Bool CControl::isVisible() const
{
	return mVisible;
}

void CControl::setParent(CView* newParent)
{
	LE_ENTER_LOG;

//	LE_IF_LOG(log << "Old parent: " << mParent << std::endl);
//	LE_IF_LOG(log << "New parent: " << newParent << std::endl);
//
	if (newParent == mParent)
		return;

	CPoint2D relPos = relativePosition();
	if (mParent)
	{
		mParent->removeChild(this);
	}

	CPoint2D parentPos = (newParent)?(newParent->absolutePosition()):(CPoint2D());
	setAbsolutePosition(CPoint2D(parentPos.x() + relPos.x(), parentPos.y() + relPos.y()));
	mParent = newParent;
}

void CControl::setNeedsRedraw()
{
	if (mParent) mParent->setNeedsRedraw();
}

void CControl::draw(const CTheme* theme, CRenderingContext* context) const
{
	if (isVisible()) theme->drawControl(this, context);
}

Bool CControl::becomeFirstResponder()
{
	LE_ENTER_LOG;
	if (mParent && controlCanBecomeFirstResponder())
	{
		if (mParent->childBecomesFirstResponder(this, NULL))
		{
			controlDidBecomeFirstResponder();
			return true;
		}
	}

	return false;
}

Bool CControl::resignFirstResponder()
{
	return isFirstResponder() && mParent && mParent->becomeFirstResponder();
}

Bool CControl::isFirstResponder() const
{
	return mParent && mParent->isChildFirstResponder(this);
}

Bool CControl::controlCanBecomeFirstResponder()
{
	return true;
}

void CControl::controlDidBecomeFirstResponder()
{

}

Bool CControl::controlCanResignFirstResponder()
{
	return true;
}

void CControl::controlDidResignFirstResponder()
{

}

// Remove control from parent and delete it.
void CControl::close()
{
	resignFirstResponder();
	if (mParent) mParent->removeChild(this);
	delete this;
}


	} // namespace le
} // namespace sokira
