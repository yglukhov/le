#include <glut/slGlut.h>

#include <map>

#include "slCScreen.h"
#include "slCDragger.h"
#include <le/core/debug/slDebug.h>
#include <le/core/auxiliary/slStdExtensions.h>

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CScreen);


typedef std::map<int, CScreen*> CScreenMap;
static CScreenMap	_screenMap;

CScreen::CScreen(bool fullscreen, const char* title, const CRectangle& rect) :
	CWindow(rect)
{
	LE_ENTER_LOG;

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
	glEnable(GL_DEPTH_TEST);
}

CScreen::~CScreen()
{
	LE_ENTER_LOG;
	clearPointerContainer(mControlsToDelete);
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

	glutSetWindow(mWindow);
	glutPostRedisplay();
}

unsigned CScreen::instanceCount()
{
	LE_ENTER_LOG;
	return static_cast<unsigned>(_screenMap.size());
}

CSize CScreen::size() const
{
	LE_ENTER_LOG;
	return mRect.size();
}

void CScreen::size(const CSize& Size)
{
	LE_ENTER_LOG;

	glutSetWindow(mWindow);
	glutReshapeWindow((int)Size.width(), (int)Size.height());
	glLoadIdentity();
	glViewport(0, 0, (int)Size.width(), (int)Size.height());
	glOrtho(0, (int)Size.width(), (int)Size.height(), 0, 0, 1);
	CWindow::size(Size);
}

void CScreen::draw()
{
	LE_ENTER_LOG;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawChilds();
	glutSwapBuffers();
}

void CScreen::drawChilds()
{
	LE_ENTER_LOG;

	CFaceList::const_iterator end = mChilds.end();
	for(CFaceList::const_iterator it = mChilds.begin(); it != end; ++it)
	{
		(*it)->draw();
	}
}

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

	CDragger* curDragger = CDragger::currentDragger();
	if(curDragger)
	{
		curDragger->drag(point);
		curDragger->handler()->onMouse(button, state, point);
	}

	return onMouseFaces(button, state, point);
}

bool CScreen::onMouseFaces(EMouseButton button, EButtonState state, const CPoint& point)
{
	LE_ENTER_LOG;

	CFaceList::iterator end = mChilds.end();
	for (CFaceList::iterator it = mChilds.begin(); it != end; ++it)
	{
		if ((*it)->hitTest(point) && (*it)->onMouse(button, state, point))
			return true;
	}

	return CControl::onMouse(button, state, point);
}
void CScreen::addChild(CFace* child)
{
	LE_ENTER_LOG;

	if(child)
	{
		mChilds.push_back(child);
	}
}

void CScreen::removeChild(CFace* child)
{
	LE_ENTER_LOG;

	mChilds.remove(child);
	invalidate();
}


LE_NAMESPACE_END