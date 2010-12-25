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
	CControl(CRectangle(0, 0, 10, 10)),
	mState(eButtonStateUp)
{

}

CButton::CButton(const CRectangle& rect) :
	CControl(rect),
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

		CRunLoop& runLoop = CThread::thread().runLoop();

		while (true)
		{
			CEvent event = runLoop.nextEventMatchingType(eEventTypeMouseUp | eEventTypeMouseMove);
			if (event.type() == eEventTypeMouseUp && event.mouseButton() == eKeyCodeMouseButtonPrimary)
			{
				mState = eButtonStateUp;
				setNeedsRedraw();
				if (mOnClick) mOnClick();
				break;
			}
			else if (event.type() == eEventTypeMouseMove)
			{
				
			}
		}

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
