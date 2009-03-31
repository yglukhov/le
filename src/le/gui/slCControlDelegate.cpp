#include "slCControlDelegate.h"
#include "slCControl.h"

namespace sokira
{
	namespace le
	{

//////////////////////////////////////////////////////////////////////////
// Mouse Events
bool CControlDelegate::onMouseMove(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseIn(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseOut(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseLeftUp(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseRightUp(const CPoint& point, CControl* sender)
{
	return true;
}


bool CControlDelegate::onMouseMiddleUp(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseLeftDown(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseRightDown(const CPoint& point, CControl* sender)
{
	return false;
}

bool CControlDelegate::onMouseMiddleDown(const CPoint& point, CControl* sender)
{
	return true;
}


bool CControlDelegate::onMouseClick(const CPoint& point, CControl* sender)
{
	return true;
}

bool CControlDelegate::onMouseMultipleClick(const CPoint& point, unsigned clicks, CControl* sender)
{
	return true;
}


//////////////////////////////////////////////////////////////////////////
// Keyboard
bool CControlDelegate::onKeyDown(int key, CControl* sender)
{
	return false;
}

bool CControlDelegate::onKeyUp(int key, CControl* sender)
{
	return false;
}


//////////////////////////////////////////////////////////////////////////
// Focus
bool CControlDelegate::onSetFocus(CControl* sender)
{
	return true;
}

bool CControlDelegate::onLooseFocus(CControl* sender)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Control specific
void CControlDelegate::onResize(CControl* sender)
{

}

void CControlDelegate::onMove(CControl* control)
{

}

	} // namespace le
} // namespace sokira
