#if !defined SL_LE_gui_slCTheme_h
#define SL_LE_gui_slCTheme_h

#include <le/core/slCString.h>
#include <le/gui/slConstants.h>

namespace sokira
{
	namespace le
	{

class CControl;
class CView;
class CButton;
class CStaticText;
class CScrollBar;
class CRenderingContext;

class CTheme
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CTheme)
	LE_RTTI_END

	public:
		CTheme();
		virtual ~CTheme();

		void drawControl(const CControl* control, CRenderingContext* context) const;
		void drawButton(const CButton* button, CRenderingContext* context) const;
		void drawWindow(const CView* window, CRenderingContext* context) const;
		void drawStaticText(const CStaticText* text, CRenderingContext* context) const;
		void drawScrollBar(const CScrollBar* scrollBar, CRenderingContext* context) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTheme_h
