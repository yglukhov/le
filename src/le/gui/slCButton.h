#pragma once

#include <le/core/slCString.h>
#include <le/core/template/function/slTCFunction.h>
#include "slCControl.h"
#include "slCControlDelegate.h"

namespace sokira
{
	namespace le
	{

class CButton: public CControl//, public CControlDelegate
{
	LE_DECLARE_RUNTIME_CLASS(CButton);

	public:
		CButton();
		CButton(const CRectangle& rect);

		EButtonState state() const;

		void setText(const CString& text);
		CString text() const;

		typedef TCFunction<> TOnClick;
		void setOnClick(TOnClick& onClick);

	protected:

//		virtual bool canSetFocus();
//		virtual void onSetFocus();
//		virtual void onLooseFocus();

//		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
//		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);

		virtual Bool onMouseDown(EMouseButton button, const CPoint2D& point);
		virtual Bool onMouseUp(EMouseButton button, const CPoint2D& point);

		virtual void controlDidBecomeFirstResponder();
		virtual void controlDidResignFirstResponder();


		virtual void draw(const CTheme* theme, CRenderingContext* constext) const;

//		virtual bool onMouseMove(int x, int y);

//		virtual bool onKeyPressed(unsigned char inKey);		
	private:
		CString mText;
		EButtonState mState;
		TOnClick mOnClick;
};


	} // namespace le
} // namespace sokira
