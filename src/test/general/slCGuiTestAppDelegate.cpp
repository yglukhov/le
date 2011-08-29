#include <le/core/thread/slCThread.h>
#include <le/core/template/function/slTCBind.h>
#include <le/gui/slCWindow.h>
#include <le/gui/auxiliary/slCGuiApplication.h>
#include <le/gui/slCButton.h>
#include <le/gui/slCRenderingContext.h>
#include "slCGuiTestAppDelegate.h"


namespace sokira
{
	namespace le
	{

		LE_IMPLEMENT_RUNTIME_CLASS(CGuiTestAppDelegate);

class CTestScreen : public CWindow
{
	public:
		virtual void draw()
		{
			CWindow::draw();

			CPolygon poly;
			poly.addPoint(CPoint2D(0, 0));
			poly.addPoint(CPoint2D(100, 0));
			poly.addPoint(CPoint2D(0, 100));
//			LE_ASSERT(poly.containsPoint(CPoint2D(0.3, 0.3)));
//			LE_ASSERT(!poly.containsPoint(CPoint2D(1, 1)));
//			LE_ASSERT(poly.isConvex());
			poly.addPoint(CPoint2D(20, 20));

//			if (poly.isCounterClockWise()) poly.reverse();
//
//			poly.reverse();

//			renderingContext()->drawConvexPolygon(poly);
//			LE_ASSERT(!poly.isConvex());

			std::vector<CPolygon> decomposedPolys = poly.decomposeToTriangles();
//			LE_ASSERT(decomposedPolys.size() == 2);
			for (std::vector<CPolygon>::iterator it = decomposedPolys.begin(); it != decomposedPolys.end(); ++it)
			{
				if (it->isCounterClockWise()) it->reverse();
				renderingContext()->drawConvexPolygon(poly);
				std::cout << "Decomposed poly: " << *it << std::endl;
			}
		}
};


		void CGuiTestAppDelegate::onTimer()
		{
			std::cout << "onTimer: Stopping runLoop" << std::endl;
			CThread::thread().runLoop().stop();
		}

		void CGuiTestAppDelegate::applicationDidFinishLaunching(CApplication& application)
		{
			CWindow* screen = new CTestScreen();

			//	CDialog::Ptr dlg1 = new CDialog(CRectangle(10, 15, 30, 30));
			//	dlg1.retain();
			//	dlg1->setAutoResizing(eAutoResizingFixedMargins);

			CView* dlg2 = new CView(CRectangle(1, 1, 60, 60));

			CButton* button = new CButton(CRectangle(1, 1, 20, 20));
			button->setText("x");
			//	dlg2->addChild(dlg1.get());
			//	CFace* face = new CFace();
			//	face->addChild(dlg2);
			dlg2->addChild(button);

//			CGuiScene* scene = new CGuiScene();
//			scene->addChild(dlg2);

//			screen->addScene(scene, 0);

//			screen->contentView()->addChild(dlg2);
//			screen->addChild(dlg2);
			dynamic_cast<CGuiApplication&>(application).addScreen(screen);

//			TCFunction<> timerFunc = bind(&CGuiTestAppDelegate::onTimer, this);
//			CThread::thread().runLoop().scheduledTimerWithInterval(2000, timerFunc);
		}

		Bool CGuiTestAppDelegate::applicationShouldTerminateAfterLastWindowClosed(CApplication& application)
		{
			return true;
		}
	}
}
