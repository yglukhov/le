#include "slCTheme.h"
#include <le/core/debug/slDebug.h>
#include "slCWindow.h"
#include "slCButton.h"
#include "slCStaticText.h"
#include "slCRenderingContext.h"


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTheme);

CTheme::CTheme()
{

}

void CTheme::drawControl(const CControl* control, CRenderingContext* context) const
{

}

void CTheme::drawWindow(const CWindow* window, CRenderingContext* context) const
{
//	CRectangle rect = window->absoluteRect();
//	std::cout << "CTheme::drawWindow: " << rect.x() << ", " << rect.y() << ", " << rect.width() << ", " << rect.height() << std::endl;
	context->setColor(0.7f, 0.7f, 0.7f, 0.5f);
	context->drawRect(window->absoluteRect());
}

void CTheme::drawButton(const CButton* button, CRenderingContext* context) const
{
	if (button->state() == eButtonStateDown)
		context->setColor(0.8f, 0.5f, 0.2f);
	else
		context->setColor(0.6f, 0.9f, 0.1f);

	context->drawRect(button->absoluteRect());
	context->setColor(0.0f, 0.0f, 0.0f);
	CPoint2D pos = button->absolutePosition();
	pos.x(pos.x() + 20);
	pos.y(pos.y() + 25);
	
	context->drawText(button->text(), pos);
}

void CTheme::drawStaticText(const CStaticText* text, CRenderingContext* context) const
{
	CPoint2D pos = text->absolutePosition();
	pos.y(pos.y() + 13);
	context->setColor(0, 0, 0);
	context->drawText(text->text(), pos);
}


	} // namespace le
} // namespace sokira
