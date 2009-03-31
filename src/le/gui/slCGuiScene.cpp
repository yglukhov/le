#include <le/gui/slCTheme.h>
#include <le/gui/slCControl.h>
#include "slCGuiScene.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CGuiScene);

CGuiScene::CGuiScene() :
	mFirstResponder(NULL)
{

}

#define COUT_MOUSE_EVENTS 1

Bool CGuiScene::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
//#if COUT_MOUSE_EVENTS
//	std::cout << "CControlBasicController::performMouse: (";
//	if (button & eMouseButtonLeft)
//		std::cout << " eMouseButtonLeft";
//	if (button & eMouseButtonRight)
//		std::cout << " eMouseButtonRight";
//	if (button & eMouseButtonMiddle)
//		std::cout << " eMouseButtonMiddle";
//
//	std::cout << " ), (";
//
//	if (state == eButtonStateUp)
//		std::cout << " eButtonStateUp";
//	if (state == eButtonStateDown)
//		std::cout << " eButtonStateDown";
//
//	std::cout << " ), (" << point.x() << ", " << point.y() << ")" << std::endl;
//#endif

	if (mFirstResponder && mTheme.onMouse(button, state, point, mFirstResponder))
		return true;		

	return mTheme.onMouse(button, state, point, this);
}

Bool CGuiScene::mouseEntered(const CPoint& point)
{
	return false;
}

Bool CGuiScene::mouseExited(const CPoint& point)
{
	return false;
}

void CGuiScene::draw(CRenderingContext* context)
{
	const CControlList& theChildren = children();
	CControlList::const_iterator end = theChildren.end();
	for(CControlList::const_iterator it = theChildren.begin(); it != end; ++it)
	{
		mTheme.drawControl(*it, context);
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

	} // namespace le
} // namespace sokira
