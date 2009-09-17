#include "slBasicGraphicControllers.h"
#include <le/gui/slCTheme.h>
#include "slCControl.h"
#include "slCButton.h"
#include "slCTitleBar.h"
#include "slCRenderingContext.h"

LE_DEFINE_LINK_MODULE(_le_slBasicGraphicControllers);

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_GRAPHIC_CONTROLLER(CControlBasicController, CTheme, CControl);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CWindowBasicController, CTheme, CWindow);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CGuiSceneBasicController, CTheme, CGuiScene);
LE_IMPLEMENT_GRAPHIC_CONTROLLER(CButtonBasicController, CTheme, CButton);
//LE_IMPLEMENT_GRAPHIC_CONTROLLER(CDialogBasicController, CTheme, CDialog);
//LE_IMPLEMENT_GRAPHIC_CONTROLLER(CTitleBarBasicController, CTheme, CTitleBar);

Bool CControlBasicController::hitTest(const CControl* control, const CPoint& point) const
{
	return control->isFirstResponder() || control->absoluteRect().pointInRect(point);
}

void CControlBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
{

}

Bool CControlBasicController::onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control, const CTheme* theme) const
{
	if (hitTest(control, point))
	{
		return performMouse(button, state, point, control);
	}

	return false;
}

Bool CControlBasicController::performMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control) const
{
	switch (state)
	{
		case eButtonStateDown:
			control->becomeFirstResponder();
			return control->onMouseDown(button, point);
		case eButtonStateUp:
			return control->onMouseUp(button, point);
		default: ;
	}

	return control->onMouseHover(point);
}

void CWindowBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
{
	context->setColor(0.7f, 0.7f, 0.7f);
	context->drawRect(control->absoluteRect());

	const CWindow* wnd = dynamic_cast<const CWindow*>(control);

	const CWindow::CControlList& list = wnd->children();

	CWindow::CControlList::const_iterator end = list.end();
	for (CWindow::CControlList::const_iterator it = list.begin(); it != end; ++it)
	{
		theme->drawControl(*it, context);
	}
}

Bool CWindowBasicController::onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control, const CTheme* theme) const
{
	if (hitTest(control, point))
	{
		const CWindow* wnd = dynamic_cast<const CWindow*>(control);

		const CWindow::CControlList& list = wnd->children();

		CWindow::CControlList::const_iterator end = list.end();
		for (CWindow::CControlList::const_iterator it = list.begin(); it != end; ++it)
		{
			if (theme->onMouse(button, state, point, *it))
			{
				return true;
			}
		}

		return performMouse(button, state, point, control);
	}

	return false;
}

Bool CGuiSceneBasicController::hitTest(const CControl* control, const CPoint& point) const
{
	return true;
}

void CGuiSceneBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
{
	const CWindow* wnd = dynamic_cast<const CWindow*>(control);

	const CWindow::CControlList& list = wnd->children();

	CWindow::CControlList::const_iterator end = list.end();
	for (CWindow::CControlList::const_iterator it = list.begin(); it != end; ++it)
	{
		theme->drawControl(*it, context);
	}
}

void CButtonBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
{
	LE_ENTER_LOG_QUIET;

	const CButton* button = dynamic_cast<const CButton*>(control);
	if (button)
	{
		if (button->state() == eButtonStateDown)
		{
			context->setColor(0.8f, 0.5f, 0.2f);
		}
		else
		{
			context->setColor(0.6f, 0.9f, 0.1f);
		}
	}
	else
	{
		LE_IF_LOG(log << "WARNING: control is not a CButton!" << std::endl);
	}

	context->drawRect(control->absoluteRect());
}
/*
void CDialogBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
{
	slSetColor(0.2f, 0.7f, 0.5f);
	control->absoluteRect().draw();
}

void CTitleBarBasicController::draw(const CControl* control, const CTheme* theme, CRenderingContext* context) const
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
*/
	} // namespace le
} // namespace sokira
