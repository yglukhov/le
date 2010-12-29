#include "slCTheme.h"
#include <le/core/debug/slDebug.h>
#include "slCView.h"
#include "slCButton.h"
#include "slCStaticText.h"
#include "slCScrollBar.h"
#include "slCRenderingContext.h"


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTheme);

CTheme::CTheme()
{

}

CTheme::~CTheme()
{

}

void CTheme::drawControl(const CControl* control, CRenderingContext* context) const
{

}

void CTheme::drawWindow(const CView* window, CRenderingContext* context) const
{
	CRectangle rect = window->absoluteRect();
	CRectangle tempRect = rect;
	tempRect.setHeight(30);
	CColor color1(0.81f, 0.81f, 0.81f, 1.0f);
	CColor color2(0.66f, 0.66f, 0.66f, 1.0f);
	context->drawVerticalGradient(color1, color2, tempRect);

	context->setColor(0.79f, 0.79f, 0.79f, 1.0f);
	context->drawSegment(CSegment2D(rect.position(), CPoint2D(rect.x() + rect.width() - 1, rect.y())));

	context->setColor(0.89f, 0.89f, 0.89f, 1.0f);
	context->drawSegment(CSegment2D(CPoint2D(rect.x(), rect.y() + 1), CPoint2D(rect.x() + rect.width() - 1, rect.y() + 1)));

	context->setColor(color2);

	tempRect = rect;
	tempRect.setY(tempRect.y() + 30);
	tempRect.setHeight(tempRect.height() - 31);
	context->drawRect(tempRect);

	tempRect = rect;
	tempRect.setY(tempRect.y() + tempRect.height() - 30);
	tempRect.setHeight(30);
	context->drawVerticalGradient(color2, color1, tempRect);
}

void CTheme::drawButton(const CButton* button, CRenderingContext* context) const
{
	CRectangle rect = button->absoluteRect();

	CColor color1(0.66f, 0.66f, 0.66f, 1.0f);
	CColor color2(0.81f, 0.81f, 0.81f, 1.0f);

	if (button->state() == eButtonStateDown)
	{
		CColor tmp = color1;
		color1 = color2;
		color2 = tmp;
	}

	CRectangle tempRect = rect;
	tempRect.setHeight(rect.height() / 2);
	context->drawVerticalGradient(color1, color2, tempRect);

	tempRect.setY(tempRect.y() + tempRect.height());
	context->drawVerticalGradient(color2, color1, tempRect);

	context->setColor(0.46f, 0.46f, 0.46f, 1.0f);
	context->setLineWidth(1.0f);
	context->drawWireRect(rect);

//	std::cout << "drawButton" << std::endl;
	context->setColor(0.0f, 0.0f, 0.0f);
	rect.offset(20, 25);
	context->drawText(button->text(), rect.position());
}

void CTheme::drawStaticText(const CStaticText* text, CRenderingContext* context) const
{
	CPoint2D pos = text->absolutePosition();
	pos.setY(pos.y() + 13);
	context->setColor(0, 0, 0);
	context->drawText(text->text(), pos);
}

void CTheme::drawScrollBar(const CScrollBar* scrollBar, CRenderingContext* context) const
{
	CRectangle rect = scrollBar->absoluteRect();
	context->setColor(0.8f, 0.5f, 0.2f);
	context->drawRect(rect);

	context->setColor(0.6f, 0.9f, 0.1f);
	if (scrollBar->isHorizontal())
	{
		context->drawRect(CRectangle(rect.x(), rect.y(), rect.height(), rect.height()));
		context->drawRect(CRectangle(rect.x() + rect.width() - rect.height(), rect.y(), rect.height(), rect.height()));
	}
	else
	{
		context->drawRect(CRectangle(rect.x(), rect.y(), rect.width(), rect.width()));
		context->drawRect(CRectangle(rect.x(), rect.y() + rect.height() - rect.width(), rect.width(), rect.width()));
	}
}

	} // namespace le
} // namespace sokira
