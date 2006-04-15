#pragma once

#include <config/slPrefix.h>
#include "slCControl.h"
#include "slCControlDelegate.h"

LE_NAMESPACE_START

class CButton: public CControl, public CControlDelegate
{
	DECLARE_RUNTIME_CLASS(CButton);

	public:
		CButton();
		CButton(const CRectangle& rect);

		EButtonState state() const;

	protected:

//		virtual bool canSetFocus();
//		virtual void onSetFocus();
//		virtual void onLooseFocus();

		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);

//		virtual bool onMouseMove(int x, int y);

//		virtual bool onKeyPressed(unsigned char inKey);		
	private:
		EButtonState mState;
};


LE_NAMESPACE_END
