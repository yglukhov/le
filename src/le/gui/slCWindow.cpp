#include <glut/slGlut.h>
//#include <OpenGL/OpenGL.h>
//#include <OpenGLES/ES1/gl.h>

#include <map>
#include <iostream>

#include "slCWindow.h"
#include <le/core/debug/slDebug.h>

#include <le/core/config/slCompiler.h>

#include <le/gui/slCOpenGLRenderingContext.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCCocoaWindowImpl.hp"
#define CWindowImpl CCocoaWindowImpl
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCWindowsWindowImpl.hp"
#define CWindowImpl CWindowsWindowImpl
#endif

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CWindow);


CWindow::CWindow(bool fullscreen, const CString& title, const CRectangle& rect) :
	CView(CRectangle(CPoint2D(), rect.size())),
	mImpl(new CWindowImpl(fullscreen, title, rect)),
	mRenderingContext(NULL)
{
	LE_ENTER_LOG;
}

CWindow::~CWindow()
{
	LE_ENTER_LOG;
	delete mRenderingContext;
	delete static_cast<CWindowImpl*>(mImpl);
}

void CWindow::setNeedsRedraw()
{
	LE_ENTER_LOG;

	if (mImpl) static_cast<CWindowImpl*>(mImpl)->setNeedsRedraw();
}

CSize2D CWindow::size() const
{
	LE_ENTER_LOG;
//	return mRect.size();
	return static_cast<CWindowImpl*>(mImpl)->size();
}

void CWindow::setSize(const CSize2D& size)
{
	LE_ENTER_LOG;


//	glutSetWindow(mWindow);
//	glutReshapeWindow((int)Size.width(), (int)Size.height());
//	glLoadIdentity();
//	glViewport(0, 0, (int)Size.width(), (int)Size.height());
//	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);

	static_cast<CWindowImpl*>(mImpl)->setSize(size);
	CView::setSize(size);
}

void CWindow::draw()
{
	LE_ENTER_LOG;

	LE_ASSERT(mRenderingContext);

//	std::cout << "CWindow::draw()" << std::endl;

//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//	CRenderingContext* context = NULL; //static_cast<CWindowImpl*>(mImpl)->renderingContext();
//	context->clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
/*
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0,0);
	glVertex2f(50, 0);
	glVertex2f(0, 50);
	glEnd();
*/
	CView::draw(&mTheme, mRenderingContext);

//	CSceneList::const_iterator end = mScenes.end();
//	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
//	{
//		(*it)->draw(mRenderingContext);
//	}

//	mContentView->draw(&mTheme, mRenderingContext);

//	CSize2D Size = CWindow::size();
//	glViewport(0, 0, (int)Size.width(), (int)Size.height());
//	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);

//	glClearColor(0, 0, 0.0, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glColor3f(1.0f, 0.85f, 0.35f);
//	glBegin(GL_TRIANGLES);
//	{
//		glVertex3f(0.0,  0.0, 0.0);
//		glVertex3f(0.0, 100.0, 0.0);
//		glVertex3f(100.0, 0.0, 0.0);
//	}
//	glEnd();
//	drawChilds();

//	glFlush();

//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	drawChilds();
//	glutSwapBuffers();
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
	return static_cast<CWindowImpl*>(mImpl)->title();
}

void CWindow::color(const CColor& Color)
{
	LE_ENTER_LOG;
	glClearColor(Color.red(), Color.green(), Color.blue(), 0.0);
}

//void CWindow::addControlToDelete(CControl* control)
//{
//	LE_ENTER_LOG;
////	mControlsToDelete.push_back(control);
//}

void CWindow::screenWillBeAddedToApplication(CGuiApplication* app)
{
	static_cast<CWindowImpl*>(mImpl)->screenWillBeAddedToApplication(this, app);
}

void CWindow::screenWasAddedToApplication(CGuiApplication* app)
{
	static_cast<CWindowImpl*>(mImpl)->screenWasAddedToApplication(this, app);
}

void CWindow::screenWillBeRemovedFromApplication(CGuiApplication* app)
{
	static_cast<CWindowImpl*>(mImpl)->screenWillBeRemovedFromApplication(this, app);
}

void CWindow::screenWasRemovedFromApplication(CGuiApplication* app)
{
	static_cast<CWindowImpl*>(mImpl)->screenWasRemovedFromApplication(this, app);
}

void CWindow::_prepareOpenGL()
{
	mRenderingContext = new COpenGLRenderingContext();
}

void CWindow::_screenWillBeClosed()
{
	delete static_cast<CWindowImpl*>(mImpl);
	mImpl = NULL;
}

//CView* CWindow::contentView()
//{
//	return mContentView;
//}

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

CRenderingContext* CWindow::renderingContext()
{
	return mRenderingContext;
}

	} // namespace le
} // namespace sokira
