#pragma once

#include <le/core/slCString.h>
#include <le/core/slCColor.h>
#include <le/gui/auxiliary/slCGuiApplication.h>
#include <le/gui/slCRenderingContext.h>
#include "slTypes.h"
#include "slCView.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

#define DEFAULT_SCREEN_RECT CRectangle(50, 50, 200, 200)

class CEvent;

class CWindow : public CView
{
	LE_DECLARE_RUNTIME_CLASS(CWindow);

	public:
		CWindow(bool fullscreen = true, const CString& title = CString(),
				  const CRectangle& rect = DEFAULT_SCREEN_RECT);
		~CWindow();

		virtual void draw();
		virtual void draw(const CTheme*, CRenderingContext* context) const;

		virtual void setSize(const CSize2D& Size);

		virtual void setAbsolutePosition(const CPoint2D& point);
		virtual CPoint2D absolutePosition() const;

		virtual CPoint2D relativePosition() const;

		CString title() const;

		virtual void setNeedsRedraw();
		virtual Bool hitTest(const CPoint2D& point) const { return true; }

		virtual CWindow* window() const;

//		void addControlToDelete(CControl* control);

		// Do not call these functions directly.
//		void _screenWasResized();
		void _screenWillBeClosed();
		virtual void prepareRenderingContext();

		Bool handleEvent(CEvent* event);
//		virtual Bool onMouse(EKeyCode button, EButtonState state, const CPoint2D& point);
//		void onMouseDown(EKeyCode button, const CPoint& point);
//		void onMouseUp(EKeyCode button, const CPoint& point);
//		void onMouseHover(const CPoint& point);
//		virtual Bool onMouseIn(const CPoint2D& point);
//		virtual Bool onMouseOut(const CPoint2D& point);

//		void onKeyDown(const CString& characters, ECharacterModifiers modifiers);
//		void onKeyUp(const CString& characters, ECharacterModifiers modifiers);

		void onResize();
	protected:

		CRenderingContext::Ptr renderingContext();
		virtual void* createImpl();

	private:
		friend class CGuiCocoaApplication;

		void screenWillBeAddedToApplication(CGuiApplication* app);
		void screenWasAddedToApplication(CGuiApplication* app);

		void screenWillBeRemovedFromApplication(CGuiApplication* app);
		void screenWasRemovedFromApplication(CGuiApplication* app);

		CTheme mTheme;
		CString mTitle;
		Bool mFullScreen;
		CPoint2D mPositionOnScreen;

		void* mImpl;
		CRenderingContext::Ptr mRenderingContext;
};

	} // namespace le
} // namespace sokira
