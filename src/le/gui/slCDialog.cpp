#if 0

#include "slCDialog.h"
#include "slCTitleBar.h"
#include <le/core/debug/slDebug.h>
#include "slCWindow.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CDialog);

CDialog::CDialog()
{
	LE_ENTER_LOG;
}

CDialog::CDialog(const CRectangle& rect) :
	CView(rect), mTitleBar(new CTitleBar(this))
{
	LE_ENTER_LOG;

	float border = borderWidth();

	// Create work area
	mWorkWindow = new CView(
		CRectangle(border, border*2 + mTitleBar->size().height(),
					  rect.width() - border*2, rect.height() - border*3 - mTitleBar->size().height()));
	mWorkWindow->setAutoResizing(eAutoResizingFixedMargins);
	CView::addChild(mWorkWindow);

	// Add title bar
	CView::addChild(mTitleBar);
}

void CDialog::addChild(CControl* child)
{
	LE_ENTER_LOG;

	LE_ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->addChild(child);
}

void CDialog::removeChild(CControl* child)
{
	LE_ENTER_LOG;

	LE_ASSERT_EX(mWorkWindow != NULL);
	mWorkWindow->removeChild(child);
}

void CDialog::title(const char* titleString)
{
	mTitleBar->caption(titleString);
}


	} // namespace le
} // namespace sokira

#endif