#include "slCWindow.h"
#include "slCScreen.h"
#include <le/core/auxiliary/slStdExtensions.h>
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CWindow);

CWindow::CWindow(const CRectangle& rect) : CControl(rect)
{
	LE_ENTER_LOG;
}

CWindow::~CWindow()
{
	LE_ENTER_LOG;
	clearPointerContainer(mChilds);
}

void CWindow::draw() const
{
	LE_ENTER_LOG;

	drawSelf();
	drawChilds();
}

void CWindow::drawSelf() const
{
	LE_ENTER_LOG;
	CControl::draw();
}

void CWindow::drawChilds() const
{
	LE_ENTER_LOG;

	CControlList::const_iterator end = mChilds.end();
	for(CControlList::const_iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->draw();
	}
}

void CWindow::addChild(CControl* child)
{
	LE_ENTER_LOG;

	if(child)
	{
		mChilds.push_back(child);

		child->parent(this);
		child->face(mFace);
	}
}

void CWindow::removeChild(CControl* child)
{
	LE_ENTER_LOG;

	mChilds.remove(child);
	CScreen::instance()->invalidate();
}

CSize CWindow::size() const
{
	LE_ENTER_LOG;
	return CControl::size();
}

void CWindow::setSize(const CSize& Size)
{
	LE_ENTER_LOG;

	CSize prevSize = mRect.size();
	CControl::setSize(Size);

	CControlList::iterator end = mChilds.end();
	for (CControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->parentResized(prevSize, mRect.size());
	}
}

void CWindow::absolutePosition(const CPoint& Position)
{
	LE_ENTER_LOG;

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
	LE_ENTER_LOG;
	return CControl::absolutePosition();
}

void CWindow::relativePosition(const CPoint& Position)
{
	LE_ENTER_LOG;

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
	LE_ENTER_LOG;

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


	} // namespace le
} // namespace sokira
