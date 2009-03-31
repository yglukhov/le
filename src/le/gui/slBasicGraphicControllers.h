#if !defined SL_LE_gui_slBasicGraphicControllers_h
#define SL_LE_gui_slBasicGraphicControllers_h

#include <le/core/slCObject.h>
#include "slTCGraphicControllerClass.h"
#include <le/gui/slConstants.h>

namespace sokira
{
	namespace le
	{

class CControl;
class CPoint;
class CRenderingContext;
class CTheme;

class CControlBasicController
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CControlBasicController)
	LE_RTTI_END

	public:
		virtual void draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const;
		virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control, const CTheme* theme) const;
	protected:
		virtual Bool hitTest(const CControl* control, const CPoint& point) const;
		Bool performMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control) const;
};

class CWindowBasicController : public CControlBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CWindowBasicController);
	virtual void draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const;
	virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control, const CTheme* theme) const;
};

class CGuiSceneBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CGuiSceneBasicController);
	virtual Bool hitTest(const CControl* control, const CPoint& point) const;
	virtual void draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const;
};

class CButtonBasicController : public CControlBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CButtonBasicController);
	virtual void draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const;
};
/*
class CDialogBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CDialogBasicController);
	virtual void draw(const CControl* control, CRenderingContext* context) const;
};

class CTitleBarBasicController : public CWindowBasicController
{
	LE_DECLARE_GRAPHIC_CONTROLLER(CTitleBarBasicController);
	virtual void draw(const CControl* control, CRenderingContext* context) const;
};
*/
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slBasicGraphicControllers_h
