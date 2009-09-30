#include <glut/slGlut.h>
//#include <OpenGL/OpenGL.h>
//#include <OpenGLES/ES1/gl.h>

#include <map>
#include <iostream>

#include "slCScreen.h"
#include "slCDragger.h"
#include <le/core/debug/slDebug.h>
//#include <le/core/auxiliary/slStdExtensions.h>

#include <le/core/config/slCompiler.h>

#include <le/gui/slCGuiScene.h>
#include <le/gui/slCOpenGLRenderingContext.h>

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

CScreen::CScreen(bool fullscreen, const CString& title, const CRectangle& rect) :
//	CWindow(rect),
	mImpl(new CScreenImpl(fullscreen, title, rect)),
	mSize(rect.size()),
	mSizeChanged(true),
	mRenderingContext(NULL)
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
//	std::cout << "CScreen::~CScreen" << std::endl;
//	clearPointerContainer(mControlsToDelete);
	for (CSceneList::iterator it = mScenes.begin(); it != mScenes.end(); ++it)
		delete *it;
	delete mRenderingContext;
	delete static_cast<CScreenImpl*>(mImpl);
}

void CScreen::setNeedsRedraw()
{
	LE_ENTER_LOG;

	if (mImpl) static_cast<CScreenImpl*>(mImpl)->setNeedsRedraw();

//	glutSetWindow(mWindow);
//	glutPostRedisplay();
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

//	CWindow::setSize(size);
}

void CScreen::draw()
{
	LE_ENTER_LOG;

	std::cout << "CScreen::draw: " << title() << std::endl;

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

	LE_ASSERT(mRenderingContext);

//	std::cout << "CScreen::draw()" << std::endl;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	CRenderingContext* context = NULL; //static_cast<CScreenImpl*>(mImpl)->renderingContext();
//	context->clear();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		(*it)->draw(mRenderingContext);
	}


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

void CScreen::setAbsolutePosition(const CPoint& point)
{
	LE_ENTER_LOG;

//	CControl::setAbsolutePosition(point);

//	glutSetWindow(mWindow);
//	glutPositionWindow((int)point.x(), (int)point.y());
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

CString CScreen::title() const
{
	return static_cast<CScreenImpl*>(mImpl)->title();
}

void CScreen::color(const CColor& Color)
{
	LE_ENTER_LOG;
	glClearColor(Color.red(), Color.green(), Color.blue(), 0.0);
}

void CScreen::addControlToDelete(CControl* control)
{
	LE_ENTER_LOG;
//	mControlsToDelete.push_back(control);
}

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

void CScreen::addScene(CScene* scene, UInt32 order)
{
	if (scene)
	{
		mScenes.push_back(scene);
		scene->setScreen(this);
	}
}

void CScreen::_prepareOpenGL()
{
	mRenderingContext = new COpenGLRenderingContext();
//	std::cout << "CScreen::_prepareOpenGL()" << std::endl;
}

void CScreen::_screenWasResized()
{
//	mSize = static_cast<CScreenImpl*>(mImpl)->size();
	mSizeChanged = true;
}

void CScreen::_screenWillBeClosed()
{
	delete static_cast<CScreenImpl*>(mImpl);
	mImpl = NULL;
}

// This event includes mouse up, mouse down and mouse hover.
void CScreen::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	std::cout << "CScreen::onMouse: " << title() << std::endl;
	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		(*it)->onMouse(button, state, point);
	}
}

void CScreen::onMouseIn(const CPoint& point)
{
	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		(*it)->mouseEntered(point);
	}
}

void CScreen::onMouseOut(const CPoint& point)
{
	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		(*it)->mouseExited(point);
	}
}

void CScreen::onKeyDown(const CString& characters, ECharacterModifiers modifiers)
{
	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		if ((*it)->onKeyDown(characters, modifiers)) break;
	}
}

void CScreen::onKeyUp(const CString& characters, ECharacterModifiers modifiers)
{
	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		if ((*it)->onKeyUp(characters, modifiers)) break;
	}
}

// This method is always called within valid OpenGL context
void CScreen::onResize()
{
	CSize2D prevSize = mSize;
	mSize = static_cast<CScreenImpl*>(mImpl)->size();

	std::cout << "CScreen::onResize: " << title() << std::endl;
//	std::cout << "{" << std::endl;

	glViewport(0, 0, (int)mSize.width(), (int)mSize.height());
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity (); 
	glOrtho(0, (int)mSize.width(), (int)mSize.height(), 0, -1, 1);

	CSceneList::const_iterator end = mScenes.end();
	for(CSceneList::const_iterator it = mScenes.begin(); it != end; ++it)
	{
		CGuiScene* scene = dynamic_cast<CGuiScene*> (*it);
		if (scene) scene->parentResized(prevSize, mSize);
	}

//	std::cout << "}" << std::endl;
	setNeedsRedraw();
}

	} // namespace le
} // namespace sokira
