#pragma once

#include "CObject.h"
#include "GraphicControllerRegistration.h"

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
