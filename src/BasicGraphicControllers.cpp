#include "BasicGraphicControllers.h"
#include "CControl.h"
#include "CButton.h"
#include "CTitleBar.h"

IMPLEMENT_GRAPHIC_CONTROLLER(CControlBasicController, CTheme, CControl);
IMPLEMENT_GRAPHIC_CONTROLLER(CWindowBasicController, CTheme, CWindow);
IMPLEMENT_GRAPHIC_CONTROLLER(CButtonBasicController, CTheme, CButton);
IMPLEMENT_GRAPHIC_CONTROLLER(CDialogBasicController, CTheme, CDialog);
IMPLEMENT_GRAPHIC_CONTROLLER(CTitleBarBasicController, CTheme, CTitleBar);


bool CControlBasicController::hitTest(const CControl* control, const CPoint& point) const
{
	return control->absoluteRect().pointInRect(point);
}

void CControlBasicController::draw(const CControl* control) const
{

}

void CWindowBasicController::draw(const CControl* control) const
{
	CColor(0.7, 0.7, 0.7).set();
	control->absoluteRect().draw();
}

void CButtonBasicController::draw(const CControl* control) const
{
	ENTER_LOG_QUIET;

	const CButton* button = dynamic_cast<const CButton*>(control);
	if(button)
	{
		if (button->state() == eButtonStateDown)
		{
			CColor(0.8, 0.5, 0.2).set();
		}
		else
		{
			CColor(0.6, 0.9, 0.1).set();
		}
	}
	else
	{
		IF_LOG(log << "WARNING: control is not a CButton!" << std::endl);
	}

	control->absoluteRect().draw();
}

void CDialogBasicController::draw(const CControl* control) const
{
	CColor(0.0, 0.0, 0.0).set();
	control->absoluteRect().draw();
}

void CTitleBarBasicController::draw(const CControl* control) const
{
	CColor(0.2, 0.3, 0.5).set();
	CRectangle rect = control->absoluteRect();
	rect.draw();
	const CTitleBar* titleBar = dynamic_cast<const CTitleBar*>(control);

	if(titleBar)
	{
		CColor(1.0, 1.0, 1.0).set();
		titleBar->captionText().draw(CPoint(rect.x() + 11, rect.y() + 1));
	}
}
