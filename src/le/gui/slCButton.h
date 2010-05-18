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

		virtual Bool onMouseDown(EKeyCode button, const CPoint2D& point);
		virtual void draw(const CTheme* theme, CRenderingContext* constext) const;

	private:
		CString mText;
		EButtonState mState;
		TOnClick mOnClick;
};


	} // namespace le
} // namespace sokira
