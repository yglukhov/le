#pragma once

#include <le/core/slCObject.h>
#include "slTCGraphicControllerClass.h"

namespace sokira
{
	namespace le
	{

class CControl;
class CPoint;

class CControlBasicController
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CControlBasicController)
	LE_RTTI_END

	public:
		virtual void draw(const CControl* control) const;
		virtual bool hitTest(const CControl* control, const CPoint& point) const;
};

class CWindowBasicController : public CControlBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CWindowBasicController);
	virtual void draw(const CControl* control) const;
};

class CButtonBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CButtonBasicController);
	virtual void draw(const CControl* control) const;
};

class CDialogBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CDialogBasicController);
	virtual void draw(const CControl* control) const;
};

class CTitleBarBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CTitleBarBasicController);
	virtual void draw(const CControl* control) const;
};

	} // namespace le
} // namespace sokira
