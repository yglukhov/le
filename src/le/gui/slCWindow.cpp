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
	clearPointerContainer(mChildren);
}

void CWindow::addChild(CControl* child)
{
	LE_ENTER_LOG;

	if(child)
	{
		mChildren.push_back(child);

		child->setParent(this);
	}
}

void CWindow::removeChild(CControl* child)
{
	LE_ENTER_LOG;

	mChildren.remove(child);
	setNeedsRedraw();
}

void CWindow::draw(const CTheme* theme, CRenderingContext* context) const
{
	if (isVisible())
	{
		theme->drawWindow(this, context);
		CControlList::const_iterator end = mChildren.end();
		for (CControlList::const_iterator it = mChildren.begin(); it != end; ++it)
		{
			(*it)->draw(theme, context);
		}
	}
}

Bool CWindow::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	if (hitTest(point))
	{
		CWindow::CControlList::const_iterator end = mChildren.end();
		for (CWindow::CControlList::const_iterator it = mChildren.begin(); it != end; ++it)
		{
			if ((*it)->onMouse(button, state, point)) return true;
		}

		return performMouse(button, state, point);
	}

	return false;
}

CSize2D CWindow::size() const
{
	LE_ENTER_LOG;
	return CControl::size();
}

void CWindow::setSize(const CSize2D& size)
{
	LE_ENTER_LOG;

	CSize2D prevSize = mRect.size();
	CControl::setSize(size);

	CControlList::iterator end = mChildren.end();
	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
	{
		(*it)->parentResized(prevSize, mRect.size());
	}
}

void CWindow::setAbsolutePosition(const CPoint& position)
{
	LE_ENTER_LOG;

	CPoint prevPos = mRect.position();
	CControl::setAbsolutePosition(position);
	moveChildren(CSize2D(position.x() - prevPos.x(), position.y() - prevPos.y()));
}

void CWindow::setRelativePosition(const CPoint& position)
{
	LE_ENTER_LOG;

	CPoint prevPos = mRect.position();
	CControl::setRelativePosition(position);
	CPoint newPos = mRect.position();
	moveChildren(CSize2D(newPos.x() - prevPos.x(), newPos.y() - prevPos.y()));
}

void CWindow::moveChildren(const CSize2D& delta)
{
	CControlList::iterator end = mChildren.end();
	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
	{
		CPoint prevPos = (*it)->absolutePosition();
		(*it)->setAbsolutePosition(
			CPoint(prevPos.x() + delta.width(), prevPos.y() + delta.height())
				);
	}
}

Bool CWindow::childBecomesFirstResponder(CControl* child, CWindow* parent)
{
	if (mParent)
	{
		if (mParent->childBecomesFirstResponder(child, this))
		{
			CControl* controlToMove = (parent)?(parent):(child);

			mChildren.remove(controlToMove);
			mChildren.push_back(controlToMove);
			return true;
		}
	}

	return false;
}

Bool CWindow::isChildFirstResponder(const CControl* child) const
{
	return mParent && mParent->isChildFirstResponder(child);
}


//Bool CWindow::mouseButtonPressed(EMouseButton button, const CPoint& point, const CTheme* theme)
//{
//	CControlList::iterator end = mChildren.end();
//	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
//	{
//		if (theme->hitTest(*it, point) && (*it)->mouseButtonPressed(button, point, theme))
//			return true;
//	}
//
//	return CControl::mouseButtonPressed(button, point, theme);
//}
//
//Bool CWindow::mouseButtonReleased(EMouseButton button, const CPoint& point, const CTheme* theme)
//{
//	CControlList::iterator end = mChildren.end();
//	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
//	{
//		if (theme->
//		if (theme->hitTest(*it, point) && (*it)->mouseButtonReleased(button, point, theme))
//			return true;
//	}
//
//	return CControl::mouseButtonReleased(button, point, theme);
//}
//
//Bool CWindow::mouseHovered(const CPoint& point, const CTheme* theme)
//{
//	CControlList::iterator end = mChildren.end();
//	for (CControlList::iterator it = mChildren.begin(); it != end; ++it)
//	{
//		if (theme->hitTest(*it, point) && (*it)->mouseHovered(point, theme))
//			return true;
//	}
//
//	return CControl::mouseHovered(point, theme);
//}

//Bool CWindow::mouseExited(const CPoint& point, const CTheme* theme)
//{
//	return onMouseOut(point);
//}
//
//Bool CWindow::mouseEntered(const CPoint& point, const CTheme* theme)
//{
//	return onMouseOut(point);
//}

//void CWindow::moveLastToDraw()
//{
//	if (mParent)
//	{
//		mParent->mChildren.remove(this);
//		mParent->mChildren.push_back(this);
//		mParent->moveLastToDraw();
//	}
//}


	} // namespace le
} // namespace sokira
