#pragma once

#include "Constants.h"
#include "Types.h"
#include "CObject.h"

class CWindow;
class CControlDelegate;
class CButton;

enum EAutoResizing
{
	eAlignTop = SET_BIT(0),
	eAlignBottom = SET_BIT(1),
	eAlignLeft = SET_BIT(2),
	eAlignRight = SET_BIT(3),
	eAlignTopLeft = (eAlignTop | eAlignLeft),
	eAlignSnapToAll = (eAlignTop | eAlignLeft | eAlignBottom | eAlignRight)
};

// CControl objects can not contain any childs.
class CControl : public CObject
{
	DECLARE_RUNTIME_CLASS(CControl);

	// Creation
	public:
		CControl();
		CControl(const CRectangle& rect);
		virtual ~CControl();

		void destroy();

		static CControl* firstResponder();
		virtual void draw() const;

		CRectangle absoluteRect() const;
		CRectangle relativeRect() const;

		CSize size() const;
		virtual void size(const CSize& Size);

		virtual CPoint relativePosition() const;
		virtual void relativePosition(const CPoint& point);

		virtual CPoint absolutePosition() const;
		virtual void absolutePosition(const CPoint& point);

		void delegate(CControlDelegate* Delegate);
		CControlDelegate* delegate();

		void autoResizing(unsigned mask);
		unsigned autoResizing() const;

		float borderWidth() const;
		void borderWidth(float width);

		bool setFocus();

		CWindow* parent() const;

	protected:

		virtual void moveLastToDraw();
		void parent(CWindow* newParent);

	private:
		friend class CScreen;
		friend class CWindow;
		void parentResized(const CSize& fromSize, const CSize& toSize);
		virtual void parentMoved(const CPoint& fromPos, const CPoint& toPos);
		virtual bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
		friend void onKey(unsigned char, int, int);
		bool onKey(unsigned char inkey, int px, int py);

		CWindow* mParent;
		CControlDelegate* mDelegate;
		unsigned mAutoResizingMask;
		float mBorderWidth;
		CRectangle mRect;	// Absolute ccords, if mParent != NULL, else relative.
};