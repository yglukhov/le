#include <glut/slGlut.h>
//#include <OpenGL/OpenGL.h>
//#include <OpenGLES/ES1/gl.h>

#include <map>
#include <iostream>

#include "slCScreen.h"
#include <le/core/debug/slDebug.h>

#include <le/core/config/slCompiler.h>

#include <le/gui/slCOpenGLRenderingContext.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCCocoaScreenImpl.hp"
#define CScreenImpl CCocoaScreenImpl
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCScreenWindowsImpl.hp"
#define CScreenImpl CScreenWindowsImpl
#endif

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScreen);


CScreen::CScreen(bool fullscreen, const CString& title, const CRectangle& rect) :
	CWindow(CRectangle(CPoint2D(), rect.size())),
	mImpl(new CScreenImpl(fullscreen, title, rect)),
	mRenderingContext(NULL)
{
	LE_ENTER_LOG;
}

CScreen::~CScreen()
{
	LE_ENTER_LOG;
	delete mRenderingContext;
	delete static_cast<CScreenImpl*>(mImpl);
}

void CScreen::setNeedsRedraw()
{
	LE_ENTER_LOG;

	if (mImpl) static_cast<CScreenImpl*>(mImpl)->setNeedsRedraw();
}

CSize2D CScreen::size() const
{
	LE_ENTER_LOG;
//	return mRect.size();
	return static_cast<CScreenImpl*>(mImpl)->size();
}

void CScreen::setSize(const CSize2D& size)
{
	LE_ENTER_LOG;


//	glutSetWindow(mWindow);
//	glutReshapeWindow((int)Size.width(), (int)Size.height());
//	glLoadIdentity();
//	glViewport(0, 0, (int)Size.width(), (int)Size.height());
//	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);

	static_cast<CScreenImpl*>(mImpl)->setSize(size);
	CWindow::setSize(size);
}

void CScreen::draw()
{
	LE_ENTER_LOG;

	LE_ASSERT(mRenderingContext);

//	std::cout << "CScreen::draw()" << std::endl;

//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//	CRenderingContext* context = NULL; //static_cast<CScreenImpl*>(mImpl)->renderingContext();
//	context->clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0,0);
	glVertex2f(50, 0);
	glVertex2f(0, 50);
	glEnd();
*/
	CWindow::draw(&mTheme, mRenderingContext);

//	CSceneList::const_iterator end = mScenes.end();
//	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
//	{
//		(*it)->draw(mRenderingContext);
//	}

//	mContentView->draw(&mTheme, mRenderingContext);

//	CSize2D Size = CScreen::size();
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

void CScreen::setAbsolutePosition(const CPoint2D& point)
{
	LE_ENTER_LOG;

//	CControl::setAbsolutePosition(point);

//	glutSetWindow(mWindow);
//	glutPositionWindow((int)point.x(), (int)point.y());
}

CPoint2D CScreen::absolutePosition() const
{
	LE_ENTER_LOG;
	return CPoint2D(0, 0);
}

CPoint2D CScreen::relativePosition() const // TODO: ...
{
	LE_ENTER_LOG;
	return CPoint2D(0, 0);
}

CString CScreen::title() const
{
	return static_cast<CScreenImpl*>(mImpl)->title();
}

void CScreen::color(const CColor& Color)
{
	LE_ENTER_LOG;
	glClearColor(Color.red(), Color.green(), Color.blue(), 0.0);
}

//void CScreen::addControlToDelete(CControl* control)
//{
//	LE_ENTER_LOG;
////	mControlsToDelete.push_back(control);
//}

void CScreen::screenWillBeAddedToApplication(CGuiApplication* app)
{
	static_cast<CScreenImpl*>(mImpl)->screenWillBeAddedToApplication(this, app);
}

void CScreen::screenWasAddedToApplication(CGuiApplication* app)
{
	static_cast<CScreenImpl*>(mImpl)->screenWasAddedToApplication(this, app);
}

void CScreen::screenWillBeRemovedFromApplication(CGuiApplication* app)
{
	static_cast<CScreenImpl*>(mImpl)->screenWillBeRemovedFromApplication(this, app);
}

void CScreen::screenWasRemovedFromApplication(CGuiApplication* app)
{
	static_cast<CScreenImpl*>(mImpl)->screenWasRemovedFromApplication(this, app);
}

void CScreen::_prepareOpenGL()
{
	mRenderingContext = new COpenGLRenderingContext();
}

void CScreen::_screenWillBeClosed()
{
	delete static_cast<CScreenImpl*>(mImpl);
	mImpl = NULL;
}

//CWindow* CScreen::contentView()
//{
//	return mContentView;
//}

// This event includes mouse up, mouse down and mouse hover.
//Bool CScreen::onMouse(EKeyCode button, EButtonState state, const CPoint2D& point)
//{
////	std::cout << "CScreen::onMouse: " << title() << std::endl;
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->onMouse(button, state, point);
////	}
////	mContentView->onMouse(button, state, point);
//	std::cout << "Screen::onMouse" << std::endl;
//	return CWindow::onMouse(button, state, point);
//}
//
//void CScreen::onMouseIn(const CPoint2D& point)
//{
//	mContentView->onMouseIn(point);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->mouseEntered(point);
////	}
//}
//
//void CScreen::onMouseOut(const CPoint2D& point)
//{
//	mContentView->onMouseOut(point);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		(*it)->mouseExited(point);
////	}
//}

//void CScreen::onKeyDown(const CString& characters, ECharacterModifiers modifiers)
//{
////	mContentView->onKeyDown(characters, modifiers);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		if ((*it)->onKeyDown(characters, modifiers)) break;
////	}
//}

//void CScreen::onKeyUp(const CString& characters, ECharacterModifiers modifiers)
//{
////	mContentView->onKeyUp(characters, modifiers);
////	CSceneList::const_iterator end = mScenes.end();
////	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
////	{
////		if ((*it)->onKeyUp(characters, modifiers)) break;
////	}
//}

// This method is always called within valid OpenGL context
void CScreen::onResize()
{
	CSize2D size = static_cast<CScreenImpl*>(mImpl)->size();

//	std::cout << "CScreen::onResize: " << mSize.width() << ", " << mSize.height() << std::endl;
//	std::cout << "{" << std::endl;

	glViewport(0, 0, (int)size.width(), (int)size.height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (int)size.width(), (int)size.height(), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	CWindow::setSize(size);

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

	} // namespace le
} // namespace sokira
