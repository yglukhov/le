#include <glut/slGlut.h>
//#include <OpenGL/OpenGL.h>

#include <map>
#include <iostream>

#include "slCScreen.h"
#include "slCDragger.h"
#include <le/core/debug/slDebug.h>
#include <le/core/auxiliary/slStdExtensions.h>

#include <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCCocoaScreenImpl.hp"
#define CScreenImpl CCocoaScreenImpl
#endif

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScreen);


typedef std::map<int, CScreen*> CScreenMap;
static CScreenMap	_screenMap;

CScreen::CScreen(bool fullscreen, const char* title, const CRectangle& rect) :
	CWindow(rect),
	mImpl(new CScreenImpl(fullscreen, title, rect)),
	mSizeChanged(true)
{
	LE_ENTER_LOG;

//	static_cast<CScreenImpl*>(mImpl)->setParent(this);
//	new CScreenImpl(fullscreen);

//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // non-stereo for main window
//
//	glutInitWindowPosition((int)rect.x(), (int)rect.y());
//	glutInitWindowSize((int)rect.width(), (int)rect.height());
//	mWindow = glutCreateWindow(title);
//
//	if(fullscreen)
//	{
//		glutFullScreen();
//	}
//
//	_screenMap[mWindow] = this;
//
//	// Initing params
//	glClearColor(0.4, 0.4, 0.4, 0.0); // Background color
//	glEnable(GL_DEPTH_TEST);
}

CScreen::~CScreen()
{
	LE_ENTER_LOG;
	clearPointerContainer(mControlsToDelete);
}

void CScreen::destroy()
{
	glutDestroyWindow(mWindow);
}

CScreen* CScreen::instance(int handle)
{
	LE_ENTER_LOG;
	return _screenMap[handle];
}

CScreen* CScreen::instance()
{
	LE_ENTER_LOG;
	return _screenMap[glutGetWindow()];
}

void CScreen::invalidate() const
{
	LE_ENTER_LOG;

//	glutSetWindow(mWindow);
//	glutPostRedisplay();
}

unsigned CScreen::instanceCount()
{
	LE_ENTER_LOG;
	return static_cast<unsigned>(_screenMap.size());
}

CSize CScreen::size() const
{
	LE_ENTER_LOG;
//	return mRect.size();
	return static_cast<CScreenImpl*>(mImpl)->size();
}

void CScreen::setSize(const CSize& size)
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

	// Handle live resize
	if (!mSizeChanged)
	{
		mSizeChanged = static_cast<CScreenImpl*>(mImpl)->inLiveResize();
	}

	if (mSizeChanged)
	{
		onResize();
		mSizeChanged = false;
	}

	std::cout << "CScreen::draw()" << std::endl;

//	CSize Size = CScreen::size();
//	glViewport(0, 0, (int)Size.width(), (int)Size.height());
//	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);

//	glClearColor(0, 0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glColor3f(1.0f, 0.85f, 0.35f);
//	glBegin(GL_TRIANGLES);
//	{
//		glVertex3f(0.0,  0.0, 0.0);
//		glVertex3f(0.0, 100.0, 0.0);
//		glVertex3f(100.0, 0.0, 0.0);
//	}
//	glEnd();
	drawChilds();

//	glFlush();

//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	drawChilds();
//	glutSwapBuffers();
}

//void CScreen::drawChilds()
//{
//	LE_ENTER_LOG;
//
//	CFaceList::const_iterator end = mChilds.end();
//	for(CFaceList::const_iterator it = mChilds.begin(); it != end; ++it)
//	{
//		(*it)->draw();
//	}
//}

void CScreen::absolutePosition(const CPoint& point)
{
	LE_ENTER_LOG;

	CControl::absolutePosition(point);

	glutSetWindow(mWindow);
	glutPositionWindow((int)point.x(), (int)point.y());
}

CPoint CScreen::absolutePosition() const
{
	LE_ENTER_LOG;
	return CPoint(0, 0);
}

CPoint CScreen::relativePosition() const // TODO: ...
{
	LE_ENTER_LOG;
	return CPoint(0, 0);
}

void CScreen::color(const CColor& Color)
{
	LE_ENTER_LOG;
	glClearColor(Color.red(), Color.green(), Color.blue(), 0.0);
}

int CScreen::handle() const
{
	LE_ENTER_LOG;
	return mWindow;
}

void CScreen::addControlToDelete(CControl* control)
{
	LE_ENTER_LOG;
	mControlsToDelete.push_back(control);
}

bool CScreen::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	LE_ENTER_LOG;

#if 1
	std::cout << "onMouse: (";
	if (button & eMouseButtonLeft)
		std::cout << " eMouseButtonLeft";
	if (button & eMouseButtonRight)
		std::cout << " eMouseButtonRight";
	if (button & eMouseButtonMiddle)
		std::cout << " eMouseButtonMiddle";

	std::cout << " ), (";

	if (state & eButtonStateUp)
		std::cout << " eButtonStateUp";
	if (state & eButtonStateDown)
		std::cout << " eButtonStateDown";

	std::cout << " ), (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif

	CDragger* curDragger = CDragger::currentDragger();
	if(curDragger)
	{
		curDragger->drag(point);
		curDragger->handler()->onMouse(button, state, point);
	}

	return CWindow::onMouse(button, state, point);

//	return onMouseFaces(button, state, point);
}

//bool CScreen::onMouseFaces(EMouseButton button, EButtonState state, const CPoint& point)
//{
//	LE_ENTER_LOG;
//
////	CFaceList::iterator end = mChilds.end();
////	for (CFaceList::iterator it = mChilds.begin(); it != end; ++it)
////	{
////		if ((*it)->hitTest(point) && (*it)->onMouse(button, state, point))
////			return true;
////	}
////
//
//	return CWindow::onMouse(button, state, point);
//}

//void CScreen::addChild(CFace* child)
//{
//	LE_ENTER_LOG;
//
//	if(child)
//	{
//		mChilds.push_back(child);
//	}
//}

//void CScreen::removeChild(CFace* child)
//{
//	LE_ENTER_LOG;
//
//	mChilds.remove(child);
//	invalidate();
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
	std::cout << "CScreen::_prepareOpenGL()" << std::endl;
}

void CScreen::_screenWasResized()
{
	mSizeChanged = true;
}

void CScreen::onMouseDown(EMouseButton button, const CPoint& point)
{
#if 1
	std::cout << "onMouseDown: (";
	if (button & eMouseButtonLeft)
		std::cout << " eMouseButtonLeft";
	if (button & eMouseButtonRight)
		std::cout << " eMouseButtonRight";
	if (button & eMouseButtonMiddle)
		std::cout << " eMouseButtonMiddle";

	std::cout << " ), (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif
}

void CScreen::onMouseUp(EMouseButton button, const CPoint& point)
{
#if 1
	std::cout << "onMouseUp: (";
	if (button & eMouseButtonLeft)
		std::cout << " eMouseButtonLeft";
	if (button & eMouseButtonRight)
		std::cout << " eMouseButtonRight";
	if (button & eMouseButtonMiddle)
		std::cout << " eMouseButtonMiddle";

	std::cout << " ), (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif
}

void CScreen::onMouseHover(const CPoint& point)
{
#if 1
	std::cout << "onMouseHover: (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif
}

void CScreen::onMouseOut(const CPoint& point)
{
#if 1
	std::cout << "onMouseOut: (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif
}

void CScreen::onMouseIn(const CPoint& point)
{
#if 1
	std::cout << "onMouseIn: (" << point.x() << ", " << point.y() << ")" << std::endl;
#endif
}

// This method is always called within valid OpenGL context
void CScreen::onResize()
{
	CSize size = static_cast<CScreenImpl*>(mImpl)->size();
	glViewport(0, 0, (int)size.width(), (int)size.height());
	glOrtho(0, (int)size.width(), (int)size.height(), 0, -1, 1);
//	std::cout << "CScreen::onResize(" << size.width() << "," << size.height() << ")" << std::endl;
}

	} // namespace le
} // namespace sokira
