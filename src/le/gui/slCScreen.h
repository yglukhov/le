#pragma once

#include <le/core/slCString.h>
#include <le/core/slCColor.h>
#include "slTypes.h"
#include "slCWindow.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

#define DEFAULT_SCREEN_RECT CRectangle(50, 50, 200, 200)

class CGuiApplication;
class CRenderingContext;
class CScene;

class CScreen : public CWindow
{
	LE_DECLARE_RUNTIME_CLASS(CScreen);

	public:
		CScreen(bool fullscreen = true, const CString& title = CString(),
				  const CRectangle& rect = DEFAULT_SCREEN_RECT);
		~CScreen();

		virtual void draw();

		CSize2D size() const;
		virtual void setSize(const CSize2D& Size);

		virtual void setAbsolutePosition(const CPoint2D& point);
		virtual CPoint2D absolutePosition() const;

		virtual CPoint2D relativePosition() const;

		CString title() const;

		void color(const CColor& Color);

		virtual void setNeedsRedraw();
		virtual Bool hitTest(const CPoint2D& point) const { return true; }

//		void addControlToDelete(CControl* control);

//		void addScene(CScene* scene, UInt32 order);

		// Do not call these functions directly.
//		void _screenWasResized();
		void _screenWillBeClosed();
		void _prepareOpenGL();

		CWindow* contentView();

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

		CRenderingContext* renderingContext();

	private:
		friend class CGuiApplication;

		void screenWillBeAddedToApplication(CGuiApplication* app);
		void screenWasAddedToApplication(CGuiApplication* app);

		void screenWillBeRemovedFromApplication(CGuiApplication* app);
		void screenWasRemovedFromApplication(CGuiApplication* app);

//		CWindow* mContentView;
		CTheme mTheme;

		void* mImpl;
//		CSize2D mSize;
		CRenderingContext* mRenderingContext;
};

	} // namespace le
} // namespace sokira
