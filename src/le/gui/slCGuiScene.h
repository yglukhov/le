#if !defined SL_LE_gui_slCGuiScene_h
#define SL_LE_gui_slCGuiScene_h

#include <list>
#include <le/gui/slCScene.h>
#include <le/gui/slCTheme.h>
#include <le/gui/slCWindow.h>

namespace sokira
{
	namespace le
	{

class CControl;
class CTheme;

class CGuiScene : public CScene, public CWindow
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CGuiScene)
		// LE_RTTI_PUBLIC_PARENT(CScene) // CScene doesn't have RTTI yet.
		LE_RTTI_PUBLIC_PARENT(CWindow)
	LE_RTTI_END

	public:
		CGuiScene();

		// Mouse events
		virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
//		virtual Bool mouseButtonPressed(EMouseButton button, const CPoint& point);
//		virtual Bool mouseButtonReleased(EMouseButton button, const CPoint& point);
//		virtual Bool mouseHovered(const CPoint& point);
		virtual Bool mouseEntered(const CPoint& point);
		virtual Bool mouseExited(const CPoint& point);

		virtual void draw(CRenderingContext* context);

		virtual void setNeedsRedraw();

		virtual Bool hitTest(const CPoint& point) const;

	protected:
		virtual Bool childBecomesFirstResponder(CControl* child, CWindow* parent);
		virtual Bool isChildFirstResponder(const CControl* child) const;
		virtual void setScreen(CScreen* screen);

	private:
		CControl* mFirstResponder;
		CTheme mTheme;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCGuiScene_h
