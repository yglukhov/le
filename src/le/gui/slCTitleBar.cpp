
#include "slCTitleBar.h"
#include "slCButton.h"
#include "slCText.h"
#include "slCScreen.h"

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CTitleBar);

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
	mCloseButton->relativePosition(CPoint(1,1));					
	mCloseButton->size(CSize(10,10));
	mCloseButton->delegate(this);
	autoResizing(eAlignTop | eAlignLeft | eAlignRight);
}

CTitleBar::CTitleBar(CWindow* Parent) :
	CDragger(Parent, this),
	mCloseButton(new CButton())
{
	LE_ENTER_LOG;

	LE_ASSERT_EX(Parent != NULL);
	addChild(mCloseButton);
	mCloseButton->relativePosition(CPoint(1,1));					
	mCloseButton->size(CSize(8,8));
	mCloseButton->delegate(this);

	autoResizing(eAlignTop | eAlignLeft | eAlignRight);
	float border = Parent->borderWidth();
	relativePosition(CPoint(border, border));
	size(CSize(Parent->size().width() - 2*border, 10));
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
	CScreen::instance()->invalidate();
}

const CText& CTitleBar::captionText() const
{
	return mCaption;
}


LE_NAMESPACE_END
