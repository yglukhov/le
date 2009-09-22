#include "slCGuiApplication.h"


#include "slCScreen.h"
#include "slCDialog.h"
//#include "slCFace.h"
#include "slTypes.h"
#include "slConstants.h"
#include "slCControlDelegate.h"
#include <le/core/auxiliary/slCNotificationCenter.h>
#include <le/core/debug/slDebug.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCGuiApplicationCocoaImpl.hp"
#define CGuiApplicationImpl CGuiApplicationCocoaImpl
#else
#error Complete this
#endif

namespace sokira
{
	namespace le
	{

CGuiApplication::CGuiApplication() :
	mImpl(new CGuiApplicationImpl())
{

}

CGuiApplication::~CGuiApplication()
{
	std::cout << "CGuiApplication::~CGuiApplication" << std::endl;
	for (std::vector<CScreen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
	{
		delete *it;
	}
	delete ((CGuiApplicationImpl*)mImpl);
}

//static void initOpenGL()
//{
//	LE_ENTER_LOG;
//	CDialog::Ptr dlg1 = new CDialog(CRectangle(10, 15, 30, 30));
//	dlg1.retain();
//	dlg1->autoResizing(eAlignSnapToAll);
//
////	IF_LOG(log << dlg1);
//
//	CDialog* dlg2 = new CDialog(CRectangle(1, 1, 60, 60));
//	
//	dlg2->addChild(dlg1.get());
//	CFace* face = new CFace();
//	face->addChild(dlg2);
//
//	CScreen::instance()->addChild(face);
//	
//	dlg2->title("dlg2");
//	dlg1->title("dlg1");
//}

//static void onMouse(int button, int state, int x, int y)
//{
////	CAutoreleasePool autoreleasePool;
//	CScreen::instance()->onMouse((EMouseButton)button, (EButtonState)state, CPoint((float)x, (float)y));
//}
//
//static void onMouseMove(int x, int y)
//{
////	CAutoreleasePool autoreleasePool;
//	CScreen::instance()->onMouse(eMouseButtonUnknown, eButtonStateUnknown, CPoint((float)x, (float)y));
//}

// onKey is not static, because it is friend for CControl.
//void onKey(unsigned char inkey, int px, int py)
//{
//	if(inkey == 27) // Escape key
//	{
////		CScreen::instance()->destroy();
//		exit(0);
//	}
//	CControl* fResponder = CControl::firstResponder();
//	if (fResponder)
//	{
////		CAutoreleasePool autoreleasePool;
//		fResponder->onKey(inkey, px, py);
//	}
//}
//
//static void onIdle()
//{
//	CNotificationCenter::instance()->fire();
//}
//
//static void onRedraw()
//{
////	CAutoreleasePool autoreleasePool;
//	CScreen::instance()->draw();
//}
//
//static void onResize(int x, int y)
//{
////	CAutoreleasePool autoreleasePool;
//	CScreen::instance()->setSize(CSize((float)x, (float)y));
//}

void CGuiApplication::addScreen(CScreen* screen)
{
	if (screen)
	{
		screen->screenWillBeAddedToApplication(this);
		screenWillBeAddedToApplication(screen);
		mScreens.push_back(screen);
		screenWasAddedToApplication(screen);
		screen->screenWasAddedToApplication(this);
	}
}

void CGuiApplication::screenWillBeAddedToApplication(CScreen* screen)
{
	static_cast<CGuiApplicationImpl*>(mImpl)->screenWillBeAddedToApplication(screen);
}

void CGuiApplication::screenWasAddedToApplication(CScreen* screen)
{
	static_cast<CGuiApplicationImpl*>(mImpl)->screenWasAddedToApplication(screen);
}

SInt32 CGuiApplication::runApplication()
{
	LE_ENTER_LOG;

	return static_cast<CGuiApplicationImpl*>(mImpl)->run(delegate(), this);
//	char ** arg = new char*[1];
//	int a = 1;
//	arg[0] = "";

//	glutInit(&a, arg);
//	delete [] arg;


//	new CScreen(false, "Light Engine");

//	initOpenGL();
//
//	glutReshapeFunc(onResize);
//	glutDisplayFunc(onRedraw);
//	glutKeyboardFunc(onKey);
//	glutMouseFunc(onMouse);
//	glutMotionFunc(onMouseMove);
//	glutIdleFunc(onIdle);

//	int result = 0;

//	try
//	{
//		glutMainLoop();
//	}
//	catch (std::exception &ex)
//	{
//		LE_IF_LOG(log << "Exception caught: " << ex.what() << std::endl);
//		result = 1;
//	}
//	catch (...)
//	{
//		LE_IF_LOG(log << "Unknown exception caught!" << std::endl);
//		result = 2;
//	}

//	return result;
}

	} // namespace le
} // namespace sokira
