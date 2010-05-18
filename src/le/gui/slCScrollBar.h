#if !defined SL_LE_gui_slCScrollBar_h
#define SL_LE_gui_slCScrollBar_h

#include <le/core/template/function/slTCFunction.h>
#include "slCControl.h"

namespace sokira
{
	namespace le
	{

class CScrollBar : public CControl
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CScrollBar)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CScrollBar();
		CScrollBar(const CRectangle& rect, Bool horizontal = true);


		typedef TCFunction<void, TSTypeList<CScrollBar*> > TOnPositionChanged;

		void setHorizontal();
		void setVertical();
		Bool isHorizontal() const;
		Float32 position() const;
		void setOnPositionChanged(TOnPositionChanged& function);

		virtual Bool onMouseDown(EKeyCode button, const CPoint2D& point);

		virtual void draw(const CTheme* theme, CRenderingContext* context) const;

	private:
		void onPositionChanged();
		TOnPositionChanged mOnPositionChanged;
		Bool mHorizontal;
		Float32 mPosition;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCScrollBar_h
