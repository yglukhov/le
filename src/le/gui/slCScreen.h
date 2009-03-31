#pragma once

#include "slTypes.h"
#include "slCWindow.h"

namespace sokira
{
	namespace le
	{

#define DEFAULT_SCREEN_RECT CRectangle(50, 50, 100, 100)

class CGuiApplication;
class CScene;

class CScreen : public CObject
{
	LE_DECLARE_RUNTIME_CLASS(CScreen);

	public:
		CScreen(bool fullscreen = true, const char* title = NULL,
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
		void _prepareOpenGL();

		void onMouse(EMouseButton button, EButtonState state, const CPoint& point);
//		void onMouseDown(EMouseButton button, const CPoint& point);
//		void onMouseUp(EMouseButton button, const CPoint& point);
//		void onMouseHover(const CPoint& point);
		void onMouseIn(const CPoint& point);
		void onMouseOut(const CPoint& point);

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
};

	} // namespace le
} // namespace sokira
