#pragma once

#include <le/core/slCString.h>
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

		CSize size() const;
		virtual void setSize(const CSize& Size);

		virtual void setAbsolutePosition(const CPoint& point);
		virtual CPoint absolutePosition() const;

		virtual CPoint relativePosition() const;

		void color(const CColor& Color);

		virtual void setNeedsRedraw();

		void addControlToDelete(CControl* control);

		void addScene(CScene* scene, UInt32 order);

		// Do not call these functions directly.
		void _screenWasResized();
		void _screenWillBeClosed();
		void _prepareOpenGL();

		void onMouse(EMouseButton button, EButtonState state, const CPoint& point);
//		void onMouseDown(EMouseButton button, const CPoint& point);
//		void onMouseUp(EMouseButton button, const CPoint& point);
//		void onMouseHover(const CPoint& point);
		void onMouseIn(const CPoint& point);
		void onMouseOut(const CPoint& point);

		void onKeyDown(const CString& characters, ECharacterModifiers modifiers);
		void onKeyUp(const CString& characters, ECharacterModifiers modifiers);

	protected:
		virtual void onResize();

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
		CSize mSize;
		Bool mSizeChanged;
		EMouseButton mPressedButtons;
		CRenderingContext* mRenderingContext;
};

	} // namespace le
} // namespace sokira
