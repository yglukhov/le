#if !defined SL_LE_gui_slCControl_h
#define SL_LE_gui_slCControl_h

#include "slConstants.h"
#include <le/core/slCObject.h>
#include <le/core/geometry/slTCRectangle.h>

namespace sokira
{
	namespace le
	{

class CWindow;
class CControlDelegate;
class CTheme;
class CRenderingContext;

enum EAutoResizing
{
	eAutoResizingFixedTop = LE_SET_BIT(0),
	eAutoResizingFixedBottom = LE_SET_BIT(1),
	eAutoResizingFixedLeft = LE_SET_BIT(2),
	eAutoResizingFixedRight = LE_SET_BIT(3),
	eAutoResizingFixedWidth = LE_SET_BIT(4),
	eAutoResizingFixedHeight = LE_SET_BIT(5),
	eAutoResizingFixedTopLeft = (eAutoResizingFixedTop | eAutoResizingFixedLeft),
	eAutoResizingFixedMargins = (eAutoResizingFixedTopLeft | eAutoResizingFixedRight | eAutoResizingFixedBottom),
	eAutoResizingFixedSize = (eAutoResizingFixedWidth | eAutoResizingFixedHeight)
};

// CControl objects can not contain any childs.
class CControl : public CObject
{
	LE_DECLARE_RUNTIME_CLASS(CControl);

	// Creation
	public:
		CControl();
		CControl(const CRectangle& rect);
		virtual ~CControl();

//		void destroy();

		CRectangle absoluteRect() const;
		CRectangle relativeRect() const;

		CSize2D size() const;
		virtual void setSize(const CSize2D& Size);

		CPoint2D relativePosition() const;
		void setRelativePosition(const CPoint2D& point);

		CPoint2D absolutePosition() const;
		virtual void setAbsolutePosition(const CPoint2D& point);

		void delegate(CControlDelegate* Delegate);
		CControlDelegate* delegate();

		void setAutoResizing(unsigned mask);
		unsigned autoResizing() const;

		float borderWidth() const;
		void borderWidth(float width);

		CWindow* parent() const;

		void setVisible(Bool visible = true);
		Bool isVisible() const;

		virtual void setNeedsRedraw();

		virtual void draw(const CTheme* theme, CRenderingContext* context) const;

		// Mouse events
		virtual Bool onMouseDown(EMouseButton button, const CPoint2D& point);
		virtual Bool onMouseUp(EMouseButton button, const CPoint2D& point);
//		virtual Bool onMouseClick(EMouseButton button, const CPoint& point);
//		virtual Bool onMouseMultipleClick(EMouseButton button, const CPoint& point);
		virtual Bool onMouseHover(const CPoint2D& point);
		virtual Bool onMouseOut(const CPoint2D& point);
		virtual Bool onMouseIn(const CPoint2D& point);

		// Low level mouse events. Do not override.
//		virtual Bool mouseButtonPressed(EMouseButton button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseButtonReleased(EMouseButton button, const CPoint& point, const CTheme* theme);
//		virtual Bool mouseHovered(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseExited(const CPoint& point, const CTheme* theme);
//		virtual Bool mouseEntered(const CPoint& point, const CTheme* theme);
		virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint2D& point);

		// Responder chain functions
		Bool becomeFirstResponder();
		Bool resignFirstResponder(); // Make parent the first responder.
		Bool isFirstResponder() const;

		virtual Bool controlCanBecomeFirstResponder();
		virtual void controlDidBecomeFirstResponder();
		virtual Bool controlCanResignFirstResponder();
		virtual void controlDidResignFirstResponder();


		// Remove control from parent and delete it.
		void close();

	protected:

		void setParent(CWindow* parent);

		virtual Bool hitTest(const CPoint2D& point) const;
		Bool performMouse(EMouseButton button, EButtonState state, const CPoint2D& point);


	private:
		friend class CWindow;
		friend void onKey(unsigned char, int, int);
		bool onKey(unsigned char inkey, int px, int py);

		CWindow* mParent;
		CControlDelegate* mDelegate;
		unsigned mAutoResizingMask;
		Float32 mBorderWidth;
		Bool mVisible;
		CRectangle mRect;	// Absolute ccords, if mParent != NULL, else relative.
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCControl_h
