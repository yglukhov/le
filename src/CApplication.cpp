#include "CApplication.h"

#include "glut/glut.h"

#include "CScreen.h"
#include "CDialog.h"
#include "Types.h"
#include "Constants.h"
#include "CControlDelegate.h"
#include "CNotificationCenter.h"
#include "CFile.h"
#include "CAutoreleasePool.h"
#include "Debug.h"

static void initOpenGL()
{
	ENTER_LOG;
	CDialog::Ptr dlg1 = new CDialog(CRectangle(10, 15, 30, 30));
	dlg1.retain();
	dlg1->autoResizing(eAlignSnapToAll);
	
	IF_LOG(log << dlg1);
	
	CDialog* dlg2 = new CDialog(CRectangle(1, 1, 60, 60));
	
	dlg2->addChild(dlg1.get());
	CScreen::instance()->addChild(dlg2);
	
	dlg2->title("dlg2");
	dlg1->title("dlg1");
}

static void onMouse(int button, int state, int x, int y)
{
	CAutoreleasePool autoreleasePool;
	CScreen::instance()->onMouse((EMouseButton)button, (EButtonState)state, CPoint((float)x, (float)y));
}

static void onMouseMove(int x, int y)
{
	CAutoreleasePool autoreleasePool;
	CScreen::instance()->onMouse(eMouseButtonUnknown, eButtonStateUnknown, CPoint((float)x, (float)y));
}

// onKey is not static, becouse it is friend for CControl.
void onKey(unsigned char inkey, int px, int py)
{
	if(inkey == 27) // Escape key
		exit(1);
	CControl* fResponder = CControl::firstResponder();
	if (fResponder)
	{
		CAutoreleasePool autoreleasePool;
		fResponder->onKey(inkey, px, py);
	}	
}

static void onIdle()
{
	CNotificationCenter::instance()->fire();
}

static void onRedraw()
{
	CAutoreleasePool autoreleasePool;
	CScreen::instance()->draw();
}

static void onResize(int x, int y)
{
	CAutoreleasePool autoreleasePool;
	CScreen::instance()->size(CSize((float)x, (float)y));
}

int CApplication::run(int argc, const char * const argv[])
{
	ENTER_LOG;
	
	glutInit(&argc, (char **)argv);
	new CScreen(false, "Light Engine");

	initOpenGL();

	glutReshapeFunc(onResize);
	glutDisplayFunc(onRedraw);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMouseMove);
	glutIdleFunc(onIdle);
	glutMainLoop();
	
	return 0;
}