#include <glut/slGlut.h>
#include "slBasicGraphicControllers.h"
#include "slCControl.h"
#include "slCButton.h"
#include "slCTitleBar.h"

LE_DEFINE_LINK_MODULE(_le_slBasicGraphicControllers);

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_GRAPHIC_CONTROLLER(CControlBasicController, CTheme, CControl);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CWindowBasicController, CTheme, CWindow);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CButtonBasicController, CTheme, CButton);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CDialogBasicController, CTheme, CDialog);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CTitleBarBasicController, CTheme, CTitleBar);

bool CControlBasicController::hitTest(const CControl* control, const CPoint& point) const
{
	return control->absoluteRect().pointInRect(point);
}

void CControlBasicController::draw(const CControl* control) const
{

}

void CWindowBasicController::draw(const CControl* control) const
{
	CColor(0.7f, 0.7f, 0.7f);
	control->absoluteRect().draw();
}

void CButtonBasicController::draw(const CControl* control) const
{
	LE_ENTER_LOG_QUIET;

	const CButton* button = dynamic_cast<const CButton*>(control);
	if(button)
	{
		if (button->state() == eButtonStateDown)
		{
			slSetColor(0.8f, 0.5f, 0.2f);
		}
		else
		{
			slSetColor(0.6f, 0.9f, 0.1f);
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
	slSetColor(CColor());
	control->absoluteRect().draw();
}

void CTitleBarBasicController::draw(const CControl* control) const
{
	slSetColor(0.2f, 0.3f, 0.5f);
	CRectangle rect = control->absoluteRect();
	rect.draw();
	const CTitleBar* titleBar = dynamic_cast<const CTitleBar*>(control);

	if(titleBar)
	{
		slSetColor(1.0f, 1.0f, 1.0f);
		titleBar->captionText().draw(CPoint(rect.x() + 11, rect.y() + 1));
	}
}

	} // namespace le
} // namespace sokira
