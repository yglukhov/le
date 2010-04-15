#include <le/gui/slCTheme.h>
#include <le/gui/slCControl.h>
#include "slCGuiScene.h"
#include "slCScreen.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CGuiScene);

CGuiScene::CGuiScene() :
	mFirstResponder(NULL)
{

}

Bool CGuiScene::onMouse(EMouseButton button, EButtonState state, const CPoint2D& point)
{
	if (mFirstResponder && mFirstResponder->onMouse(button, state, point))
		return true;

	return CWindow::onMouse(button, state, point);
}

Bool CGuiScene::mouseEntered(const CPoint2D& point)
{
	return false;
}

Bool CGuiScene::mouseExited(const CPoint2D& point)
{
	return false;
}

void CGuiScene::draw(CRenderingContext* context)
{
	const CControlList& theChildren = children();
	CControlList::const_iterator end = theChildren.end();
	for(CControlList::const_iterator it = theChildren.begin(); it != end; ++it)
	{
		(*it)->draw(&mTheme, context);
	}
}

void CGuiScene::setNeedsRedraw()
{
	CScene::setNeedsRedraw();
}

Bool CGuiScene::childBecomesFirstResponder(CControl* child, CWindow* parent)
{
	Bool firstResponderCanResign = true;
	if (mFirstResponder == child ||
		(mFirstResponder && !mFirstResponder->controlCanResignFirstResponder()))
		firstResponderCanResign = false;

	if (firstResponderCanResign)
	{
		CControl* controlToMove = (parent)?(parent):(child);
		mChildren.remove(controlToMove);
		mChildren.push_back(controlToMove);
		if (mFirstResponder) mFirstResponder->controlDidResignFirstResponder();
		mFirstResponder = child;
		return true;
	}

	return false;
}

Bool CGuiScene::isChildFirstResponder(const CControl* child) const
{
	return child == mFirstResponder;
}

void CGuiScene::setScreen(CScreen* screen)
{
	CScene::setScreen(screen);
	setSize(screen->size()); // Resize to fit the screen
}

Bool CGuiScene::hitTest(const CPoint2D& point) const
{
	return true;
}


	} // namespace le
} // namespace sokira
