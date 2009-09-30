#include "slCControl.h"

#include <le/core/debug/slDebug.h>
#include "slCScreen.h"
#include "slCControlDelegate.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CControl);

template <class T>
class CDelegator
{
	public:
		template <class T2>
		CDelegator(T2* del1, T* del2, CControl* sender) :
			mDel1(dynamic_cast<T*>(del1)), mDel2(del2), mSender(sender)
		{

		}

		template<class ARG>
		void callMethod0(void (T::*func)(ARG, CControl*), ARG arg)
		{
			if(mDel1)(mDel1->*func)(arg, mSender);
			if(mDel2)(mDel2->*func)(arg, mSender);
		}

		template<class ARG>
		bool callMethod1(bool (T::*func)(ARG, CControl*), ARG arg)
		{
			bool result = false;
			if(mDel1)
				result = (mDel1->*func)(arg, mSender);
			if(mDel2)
				result = (mDel2->*func)(arg, mSender) || result;
			return result;
		}

		bool callMethod2(bool (T::*func)(CControl*))
		{
			bool result = false;
			if(mDel1)
				result = (mDel1->*func)(mSender);
			if(mDel2)
				result = (mDel2->*func)(mSender) || result;
			return result;
		}

	private:
		T* mDel1, *mDel2;
		CControl* mSender;
};


CControl::CControl() :
	mParent(NULL), mDelegate(NULL), mAutoResizingMask(eAutoResizingFixedTopLeft), mBorderWidth(1.0f), mVisible(true)
{
	LE_ENTER_LOG;
}

CControl::CControl(const CRectangle& rect) :
	mParent(NULL), mDelegate(NULL), mAutoResizingMask(eAutoResizingFixedTopLeft), mBorderWidth(1.0f), mVisible(true), mRect(rect)
{
	LE_ENTER_LOG;
}

CControl::~CControl()
{
	LE_ENTER_LOG;
}

void CControl::destroy()
{
	LE_ENTER_LOG;

	if(mParent)
		mParent->removeChild(this);
}

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

void CControl::setSize(const CSize2D& Size)
{
	LE_ENTER_LOG;

	if(mRect.size() != Size)
	{
		mRect.size(Size);

		if (mDelegate) mDelegate->onResize(this);

		setNeedsRedraw();
	}
}

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

void CControl::parentResized(const CSize2D& fromSize, const CSize2D& toSize)
{
	LE_ENTER_LOG;

	Bool bLog = false;

	if (objectClass().name() == "CMainMenu")
	{
		bLog = true;
	}

	float deltaWidth = toSize.width() - fromSize.width();
	float deltaHeight = toSize.height() - fromSize.height();

	CPoint2D pos = relativePosition();
	CSize2D newSize(mRect.size());
	CPoint2D newPos = mRect.position();

//	float leftRatio = fromSize.width() / rect.x();
//	float widthRatio = fromSize.width() / rect.width();
//	float rightRatio = fromSize.width() / (fromSize.width() - rect.width() - rect.x());
//
//	float newLeftRatio = 1.0f;
//	float newWidthRatio = 1.0f;
//	float newRightRatio = 1.0f;
if (bLog)
{
	std::cout << "parentResized(CSize2D(" << fromSize.width() << ", " << fromSize.height() << "), CSize2D(" << toSize.width() << ", " << toSize.height() << "))" << std::endl;
	std::cout << "mask: ";
	logAutoresizingMask(std::cout, mAutoResizingMask);
	std::cout << std::endl;
}

	if (fromSize.width() > 0)
	{
		if ((mAutoResizingMask & eAutoResizingFixedLeft) && (mAutoResizingMask & eAutoResizingFixedWidth))
		{	// l + w
			
		}
		else if ((mAutoResizingMask & eAutoResizingFixedLeft) && (mAutoResizingMask & eAutoResizingFixedRight))
		{ // l + r
			newSize.setWidth(newSize.width() + deltaWidth);
		}
		else if ((mAutoResizingMask & eAutoResizingFixedWidth) && (mAutoResizingMask & eAutoResizingFixedRight))
		{ // w + r
			newPos.x(mRect.x() + deltaWidth);
		}
		else if (mAutoResizingMask & eAutoResizingFixedLeft)
		{ // l
			newSize.setWidth(toSize.width() / (fromSize.width() / mRect.width()));
		}
		else if (mAutoResizingMask & eAutoResizingFixedWidth)
		{ // w
			Float32 oldLeftRatio = pos.x() ? (fromSize.width() - mRect.width()) / pos.x() : 2.0f;
			Float32 newLeft = (toSize.width() - mRect.width()) / oldLeftRatio;
			newPos.x(mRect.x() + newLeft - pos.x());
		}
		else if (mAutoResizingMask & eAutoResizingFixedRight)
		{ // r
		
		}
		else
		{ // 0

		}
	}


	if (fromSize.height() > 0)
	{
		if ((mAutoResizingMask & eAutoResizingFixedTop) && (mAutoResizingMask & eAutoResizingFixedHeight))
		{	// l + w
			
		}
		else if ((mAutoResizingMask & eAutoResizingFixedTop) && (mAutoResizingMask & eAutoResizingFixedBottom))
		{ // l + r
			newSize.setHeight(newSize.height() + deltaHeight);
		}
		else if ((mAutoResizingMask & eAutoResizingFixedHeight) && (mAutoResizingMask & eAutoResizingFixedBottom))
		{ // w + r
			newPos.x(mRect.x() + deltaHeight);
		}
		else if (mAutoResizingMask & eAutoResizingFixedTop)
		{ // l
			newSize.setHeight(toSize.height() / (fromSize.height() / mRect.height()));
		}
		else if (mAutoResizingMask & eAutoResizingFixedHeight)
		{ // w
			Float32 oldTopRatio = pos.y() ? (fromSize.height() - mRect.height()) / pos.y() : 2.0f;
			Float32 newTop = (toSize.height() - mRect.height()) / oldTopRatio;
			newPos.y(mRect.y() + newTop - pos.y());
		}
		else if (mAutoResizingMask & eAutoResizingFixedBottom)
		{ // r
		
		}
		else
		{ // 0

		}
	}

	setAbsolutePosition(newPos);
	setSize(newSize);
}

//void CControl::parentMoved(const CPoint& fromPos, const CPoint& toPos)
//{
//	LE_ENTER_LOG;
//
//	CPoint prevPos = CControl::absolutePosition();
//	absolutePosition(CPoint(prevPos.x() + (toPos.x() - fromPos.x()), prevPos.y() + (toPos.y() - fromPos.y())));
//}

CPoint CControl::absolutePosition() const
{
	LE_ENTER_LOG;
	return mRect.position();
}

void CControl::setAbsolutePosition(const CPoint& position)
{
	LE_ENTER_LOG;
	mRect.position(position);
}

CPoint CControl::relativePosition() const
{
	LE_ENTER_LOG;

	if(mParent)
	{
		CPoint myPos = mRect.position();
		CPoint parentPos = mParent->absolutePosition();
		return CPoint(myPos.x() - parentPos.x(), myPos.y() - parentPos.y());
	}
	return absolutePosition();
}

void CControl::setRelativePosition(const CPoint& point)
{
	LE_ENTER_LOG;

	CPoint parentPosition = (mParent)?(mParent->absolutePosition()):(CPoint());
	mRect.position(CPoint(parentPosition.x() + point.x(), parentPosition.y() + point.y()));
	if (mDelegate) mDelegate->onMove(this);
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

Bool CControl::onMouseDown(EMouseButton button, const CPoint& point)
{
	return false;
}

Bool CControl::onMouseUp(EMouseButton button, const CPoint& point)
{
	return false;
}

Bool CControl::onMouseHover(const CPoint& point)
{
	return false;
}

Bool CControl::onMouseOut(const CPoint& point)
{
	return false;
}

Bool CControl::onMouseIn(const CPoint& point)
{
	return false;
}

Bool CControl::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	return (hitTest(point))?(performMouse(button, state, point)):(false);
}

Bool CControl::hitTest(const CPoint& point) const
{
	return isVisible() && (isFirstResponder() || absoluteRect().pointInRect(point));
}

Bool CControl::performMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	switch (state)
	{
		case eButtonStateDown:
			becomeFirstResponder();
			return onMouseDown(button, point);
		case eButtonStateUp:
			return onMouseUp(button, point);
		default: ;
	}

	return onMouseHover(point);
}


//Bool CControl::mouseButtonPressed(EMouseButton button, const CPoint& point, const CTheme* theme)
//{
//	return onMouseDown(button, point);
//}
//
//Bool CControl::mouseButtonReleased(EMouseButton button, const CPoint& point, const CTheme* theme)
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

bool CControl::onKey(unsigned char inkey, int px, int py)
{
	LE_ENTER_LOG;

	return CDelegator<CControlDelegate>(this, mDelegate, this).
				callMethod1<int>(&CControlDelegate::onKeyDown, inkey);
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

void CControl::moveLastToDraw()
{
	LE_ENTER_LOG;

	if(mParent)
	{
		mParent->mChildren.remove(this);
		mParent->mChildren.push_back(this);
		mParent->moveLastToDraw();
	}
}

CWindow* CControl::parent() const
{
	LE_ENTER_LOG;
	return mParent;
}

void CControl::setVisible(Bool visible)
{
	mVisible = visible;
}

Bool CControl::isVisible() const
{
	return mVisible;
}

void CControl::setParent(CWindow* newParent)
{
	LE_ENTER_LOG;

	if(newParent == mParent)
		return;

	CPoint relPos = relativePosition();
	if(mParent)
	{
		mParent->removeChild(this);
	}

	CPoint parentPos = (newParent)?(newParent->absolutePosition()):(CPoint());
	setAbsolutePosition(CPoint(parentPos.x() + relPos.x(), parentPos.y() + relPos.y()));
	mParent = newParent;
}

void CControl::setNeedsRedraw()
{
	if (mParent) mParent->setNeedsRedraw();
}

void CControl::draw(const CTheme* theme, CRenderingContext* context) const
{
//	std::cout << "CControl::draw" << std::endl;
	if (isVisible())
		theme->drawControl(this, context);
}

Bool CControl::becomeFirstResponder()
{
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

	} // namespace le
} // namespace sokira
