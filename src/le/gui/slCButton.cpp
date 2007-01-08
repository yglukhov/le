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

bool CButton::onMouseLeftDown(const CPoint& point, CControl* sender)
{
	mState = eButtonStateDown;
	return true;
}

bool CButton::onMouseLeftUp(const CPoint& point, CControl* sender)
{
	mState = eButtonStateUp;
	CScreen::instance()->invalidate();
	return false;
}

EButtonState CButton::state() const
{
	return mState;
}

	} // namespace le
} // namespace sokira
