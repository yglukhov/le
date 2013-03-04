#include <le/core/template/function/slTCBind.h>
#include "slCScrollView.h"
#include "slCScrollBar.h"
#include "slCRenderingContext.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScrollView);

#define LE_SCROLL_BAR_WIDTH 12

CScrollView::CScrollView()
{

}

CScrollView::CScrollView(const CRectangle& rect) :
	CView(rect)
{
//	mHorizontalScrollBar.setParent(this);
//	mVerticalScrollBar.setParent(this);
//	addChild(mHorizontalScrollBar);
	CScrollBar *scrollBar = new CScrollBar(CRectangle(rect.width() - LE_SCROLL_BAR_WIDTH, 0, LE_SCROLL_BAR_WIDTH, rect.height() - LE_SCROLL_BAR_WIDTH), false);
//	std::cout << "mVerticalScrollBar: " << scrollBar << std::endl;
	CScrollBar::TOnPositionChanged func = bind(&leSelf::onVerticalPositionChanged, this, scrollBar);
	scrollBar->setOnPositionChanged(func);
	addChild(scrollBar);

	scrollBar = new CScrollBar(CRectangle(0, rect.height() - LE_SCROLL_BAR_WIDTH, rect.width() - LE_SCROLL_BAR_WIDTH, LE_SCROLL_BAR_WIDTH), true);
	func = bind(&leSelf::onHorizontalPositionChanged, this, scrollBar);
	scrollBar->setOnPositionChanged(func);
//	std::cout << "mHorizontalScrollBar: " << scrollBar << std::endl;
	addChild(scrollBar);
}

void CScrollView::setContent(CView::Ptr content)
{
	if (mContent)
	{
		removeChild(mContent);
	}
	mContent = content;
	addChild(mContent);
}

CView::Ptr CScrollView::content() const
{
	return mContent;
}

void CScrollView::draw(const CTheme* theme, CRenderingContext* context) const
{
	CView::draw(theme, context);
	if (mContent)
	{
		CRectangle rect = absoluteRect();

		rect.setWidth(rect.width() - LE_SCROLL_BAR_WIDTH);
		rect.setHeight(rect.height() - LE_SCROLL_BAR_WIDTH);
		context->pushClippingRect(rect);
		mContent->draw(theme, context);

		context->popClippingRect();
	}
}

void CScrollView::onVerticalPositionChanged(CScrollBar* scrollBar)
{
	if (mContent)
	{
		CPoint2D pos = absolutePosition();
		pos.setY(pos.y() - (mContent->size().height() - size().height() + LE_SCROLL_BAR_WIDTH) * scrollBar->position());
		mContent->setAbsolutePosition(pos);
		setNeedsRedraw();
	}
}

void CScrollView::onHorizontalPositionChanged(CScrollBar* scrollBar)
{
	if (mContent)
	{
		CPoint2D pos = absolutePosition();
		pos.setX(pos.x() - (mContent->size().width() - size().width() + LE_SCROLL_BAR_WIDTH) * scrollBar->position());
		mContent->setAbsolutePosition(pos);
		setNeedsRedraw();
	}
}

	} // namespace le
} // namespace sokira
