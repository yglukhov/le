#include "CDecorator.h"
#include "Debug.h"

CDecorator::CDecorator(CControl* Child) :
	CControl(CRectangle()), mChild(NULL)
{
	if(Child)
	{
		child(Child);
	}
}

void CDecorator::child(CControl* Child)
{
	ASSERT(Child != NULL);

	mChild = Child;
	mRect = Child->mRect;

	Child->mRect.x(0);
	Child->mRect.y(0);

	Child->mParent = mParent;
}

//bool CDecorator::canLooseFocus()
//{
//	ASSERT(mChild != NULL);
//	return mChild->canLooseFocus();
//}
//
//bool CDecorator::canSetFocus()
//{
//	ASSERT(mChild != NULL);
//	return mChild->canSetFocus();
//}
//
//void CDecorator::onSetFocus()
//{
//	ASSERT(mChild != NULL);
//	mChild->onSetFocus();
//}
//
//void CDecorator::onLooseFocus()
//{
//	ASSERT(mChild != NULL);
//	mChild->onLooseFocus();
//}

bool CDecorator::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	ASSERT(mChild != NULL);
//	return mChild->onMouse(button, state, point);
	ASSERT(false);
}

//bool CDecorator::onMouseDownLeft(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseDownLeft(x, y);
//}
//
//bool CDecorator::onMouseDownRight(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseDownRight(x, y);
//}
//
//bool CDecorator::onMouseDownMiddle(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseDownMiddle(x, y);
//}
//
//bool CDecorator::onMouseUpLeft(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseUpLeft(x, y);
//}
//
//bool CDecorator::onMouseUpRight(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseUpRight(x, y);
//}
//
//bool CDecorator::onMouseUpMiddle(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseUpMiddle(x, y);
//}
//
//bool CDecorator::onMouseMove(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseMove(x, y);
//}
//
//bool CDecorator::onMouseClick(int x, int y)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onMouseClick(x, y);
//}

//bool CDecorator::onKeyPressed(unsigned char inKey)
//{
//	ASSERT(mChild != NULL);
//	return mChild->onKeyPressed(inKey);
//}

//void CDecorator::onResize(const CSize& size)
//{
//	ASSERT(mChild != NULL);
//	mChild->onResize(size);
//}