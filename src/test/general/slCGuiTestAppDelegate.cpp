#include <le/gui/slCScreen.h>
#include <le/gui/slCGuiScene.h>
#include <le/gui/auxiliary/slCGuiApplication.h>
//#include <le/gui/slCDialog.h>
#include <le/gui/slCButton.h>
#include "slCGuiTestAppDelegate.h"


namespace sokira
{
	namespace le
	{
		
		LE_IMPLEMENT_RUNTIME_CLASS(CGuiTestAppDelegate);
		
		void CGuiTestAppDelegate::applicationDidFinishLaunching(CApplication& application)
		{
			CScreen* screen = new CScreen(false);
			
			//	CDialog::Ptr dlg1 = new CDialog(CRectangle(10, 15, 30, 30));
			//	dlg1.retain();
			//	dlg1->setAutoResizing(eAutoResizingFixedMargins);
			
			CWindow* dlg2 = new CWindow(CRectangle(1, 1, 60, 60));
			
			CButton* button = new CButton(CRectangle(1, 1, 20, 20));
			//	dlg2->addChild(dlg1.get());
			//	CFace* face = new CFace();
			//	face->addChild(dlg2);
			dlg2->addChild(button);
			
			CGuiScene* scene = new CGuiScene();
			scene->addChild(dlg2);
			
			screen->addScene(scene, 0);
			
			dynamic_cast<CGuiApplication&>(application).addScreen(screen);
		}
		
		Bool CGuiTestAppDelegate::applicationShouldTerminateAfterLastWindowClosed(CApplication& application)
		{
			return true;
		}
		
	}
}
