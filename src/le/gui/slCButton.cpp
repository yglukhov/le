#include <le/core/thread/slCThread.h>
#include "slCTheme.h"
#include "slCButton.h"
#include "slCWindow.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CButton);

CButton::CButton() :
	CView(CRectangle(0, 0, 10, 10)),
	mState(eButtonStateUp)
{

}

CButton::CButton(const CRectangle& rect) :
	CView(rect),
	mState(eButtonStateUp)
{

}

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


Bool CButton::onMouseDown(EKeyCode button, const CPoint2D& point)
{
	if (button == eKeyCodeMouseButtonPrimary)
	{
		mState = eButtonStateDown;
		setNeedsRedraw();
		return true;
	}
	return false;
}

Bool CButton::onMouseUp(EKeyCode button, const CPoint2D& point)
{
	if (button == eKeyCodeMouseButtonPrimary && mState == eButtonStateDown)
	{
		mState = eButtonStateUp;
		setNeedsRedraw();
		if (mOnClick) mOnClick();
		return true;
	}
	return false;
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
