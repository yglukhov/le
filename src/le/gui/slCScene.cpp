#include "slCScene.h"
#include <le/gui/slCScreen.h>

namespace sokira
{
	namespace le
	{

CScene::CScene() :
	mScreen(NULL)
{

}

Bool CScene::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	return false;
}

//Bool CScene::mouseButtonPressed(EMouseButton button, const CPoint& point)
//{
//	return false;
//}
//
//Bool CScene::mouseButtonReleased(EMouseButton button, const CPoint& point)
//{
//	return false;
//}
//
//Bool CScene::mouseHovered(const CPoint& point)
//{
//	return false;
//}

Bool CScene::mouseEntered(const CPoint& point)
{
	return false;
}

Bool CScene::mouseExited(const CPoint& point)
{
	return false;
}

Bool CScene::onKeyDown(const CString& characters, ECharacterModifiers modifiers)
{
	return false;
}

Bool CScene::onKeyUp(const CString& characters, ECharacterModifiers modifiers)
{
	return false;
}

void CScene::draw(CRenderingContext* context)
{

}

void CScene::setScreen(CScreen* screen)
{
	mScreen = screen;
}

void CScene::setNeedsRedraw()
{
	if (mScreen) mScreen->setNeedsRedraw();
}

	} // namespace le
} // namespace sokira
