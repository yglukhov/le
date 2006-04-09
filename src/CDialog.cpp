#include "CDialog.h"
#include "CTitleBar.h"
#include <debug/Debug.h>
#include "CScreen.h"

IMPLEMENT_RUNTIME_CLASS(CDialog);

CDialog::CDialog()
{
	ENTER_LOG;
}

CDialog::CDialog(const CRectangle& rect) :
	CWindow(rect), mTitleBar(new CTitleBar(this))
{
	ENTER_LOG;

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
	ENTER_LOG;

	ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->addChild(child);
}

void CDialog::removeChild(CControl* child)
{
	ENTER_LOG;

	ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->removeChild(child);
}

void CDialog::title(const char* titleString)
{
	mTitleBar->caption(titleString);
}