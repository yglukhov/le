#include "CWindow.h"
#include "CScreen.h"
#include "StdExtensions.h"
#include "ClassImplementation.h"
#include "CTheme.h"


IMPLEMENT_RUNTIME_CLASS(CWindow);

CWindow::CWindow(const CRectangle& rect) : CControl(rect)
{
	ENTER_LOG;
}

CWindow::~CWindow()
{
	ENTER_LOG;
	clearPointerContainer(mChilds);
}

void CWindow::draw() const
{
	ENTER_LOG;

	drawSelf();
	drawChilds();
}

void CWindow::drawSelf() const
{
	ENTER_LOG;
	CControl::draw();
}

void CWindow::drawChilds() const
{
	ENTER_LOG;

	CControlList::const_iterator end = mChilds.end();
	for(CControlList::const_iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->draw();
	}
}

void CWindow::addChild(CControl* child)
{
	ENTER_LOG;

	if(child)
	{
		mChilds.push_back(child);
		child->parent(this);
	}
}

void CWindow::removeChild(CControl* child)
{
	ENTER_LOG;

	mChilds.remove(child);
	CScreen::instance()->invalidate();
}

CSize CWindow::size() const
{
	ENTER_LOG;
	return CControl::size();
}

void CWindow::size(const CSize& Size)
{
	ENTER_LOG;

	CSize prevSize = mRect.size();
	CControl::size(Size);

	CControlList::iterator end = mChilds.end();
	for (CControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->parentResized(prevSize, mRect.size());
	}
}

void CWindow::absolutePosition(const CPoint& Position)
{
	ENTER_LOG;

	CPoint prevPos = mRect.position();
	CControl::absolutePosition(Position);

	CControlList::iterator end = mChilds.end();
	for (CControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->parentMoved(prevPos, Position);
	}
}

CPoint CWindow::absolutePosition() const
{
	ENTER_LOG;
	return CControl::absolutePosition();
}

void CWindow::relativePosition(const CPoint& Position)
{
	ENTER_LOG;

	CPoint prevPos = mRect.position();
	CControl::relativePosition(Position);

	CControlList::iterator end = mChilds.end();
	for (CControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->parentMoved(prevPos, mRect.position());
	}
}

bool CWindow::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	ENTER_LOG;

	CControlList::iterator end = mChilds.end();
	for (CControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		if (CTheme::instance()->hitTest(*it, point) && (*it)->onMouse(button, state, point))
			return true;
	}

	return CControl::onMouse(button, state, point);
}

//void CWindow::moveLastToDraw()
//{
//	if (mParent)
//	{
//		mParent->mChilds.remove(this);
//		mParent->mChilds.push_back(this);
//		mParent->moveLastToDraw();
//	}
//}
