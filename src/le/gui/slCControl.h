#pragma once

#include <common/config/slPrefix.h>
#include "slConstants.h"
#include "slTypes.h"
#include <common/slCObject.h>
#include "slCFace.h"

LE_NAMESPACE_START

class CWindow;
class CControlDelegate;
class CButton;

enum EAutoResizing
{
	eAlignTop = LE_SET_BIT(0),
	eAlignBottom = LE_SET_BIT(1),
	eAlignLeft = LE_SET_BIT(2),
	eAlignRight = LE_SET_BIT(3),
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

		CFace* face();
		void face(CFace* face);

	private:
		friend class CScreen;
		friend class CWindow;
		friend class CFace;
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
		CFace* mFace;
};


LE_NAMESPACE_END
