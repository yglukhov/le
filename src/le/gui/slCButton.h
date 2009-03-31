#pragma once

#include "slCControl.h"
#include "slCControlDelegate.h"

namespace sokira
{
	namespace le
	{

class CButton: public CControl//, public CControlDelegate
{
	LE_DECLARE_RUNTIME_CLASS(CButton);

	public:
		CButton();
		CButton(const CRectangle& rect);

		EButtonState state() const;

	protected:

//		virtual bool canSetFocus();
//		virtual void onSetFocus();
//		virtual void onLooseFocus();

//		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
//		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);

		virtual Bool onMouseDown(EMouseButton button, const CPoint& point);
		virtual Bool onMouseUp(EMouseButton button, const CPoint& point);

		virtual void onClick();

		virtual void controlDidBecomeFirstResponder();
		virtual void controlDidResignFirstResponder();

//		virtual bool onMouseMove(int x, int y);

//		virtual bool onKeyPressed(unsigned char inKey);		
	private:
		EButtonState mState;
};


	} // namespace le
} // namespace sokira
