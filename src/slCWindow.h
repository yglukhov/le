#pragma once

#include <config/slPrefix.h>
#include "slCControl.h"
#include <list>

LE_NAMESPACE_START

class CWindow : public CControl
{
	DECLARE_RUNTIME_CLASS(CWindow);

	// Creation
	public:
		CWindow() {}
		CWindow(const CRectangle& rect);
		~CWindow();

		virtual void draw() const;

		CSize size() const;
		virtual void size(const CSize& Size);

		virtual void relativePosition(const CPoint& Position);
		virtual void absolutePosition(const CPoint& Position);
		
		CPoint absolutePosition() const;

		virtual void addChild(CControl* child);
		virtual void removeChild(CControl* child);

//		virtual void moveLastToDraw();

	protected:
		virtual void drawSelf() const;
		void drawChilds() const;
		
		friend class CControl;
		typedef std::list<CControl*> CControlList;
		CControlList mChilds;
	private:
		friend class CScreen;
		bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
};

LE_NAMESPACE_END
