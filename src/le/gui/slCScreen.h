#pragma once

#include "slTypes.h"
#include "slCWindow.h"

namespace sokira
{
	namespace le
	{

#define DEFAULT_SCREEN_RECT CRectangle(50, 50, 100, 100)

class CGuiApplication;

class CScreen : public CWindow
{
	LE_DECLARE_RUNTIME_CLASS(CScreen);

	public:
		typedef std::list<CControl*> CControlList;
		typedef std::list<CFace*> CFaceList;

		CScreen(bool fullscreen = true, const char* title = NULL,
				  const CRectangle& rect = DEFAULT_SCREEN_RECT);
		~CScreen();

		static CScreen* instance(int handle);
		static CScreen* instance();
		static unsigned instanceCount();

		virtual void draw();
//		virtual void drawChilds();

//		virtual void addChild(CFace* child);
//		virtual void removeChild(CFace* child);

		CSize size() const;
		virtual void setSize(const CSize& Size);

		virtual void absolutePosition(const CPoint& point);
		virtual CPoint absolutePosition() const;

		virtual CPoint relativePosition() const;

		void color(const CColor& Color);

		int handle() const;
		void invalidate() const;

		bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
//		bool onMouseFaces(EMouseButton button, EButtonState state, const CPoint& point);

		void addControlToDelete(CControl* control);

		void destroy();

		// Do not call these functions directly.
		void _screenWasResized();
		void _prepareOpenGL();

		
		void onMouseDown(EMouseButton button, const CPoint& point);
		void onMouseUp(EMouseButton button, const CPoint& point);
		void onMouseHover(const CPoint& point);
		void onMouseOut(const CPoint& point);
		void onMouseIn(const CPoint& point);

	protected:
		virtual void onResize();

	private:
		friend class CGuiApplication;

		void screenWillBeAddedToApplication(CGuiApplication* app);
		void screenWasAddedToApplication(CGuiApplication* app);

		void screenWillBeRemovedFromApplication(CGuiApplication* app);
		void screenWasRemovedFromApplication(CGuiApplication* app);

		int mWindow;
//		CFaceList mChilds;
		CControlList mControlsToDelete;
		void* mImpl;
		Bool mSizeChanged;
};


	} // namespace le
} // namespace sokira
