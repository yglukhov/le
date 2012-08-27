#if !defined SL_LE_gui_slCView_h
#define SL_LE_gui_slCView_h

#include <le/core/config/slPrefix.h>
#include "slCControl.h"
#include "slCEventTracker.h"
#include <list>

namespace sokira
{
	namespace le
	{

class CWindow;

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

		virtual void addChild(CView::Ptr child);
		virtual void removeChild(CView::Ptr child);

		virtual void draw(const CTheme*, CRenderingContext* context) const;

		void enterFullScreenMode();
		void exitFullScreenMode();
		Bool isInFullScreenMode() const;

		virtual CWindow* window() const;

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


		typedef std::list<CView::Ptr> CControlList;
		typedef std::list<CEventTracker::Ptr> CEventTrackerList;

		const CControlList& children() const
		{
			return mChildren;
		}

		const CEventTrackerList& eventTrackers() const
		{
			return mEventTrackers;
		}


		// Responder chain functions
		Bool becomeFirstResponder();
		Bool resignFirstResponder(); // Make parent the first responder.
		Bool isFirstResponder() const;


	protected:

		void recursiveDraw(const CTheme* theme, CRenderingContext* context) const;

		virtual Bool hitTest(const CPoint2D& point) const;


		friend class CControl;
		CControlList mChildren;
		CEventTrackerList mEventTrackers;
		virtual Bool childBecomesFirstResponder(CView* child, CView* parent);
		virtual Bool isChildFirstResponder(const CControl* child) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCView_h
