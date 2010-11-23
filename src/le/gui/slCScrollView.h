#if !defined SL_LE_gui_slCScrollView_h
#define SL_LE_gui_slCScrollView_h

//#include <le/core/slCString.h>
#include "slCView.h"

namespace sokira
{
	namespace le
	{

class CScrollBar;

class CScrollView : public CView
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CScrollView)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CScrollView();
		CScrollView(const CRectangle& rect);

		void setContent(CControl* content);
		CControl* content() const;

		virtual void draw(const CTheme* theme, CRenderingContext* context) const;

		void onVerticalPositionChanged(CScrollBar* scrollBar);
		void onHorizontalPositionChanged(CScrollBar* scrollBar);

	private:
		CControl* mContent;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCScrollView_h
