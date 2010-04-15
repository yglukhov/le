#pragma once

#include <le/core/slCString.h>
#include <le/core/slCColor.h>
#include "slTypes.h"
#include "slCWindow.h"

namespace sokira
{
	namespace le
	{

#define DEFAULT_SCREEN_RECT CRectangle(50, 50, 100, 100)

class CGuiApplication;
class CRenderingContext;
class CScene;

class CScreen : public CObject
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

		void addControlToDelete(CControl* control);

		void addScene(CScene* scene, UInt32 order);

		// Do not call these functions directly.
//		void _screenWasResized();
		void _screenWillBeClosed();
		void _prepareOpenGL();

		void onMouse(EMouseButton button, EButtonState state, const CPoint2D& point);
//		void onMouseDown(EMouseButton button, const CPoint& point);
//		void onMouseUp(EMouseButton button, const CPoint& point);
//		void onMouseHover(const CPoint& point);
		void onMouseIn(const CPoint2D& point);
		void onMouseOut(const CPoint2D& point);

		void onKeyDown(const CString& characters, ECharacterModifiers modifiers);
		void onKeyUp(const CString& characters, ECharacterModifiers modifiers);

		void onResize();
	protected:

	private:
		friend class CGuiApplication;

		void screenWillBeAddedToApplication(CGuiApplication* app);
		void screenWasAddedToApplication(CGuiApplication* app);

		void screenWillBeRemovedFromApplication(CGuiApplication* app);
		void screenWasRemovedFromApplication(CGuiApplication* app);

		typedef std::list<CScene*> CSceneList;
		CSceneList mScenes;

//		CControlList mControlsToDelete;
		void* mImpl;
		CSize2D mSize;
		EMouseButton mPressedButtons;
		CRenderingContext* mRenderingContext;
};

	} // namespace le
} // namespace sokira
