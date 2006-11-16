#include "slCControl.h"

#include <le/core/debug/slDebug.h>
#include "slCScreen.h"
#include "slCControlDelegate.h"
#include "slCTheme.h"

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CControl);

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

static CControl* _firstResponder = NULL;

CControl::CControl() :
	mParent(NULL), mFace(NULL), mDelegate(NULL), mAutoResizingMask(eAlignTopLeft), mBorderWidth(1.0f)
{
	LE_ENTER_LOG;
}

CControl::CControl(const CRectangle& rect) :
	mParent(NULL), mFace(NULL), mDelegate(NULL), mAutoResizingMask(eAlignTopLeft), mBorderWidth(1.0f), mRect(rect)
{
	LE_ENTER_LOG;
}

CControl::~CControl()
{
	LE_ENTER_LOG;

	if(_firstResponder == this)
		_firstResponder = NULL;
}

void CControl::destroy()
{
	LE_ENTER_LOG;

	if(mParent)
		mParent->removeChild(this);
	
	CScreen::instance()->addControlToDelete(this);
	
}

void CControl::draw() const
{
	LE_ENTER_LOG;
	CTheme::instance()->drawControl(this);
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

void CControl::size(const CSize& Size)
{
	LE_ENTER_LOG;

	if(mRect.size() != Size)
	{
		mRect.size(Size);

		CDelegator<CControlDelegate>(this, mDelegate, this).
			callMethod0<const CSize&>(&CControlDelegate::onResize, Size);

		CScreen::instance()->invalidate();
	}
}

void CControl::parentResized(const CSize& fromSize, const CSize& toSize)
{
	LE_ENTER_LOG;

	float deltaWidth = toSize.width() - fromSize.width();
	float deltaHeight = toSize.height() - fromSize.height();

	CSize newSize(mRect.size());

	if((mAutoResizingMask & eAlignRight) && !(mAutoResizingMask & eAlignLeft))
	{
		mRect.x(mRect.x() + deltaWidth);
	}
	else if(mAutoResizingMask & eAlignRight)
	{
		newSize.width(mRect.width() + deltaWidth);
	}

	if((mAutoResizingMask & eAlignBottom) && !(mAutoResizingMask & eAlignTop))
	{
		mRect.y(mRect.y() + deltaHeight);
	}
	else if(mAutoResizingMask & eAlignBottom)
	{
		newSize.height(mRect.height() + deltaHeight);
	}

	size(newSize);
}

void CControl::parentMoved(const CPoint& fromPos, const CPoint& toPos)
{
	LE_ENTER_LOG;

	CPoint prevPos = CControl::absolutePosition();
	absolutePosition(CPoint(prevPos.x() + (toPos.x() - fromPos.x()), prevPos.y() + (toPos.y() - fromPos.y())));
}

CPoint CControl::absolutePosition() const
{
	LE_ENTER_LOG;
	return mRect.position();
}

void CControl::absolutePosition(const CPoint& position)
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

void CControl::relativePosition(const CPoint& point)
{
	LE_ENTER_LOG;

	CPoint parentPosition = (mParent)?(mParent->absolutePosition()):(CPoint());

	mRect.position(CPoint(parentPosition.x() + point.x(), parentPosition.y() + point.y()));

	CDelegator<CControlDelegate>(this, mDelegate, this).
		callMethod1<const CPoint&>(&CControlDelegate::onMove, point);
	CScreen::instance()->invalidate();
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

bool CControl::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	LE_ENTER_LOG;

	CPoint absPos = absolutePosition();
	CPoint relPoint(point.x() - absPos.x(), point.y() - absPos.y());
	CDelegator<CControlDelegate> delegator(this, mDelegate, this);

	switch(button)
	{
		case eMouseButtonLeft:
		{
			if(state == eButtonStateDown)
				setFocus();
			return (state == eButtonStateUp)?delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseLeftUp, relPoint):
														delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseLeftDown, relPoint);
		}
		case eMouseButtonMiddle:
		{
			return (state == eButtonStateUp)?(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMiddleUp, relPoint)):
														(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMiddleDown, relPoint));
		}
		case eMouseButtonRight:
		{
			return (state == eButtonStateUp)?(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseRightUp, relPoint)):
														(delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseRightDown, relPoint));
		}
		default:
		{
			return delegator.callMethod1<const CPoint&>(&CControlDelegate::onMouseMove, relPoint);
		}
	}
	
	return false;
}

bool CControl::onKey(unsigned char inkey, int px, int py)
{
	LE_ENTER_LOG;

	return CDelegator<CControlDelegate>(this, mDelegate, this).
				callMethod1<int>(&CControlDelegate::onKeyDown, inkey);
}

void CControl::autoResizing(unsigned mask)
{
	LE_ENTER_LOG;
	mAutoResizingMask = mask;
}

unsigned CControl::autoResizing() const
{
	LE_ENTER_LOG;
	return mAutoResizingMask;
}

bool CControl::setFocus()
{
	LE_ENTER_LOG;

	if(_firstResponder)
	{
		CDelegator<CControlDelegate> delegator(_firstResponder, _firstResponder->delegate(), this);
		if(!delegator.callMethod2(&CControlDelegate::onLooseFocus))
			return false;
	}

	CDelegator<CControlDelegate> delegator(this, mDelegate, this);

	if(!delegator.callMethod2(&CControlDelegate::onSetFocus))
		return false;

	_firstResponder = this;
	moveLastToDraw();
	CScreen::instance()->invalidate();
	return true;
}

void CControl::moveLastToDraw()
{
	LE_ENTER_LOG;

	if(mParent)
	{
		mParent->mChilds.remove(this);
		mParent->mChilds.push_back(this);
		mParent->moveLastToDraw();
	}
}

CWindow* CControl::parent() const
{
	LE_ENTER_LOG;
	return mParent;
}

CFace* CControl::face()
{
	return mFace;
}

void CControl::face(CFace* face)
{
	mFace = face;
}

void CControl::parent(CWindow* newParent)
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
	absolutePosition(CPoint(parentPos.x() + relPos.x(), parentPos.y() + relPos.y()));
	mParent = newParent;
}

CControl* CControl::firstResponder()
{
	LE_ENTER_LOG;
	return _firstResponder;
}


LE_NAMESPACE_END
