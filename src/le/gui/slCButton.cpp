#include "slCTheme.h"
#include "slCButton.h"
#include "slCScreen.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CButton);

CButton::CButton() :
	CControl(CRectangle(0, 0, 10, 10)),
	mState(eButtonStateUp)
{

}

CButton::CButton(const CRectangle& rect) :
	CControl(rect),
	mState(eButtonStateUp)
{

}

//void CButton::onSetFocus()
//{
//
//}
//
//void CButton::onLooseFocus()
//{
//
//}

//bool CButton::onMouseLeftDown(const CPoint& point, CControl* sender)
//{
//	mState = eButtonStateDown;
//	return true;
//}
//
//bool CButton::onMouseLeftUp(const CPoint& point, CControl* sender)
//{
//	std::cout << "Button pressed!" << std::endl;
//	mState = eButtonStateUp;
//	setNeedsRedraw();
//	return false;
//}

void CButton::setText(const CString& text)
{
	mText = text;
}

CString CButton::text() const
{
	return mText;
}

void CButton::setOnClick(TOnClick& onClick)
{
	mOnClick = onClick;
}


Bool CButton::onMouseDown(EMouseButton button, const CPoint2D& point)
{
	if (button == eMouseButtonLeft)
	{
		mState = eButtonStateDown;
		setNeedsRedraw();
		return true;
	}
	return false;
}

Bool CButton::onMouseUp(EMouseButton button, const CPoint2D& point)
{
	LE_ENTER_LOG;
	if (button == eMouseButtonLeft && mState == eButtonStateDown)
	{
		mState = eButtonStateUp;
		resignFirstResponder();
		if (absoluteRect().containsPoint(point) && mOnClick) { LE_IF_LOG(log << "CLICK!!!" << std::endl); mOnClick(); }
		setNeedsRedraw();
		return true;
	}
	return false;
}

void CButton::controlDidBecomeFirstResponder()
{
//	std::cout << "Button did become first responder!" << std::endl;
}

void CButton::controlDidResignFirstResponder()
{
//	std::cout << "Button did resign first responder!" << std::endl;
}

void CButton::draw(const CTheme* theme, CRenderingContext* context) const
{
	theme->drawButton(this, context);
}


EButtonState CButton::state() const
{
	return mState;
}

	} // namespace le
} // namespace sokira
