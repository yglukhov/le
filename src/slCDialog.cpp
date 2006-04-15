#include "slCDialog.h"
#include "slCTitleBar.h"
#include <debug/slDebug.h>
#include "slCScreen.h"

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CDialog);

CDialog::CDialog()
{
	LE_ENTER_LOG;
}

CDialog::CDialog(const CRectangle& rect) :
	CWindow(rect), mTitleBar(new CTitleBar(this))
{
	LE_ENTER_LOG;

	float border = borderWidth();

	// Create work area
	mWorkWindow = new CWindow(
		CRectangle(border, border*2 + mTitleBar->size().height(),
					  rect.width() - border*2, rect.height() - border*3 - mTitleBar->size().height()));
	mWorkWindow->autoResizing(eAlignSnapToAll);
	CWindow::addChild(mWorkWindow);

	// Add title bar
	CWindow::addChild(mTitleBar);
}

void CDialog::addChild(CControl* child)
{
	LE_ENTER_LOG;

	ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->addChild(child);
}

void CDialog::removeChild(CControl* child)
{
	LE_ENTER_LOG;

	ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->removeChild(child);
}

void CDialog::title(const char* titleString)
{
	mTitleBar->caption(titleString);
}


LE_NAMESPACE_END
