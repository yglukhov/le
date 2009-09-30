#pragma once

#include <le/core/config/slPrefix.h>
#include <le/core/geometry/slTCPoint2D.h>

namespace sokira
{
	namespace le
	{

class CControl;
//class CPoint;
//class CSize2D;
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
		virtual bool onMouseMove(const CPoint2D& point, CControl* sender);
		virtual bool onMouseIn(const CPoint2D& point, CControl* sender);
		virtual bool onMouseOut(const CPoint2D& point, CControl* sender);

		virtual bool onMouseLeftUp(const CPoint2D& point, CControl* sender);
		virtual bool onMouseRightUp(const CPoint2D& point, CControl* sender);
		virtual bool onMouseMiddleUp(const CPoint2D& point, CControl* sender);

		virtual bool onMouseLeftDown(const CPoint2D& point, CControl* sender);
		virtual bool onMouseRightDown(const CPoint2D& point, CControl* sender);
		virtual bool onMouseMiddleDown(const CPoint2D& point, CControl* sender);

		virtual bool onMouseClick(const CPoint2D& point, CControl* sender);
		virtual bool onMouseMultipleClick(const CPoint2D& point, unsigned clicks, CControl* sender);

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
		virtual void onResize(CControl* sender);
		virtual void onMove(CControl* control);
};


	} // namespace le
} // namespace sokira
