#pragma once

#include "CWindow.h"

class CDecorator : public CControl
{
	public:
		CDecorator(CControl* child);
		virtual void child(CControl* child);

	protected:
		bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);

//		virtual bool canLooseFocus();
//		virtual bool canSetFocus();
//		virtual void onSetFocus();
//		virtual void onLooseFocus();

//		virtual bool onMouseDownLeft(int x, int y);
//		virtual bool onMouseDownRight(int x, int y);
//		virtual bool onMouseDownMiddle(int x, int y);
//
//		virtual bool onMouseUpLeft(int x, int y);
//		virtual bool onMouseUpRight(int x, int y);
//		virtual bool onMouseUpMiddle(int x, int y);
//
//		virtual bool onMouseMove(int x, int y);
//		virtual bool onMouseClick(int x, int y);
//		virtual bool onKeyPressed(unsigned char inKey);

//		virtual void onResize(const CSize& size);
	
	protected:
		CControl* mChild;
};