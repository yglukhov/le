
#include "slCTitleBar.h"
#include "slCButton.h"
#include "slCText.h"
#include "slCScreen.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTitleBar);

//bool closeButtonPressed(int x,int y, CControl* sender)
//{
//	if (sender->parent())
//	{
//		sender->parent()->destroy();
////		sender->parent()->parent()->parent()->deleteChild(sender->parent()->parent());
//	}
//	return false;
//}

CTitleBar::CTitleBar() :
	CDragger(NULL, this),
	mCloseButton(new CButton())
{
	LE_ENTER_LOG;
	addChild(mCloseButton);
	mCloseButton->setRelativePosition(CPoint(1,1));
	mCloseButton->setSize(CSize2D(10,10));
	mCloseButton->delegate(this);
	setAutoResizing(eAutoResizingFixedTopLeft | eAutoResizingFixedRight);
}

CTitleBar::CTitleBar(CWindow* Parent) :
	CDragger(Parent, this),
	mCloseButton(new CButton())
{
	LE_ENTER_LOG;

	LE_ASSERT_EX(Parent != NULL);
	addChild(mCloseButton);
	mCloseButton->setRelativePosition(CPoint(1,1));
	mCloseButton->setSize(CSize2D(8,8));
	mCloseButton->delegate(this);

	setAutoResizing(eAutoResizingFixedTopLeft | eAutoResizingFixedRight);
	float border = Parent->borderWidth();
	setRelativePosition(CPoint(border, border));
	setSize(CSize2D(Parent->size().width() - 2*border, 10));
	parent(Parent);
}

bool CTitleBar::onMouseLeftDown(const CPoint& point, CControl* sender)
{
	LE_ENTER_LOG;

	if (sender == mCloseButton)
	{
		return true;
	}

	startDrag(point);
	return true;
}

bool CTitleBar::onMouseLeftUp(const CPoint& point, CControl* sender)
{
	LE_ENTER_LOG;

	endDrag();

	if (sender == mCloseButton)
	{
		parent()->destroy();
		return true;
	}

	return true;
}

void CTitleBar::caption(const char* captionString)
{
	mCaption.text(captionString);
	setNeedsRedraw();
}

const CText& CTitleBar::captionText() const
{
	return mCaption;
}


	} // namespace le
} // namespace sokira
