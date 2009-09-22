#if !defined SL_LE_gui_slCWindow_h
#define SL_LE_gui_slCWindow_h

#include <le/core/config/slPrefix.h>
#include "slCControl.h"
#include <list>

namespace sokira
{
	namespace le
	{

class CWindow : public CControl
{
	LE_DECLARE_RUNTIME_CLASS(CWindow);

	// Creation
	public:
		CWindow() {}
		CWindow(const CRectangle& rect);
		~CWindow();

		CSize size() const;
		virtual void setSize(const CSize& Size);

		virtual void setRelativePosition(const CPoint& Position);
		virtual void setAbsolutePosition(const CPoint& Position);

		virtual void addChild(CControl* child);
		virtual void removeChild(CControl* child);

		virtual void draw(const CTheme*, CRenderingContext* constext) const;

//		virtual void moveLastToDraw();

		// Mouse events
//		virtual Bool onMouseDown(EMouseButton button, const CPoint& point);
//		virtual Bool onMouseUp(EMouseButton button, const CPoint& point);
//		virtual Bool onMouseHover(const CPoint& point);
//		virtual Bool onMouseOut(const CPoint& point);
//		virtual Bool onMouseIn(const CPoint& point);

		// Low level mouse events. Do not override.
//		virtual Bool mouseButtonPressed(EMouseButton button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseButtonReleased(EMouseButton button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseHovered(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseExited(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseEntered(const CPoint& point, const CTheme* theme);
		virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);


		typedef std::list<CControl*> CControlList;

		const CControlList& children() const
		{
			return mChildren;
		}

	protected:

		friend class CControl;
		CControlList mChildren;
		virtual Bool childBecomesFirstResponder(CControl* child, CWindow* parent);
		virtual Bool isChildFirstResponder(const CControl* child) const;

	private:
		void moveChildren(const CSize& delta);

//		friend class CScreen;
//		bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCWindow_h
