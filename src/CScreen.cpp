#include <glut/le_glut.h>

#include <map>

#include "CScreen.h"
#include "CDragger.h"
#include <debug/Debug.h>
#include "StdExtensions.h"

IMPLEMENT_RUNTIME_CLASS(CScreen);


typedef std::map<int, CScreen*> CScreenMap;
static CScreenMap	_screenMap;

CScreen::CScreen(bool fullscreen, const char* title, const CRectangle& rect) :
	CWindow(rect)
{
	ENTER_LOG;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // non-stereo for main window

	glutInitWindowPosition((int)rect.x(), (int)rect.y());
	glutInitWindowSize((int)rect.width(), (int)rect.height());
	mWindow = glutCreateWindow(title);

	if(fullscreen)
	{
		glutFullScreen();
	}
	
	_screenMap[mWindow] = this;

	// Initing params
	glClearColor(0.4, 0.4, 0.4, 0.0); // Background color
}

CScreen::~CScreen()
{
	ENTER_LOG;
	clearPointerContainer(mControlsToDelete);
}

CScreen* CScreen::instance(int handle)
{
	ENTER_LOG;
	return _screenMap[handle];
}

CScreen* CScreen::instance()
{
	ENTER_LOG;
	return _screenMap[glutGetWindow()];
}

void CScreen::invalidate() const
{
	ENTER_LOG;

	glutSetWindow(mWindow);
	glutPostRedisplay();
}

unsigned CScreen::instanceCount()
{
	ENTER_LOG;
	return static_cast<unsigned>(_screenMap.size());
}

CSize CScreen::size() const
{
	ENTER_LOG;
	return mRect.size();
}

void CScreen::size(const CSize& Size)
{
	ENTER_LOG;

	glutSetWindow(mWindow);
	glutReshapeWindow((int)Size.width(), (int)Size.height());
	glLoadIdentity();
	glViewport(0, 0, (int)Size.width(), (int)Size.height());
	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);
	CWindow::size(Size);
}

void CScreen::draw() const
{
	ENTER_LOG;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawChilds();
	glutSwapBuffers();
}

void CScreen::absolutePosition(const CPoint& point)
{
	ENTER_LOG;

	CControl::absolutePosition(point);

	glutSetWindow(mWindow);
	glutPositionWindow((int)point.x(), (int)point.y());
}

CPoint CScreen::absolutePosition() const
{
	ENTER_LOG;
	return CPoint(0, 0);
}

CPoint CScreen::relativePosition() const // TODO: ...
{
	ENTER_LOG;
	return CPoint(0, 0);
}

void CScreen::color(const CColor& Color)
{
	ENTER_LOG;
	glClearColor(Color.red(), Color.green(), Color.blue(), 0.0);
}

int CScreen::handle() const
{
	ENTER_LOG;
	return mWindow;
}

void CScreen::addControlToDelete(CControl* control)
{
	ENTER_LOG;
	mControlsToDelete.push_back(control);
}

bool CScreen::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	ENTER_LOG;

	CDragger* curDragger = CDragger::currentDragger();
	if(curDragger)
	{
		curDragger->drag(point);
		curDragger->handler()->onMouse(button, state, point);
	}

	return CWindow::onMouse(button, state, point);
}

void CScreen::addChild(CFace* child)
{
	ENTER_LOG;

	if(child)
	{
		mChilds.push_back(child);
	}
}

void CScreen::removeChild(CFace* child)
{
	ENTER_LOG;

	mChilds.remove(child);
	invalidate();
}