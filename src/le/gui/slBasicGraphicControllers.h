#pragma once

#include <le/core/slCObject.h>
#include "slTCGraphicControllerClass.h"

LE_NAMESPACE_START

class CControl;
class CPoint;

class CControlBasicController : public CObject
{
	public:
		virtual void draw(const CControl* control) const;
		virtual bool hitTest(const CControl* control, const CPoint& point) const;
};

class CWindowBasicController : public CControlBasicController
{
	virtual void draw(const CControl* control) const;
};

class CButtonBasicController : public CWindowBasicController
{
	virtual void draw(const CControl* control) const;
};

class CDialogBasicController : public CWindowBasicController
{
	virtual void draw(const CControl* control) const;
};

class CTitleBarBasicController : public CWindowBasicController
{
	virtual void draw(const CControl* control) const;
};

LE_NAMESPACE_END
