#pragma once

#include <le/core/config/slPrefix.h>

LE_NAMESPACE_START

class CControl;
class CPoint;
class CSize;
class CNotification;
class CTitleBar;
class CButton;
// CControlDelegate is a set of event handlers for controls. Some event handlers
// must return true, if the event is succesfully handled and there is no need to
// pass it to parent window.


class CControlDelegate
{
	public:
		//////////////////////////////////////////////////////////////////////////
		// Mouse Events
		virtual bool onMouseMove(const CPoint& point, CControl* sender);
		virtual bool onMouseIn(const CPoint& point, CControl* sender);
		virtual bool onMouseOut(const CPoint& point, CControl* sender);

		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);
		virtual bool onMouseRightUp(const CPoint& point, CControl* sender);
		virtual bool onMouseMiddleUp(const CPoint& point, CControl* sender);

		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
		virtual bool onMouseRightDown(const CPoint& point, CControl* sender);
		virtual bool onMouseMiddleDown(const CPoint& point, CControl* sender);

		virtual bool onMouseClick(const CPoint& point, CControl* sender);
		virtual bool onMouseMultipleClick(const CPoint& point, unsigned clicks, CControl* sender);

		//////////////////////////////////////////////////////////////////////////
		// Keyboard
		virtual bool onKeyDown(int key, CControl* sender);
		virtual bool onKeyUp(int key, CControl* sender);

		//////////////////////////////////////////////////////////////////////////
		// Focus
		virtual bool onSetFocus(CControl* sender);
		virtual bool onLooseFocus(CControl* sender);

		//////////////////////////////////////////////////////////////////////////
		// Control specific
		virtual void onResize(const CSize& size, CControl* sender);
		virtual bool onMove(const CPoint& point, CControl* sender);
};


LE_NAMESPACE_END
