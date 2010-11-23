#if !defined SL_LE_gui_slCView_h
#define SL_LE_gui_slCView_h

#include <le/core/config/slPrefix.h>
#include "slCControl.h"
#include <list>

namespace sokira
{
	namespace le
	{

class CView : public CControl
{
	LE_DECLARE_RUNTIME_CLASS(CView);

	// Creation
	public:
		CView() {}
		CView(const CRectangle& rect);
		~CView();

		virtual void setSize(const CSize2D& Size);

		virtual void setAbsolutePosition(const CPoint2D& Position);

		virtual void addChild(CControl* child);
		virtual void removeChild(CControl* child);

		virtual void draw(const CTheme*, CRenderingContext* context) const;

//		virtual void moveLastToDraw();

		// Mouse events
//		virtual Bool onMouseDown(EKeyCode button, const CPoint& point);
//		virtual Bool onMouseUp(EKeyCode button, const CPoint& point);
//		virtual Bool onMouseHover(const CPoint& point);
//		virtual Bool onMouseOut(const CPoint& point);
//		virtual Bool onMouseIn(const CPoint& point);

		// Low level mouse events. Do not override.
//		virtual Bool mouseButtonPressed(EKeyCode button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseButtonReleased(EKeyCode button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseHovered(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseExited(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseEntered(const CPoint& point, const CTheme* theme);
		virtual Bool onMouse(EKeyCode button, EButtonState state, const CPoint2D& point);
		virtual Bool onKeyDown(EKeyCode keyCode);
		virtual Bool onKeyUp(EKeyCode keyCode);


		typedef std::list<CControl*> CControlList;

		const CControlList& children() const
		{
			return mChildren;
		}

	protected:

		friend class CControl;
		CControlList mChildren;
		virtual Bool childBecomesFirstResponder(CControl* child, CView* parent);
		virtual Bool isChildFirstResponder(const CControl* child) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCView_h
