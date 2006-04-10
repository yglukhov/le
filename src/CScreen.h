#pragma once

#include "Types.h"
#include "CWindow.h"

#define DEFAULT_SCREEN_RECT CRectangle(100, 768, 100, 100)

class CScreen : public CWindow
{
	DECLARE_RUNTIME_CLASS(CScreen);

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
		virtual void drawChilds();

		virtual void addChild(CFace* child);
		virtual void removeChild(CFace* child);

		CSize size() const;
		virtual void size(const CSize& Size);

		virtual void absolutePosition(const CPoint& point);
		virtual CPoint absolutePosition() const;

		virtual CPoint relativePosition() const;

		void color(const CColor& Color);
		
		int handle() const;
		void invalidate() const;

		bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
		bool onMouseFaces(EMouseButton button, EButtonState state, const CPoint& point);		
		
		void addControlToDelete(CControl* control);

	private:
		int mWindow;

		CFaceList mChilds;
		CControlList mControlsToDelete;
};