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

//static CControl* _firstResponder = NULL;

CControl::CControl() :
	mParent(NULL), mDelegate(NULL), mAutoResizingMask(eAutoResizingFixedTopLeft), mBorderWidth(1.0f)
{
	LE_ENTER_LOG;
}

CControl::CControl(const CRectangle& rect) :
	mParent(NULL), mDelegate(NULL), mAutoResizingMask(eAutoResizingFixedTopLeft), mBorderWidth(1.0f), mRect(rect)
{
	LE_ENTER_LOG;
}

CControl::~CControl()
{
	LE_ENTER_LOG;

//	if(_firstResponder == this)
//		_firstResponder = NULL;
}

void CControl::destroy()
{
	LE_ENTER_LOG;

	if(mParent)
		mParent->removeChild(this);

//	CScreen::instance()->addControlToDelete(this);
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

CSize CControl::size() const
{
	LE_ENTER_LOG;
	return mRect.size();
}

void CControl::setSize(const CSize& Size)
{
	LE_ENTER_LOG;

	if(mRect.size() != Size)
	{
		mRect.size(Size);

		if (mDelegate) mDelegate->onResize(this);

		setNeedsRedraw();
	}
}

void CControl::parentResized(const CSize& fromSize, const CSize& toSize)
{
	LE_ENTER_LOG;

	float deltaWidth = toSize.width() - fromSize.width();
	float deltaHeight = toSize.height() - fromSize.height();

	CSize newSize(mRect.size());

	if((mAutoResizingMask & eAutoResizingFixedRight) && !(mAutoResizingMask & eAutoResizingFixedLeft))
	{
		mRect.x(mRect.x() + deltaWidth);
	}
	else if(mAutoResizingMask & eAutoResizingFixedRight)
	{
		newSize.width(mRect.width() + deltaWidth);
	}

	if((mAutoResizingMask & eAutoResizingFixedBottom) && !(mAutoResizingMask & eAutoResizingFixedTop))
	{
		mRect.y(mRect.y() + deltaHeight);
	}
	else if(mAutoResizingMask & eAutoResizingFixedBottom)
	{
		newSize.height(mRect.height() + deltaHeight);
	}

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
//
//	CScreen::instance()->invalidate();
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

//bool CControl::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
//{
//	LE_ENTER_LOG;
//
//	CPoint absPos = absolutePosition();
//	CPoint relPoint(point.x() - absPos.x(), point.y() - absPos.y());
//	CDelegator<CControlDelegate> delegator(this, mDelegate, this);
//
//	switch(button)
//	{
//		case eMouseButtonLeft:
//		{
//			std::cout << "CControl::onMouse" << std::endl;
//			if(state == eButtonStateDown)
//				setFocus();
//			return (state == eButtonStateUp)?delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseLeftUp, relPoint):
//														delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseLeftDown, relPoint);
//		}
//		case eMouseButtonMiddle:
//		{
//			std::cout << "CControl::onMouse" << std::endl;
//			return (state == eButtonStateUp)?(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMiddleUp, relPoint)):
//														(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMiddleDown, relPoint));
//		}
//		case eMouseButtonRight:
//		{
//			std::cout << "CControl::onMouse" << std::endl;
//			return (state == eButtonStateUp)?(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseRightUp, relPoint)):
//														(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseRightDown, relPoint));
//		}
//		default:
//		{
//			return delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMove, relPoint);
//		}
//	}
//	
//	return false;
//}

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
