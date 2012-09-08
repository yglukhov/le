#include <map>
#include <iostream>

#include <le/gui/slOpenGL.h>

#include "slCWindow.h"
#include <le/core/debug/slDebug.h>

#include <le/core/config/slCompiler.h>
#include <le/core/slCClassFactory.h>
#include <le/core/auxiliary/slCRunLoop.h>

#include <le/gui/slCRenderingContext.h>

#include <le/core/slCImage.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#include "base/slCCocoaWindowImpl.hp"
#define CWindowImpl CCocoaWindowImpl
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCWindowsWindowImpl.hp"
#define CWindowImpl CWindowsWindowImpl
#endif

LE_LINK_MODULE_DEPENDENCY(COpenGLRenderingContext);

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CWindow);


CWindow::CWindow(bool fullscreen, const CString& title, const CRectangle& rect) :
	CView(CRectangle(CPoint2D(), rect.size())),
	mTitle(title),
	mFullScreen(fullscreen),
	mPositionOnScreen(rect.position()),
	mImpl(NULL)
{
	LE_ENTER_LOG;
}

CWindow::~CWindow()
{
	CImage image;
	LE_ENTER_LOG;
	delete static_cast<CWindowImpl*>(mImpl);
}

void* CWindow::createImpl()
{
	return static_cast<void*>(new CWindowImpl(mFullScreen, mTitle, CRectangle(mPositionOnScreen, size())));
}

void CWindow::setNeedsRedraw()
{
	LE_ENTER_LOG;

	if (mImpl) static_cast<CWindowImpl*>(mImpl)->setNeedsRedraw();
}

void CWindow::setSize(const CSize2D& size)
{
	LE_ENTER_LOG;


//	glutSetWindow(mWindow);
//	glutReshapeWindow((int)Size.width(), (int)Size.height());
//	glLoadIdentity();
//	glViewport(0, 0, (int)Size.width(), (int)Size.height());
//	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);

	if (mImpl) static_cast<CWindowImpl*>(mImpl)->setSize(size);
	CView::setSize(size);
}

void CWindow::draw()
{
	LE_ASSERT(mRenderingContext);
	mRenderingContext->beginDrawing();
	recursiveDraw(&mTheme, mRenderingContext);
	mRenderingContext->endDrawing();
}

void CWindow::draw(const CTheme* theme, CRenderingContext* context) const
{
	CView::draw(theme, context);
}

void CWindow::setAbsolutePosition(const CPoint2D& point)
{
	LE_ENTER_LOG;

//	CControl::setAbsolutePosition(point);

//	glutSetWindow(mWindow);
//	glutPositionWindow((int)point.x(), (int)point.y());
}

CPoint2D CWindow::absolutePosition() const
{
	LE_ENTER_LOG;
	return CPoint2D(0, 0);
}

CPoint2D CWindow::relativePosition() const // TODO: ...
{
	LE_ENTER_LOG;
	return CPoint2D(0, 0);
}

CString CWindow::title() const
{
	return mTitle;
}

CWindow* CWindow::window() const
{
	return const_cast<CWindow*>(this);
}

//void CWindow::addControlToDelete(CControl* control)
//{
//	LE_ENTER_LOG;
////	mControlsToDelete.push_back(control);
//}

void CWindow::screenWillBeAddedToApplication(CGuiApplication* app)
{
	if (!mImpl)
	{
		mImpl = createImpl();
	}
	if (mImpl) static_cast<CWindowImpl*>(mImpl)->screenWillBeAddedToApplication(this, app);
}

void CWindow::screenWasAddedToApplication(CGuiApplication* app)
{
	if (mImpl) static_cast<CWindowImpl*>(mImpl)->screenWasAddedToApplication(this, app);
}

void CWindow::screenWillBeRemovedFromApplication(CGuiApplication* app)
{
	if (mImpl) static_cast<CWindowImpl*>(mImpl)->screenWillBeRemovedFromApplication(this, app);
}

void CWindow::screenWasRemovedFromApplication(CGuiApplication* app)
{
	if (mImpl) static_cast<CWindowImpl*>(mImpl)->screenWasRemovedFromApplication(this, app);
}

void CWindow::prepareRenderingContext()
{
	CClass rendererClass = CClassFactory::defaultInstance()->bestSubclassOfClassWithParameters(CRenderingContext::staticClass(), CDictionary());
	mRenderingContext = rendererClass.create<CRenderingContext>();
}

void CWindow::_screenWillBeClosed()
{
	delete static_cast<CWindowImpl*>(mImpl);
	mImpl = NULL;
}


// This event includes mouse up, mouse down and mouse hover.
//Bool CWindow::onMouse(EKeyCode button, EButtonState state, const CPoint2D& point)
//{
////	std::cout << "CWindow::onMouse: " << title() << std::endl;
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->onMouse(button, state, point);
////	}
////	mContentView->onMouse(button, state, point);
//	std::cout << "Screen::onMouse" << std::endl;
//	return CView::onMouse(button, state, point);
//}
//
//void CWindow::onMouseIn(const CPoint2D& point)
//{
//	mContentView->onMouseIn(point);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->mouseEntered(point);
////	}
//}
//
//void CWindow::onMouseOut(const CPoint2D& point)
//{
//	mContentView->onMouseOut(point);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->mouseExited(point);
////	}
//}

//void CWindow::onKeyDown(const CString& characters, ECharacterModifiers modifiers)
//{
////	mContentView->onKeyDown(characters, modifiers);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		if ((*it)->onKeyDown(characters, modifiers)) break;
////	}
//}

//void CWindow::onKeyUp(const CString& characters, ECharacterModifiers modifiers)
//{
////	mContentView->onKeyUp(characters, modifiers);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		if ((*it)->onKeyUp(characters, modifiers)) break;
////	}
//}

Bool CWindow::handleEvent(CEvent* event)
{
	Bool result = false;
	if (event->isMouseEvent())
	{
		result = onMouse(event->mouseButton(), event->buttonState(), event->mouseLocation());
	}
	else if (event->isKeyboardEvent())
	{
		if (event->buttonState() == eButtonStateUp)
		{
			result = onKeyUp(event->keyCode());
		}
		else
		{
			result = onKeyDown(event->keyCode());
		}
	}

	return result;
}

// This method is always called within valid OpenGL context
void CWindow::onResize()
{
	CSize2D size = static_cast<CWindowImpl*>(mImpl)->size();

//	std::cout << "CWindow::onResize: " << mSize.width() << ", " << mSize.height() << std::endl;
//	std::cout << "{" << std::endl;

	glViewport(0, 0, (int)size.width(), (int)size.height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (int)size.width(), (int)size.height(), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	CView::setSize(size);

//	mContentView->setSize(mSize);

//	CSceneList::const_iterator end = mScenes.end();
//	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
//	{
//		CGuiScene* scene = dynamic_cast<CGuiScene*> (*it);
//		if (scene) scene->setSize(mSize);
//	}

//	std::cout << "}" << std::endl;
//	setNeedsRedraw();
}

CRenderingContext::Ptr CWindow::renderingContext()
{
	return mRenderingContext;
}

	} // namespace le
} // namespace sokira
