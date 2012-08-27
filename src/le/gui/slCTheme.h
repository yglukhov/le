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

		virtual void drawControl(const CControl* control, CRenderingContext* context) const;
		virtual void drawButton(const CButton* button, CRenderingContext* context) const;
		virtual void drawWindow(const CView* window, CRenderingContext* context) const;
		virtual void drawStaticText(const CStaticText* text, CRenderingContext* context) const;
		virtual void drawScrollBar(const CScrollBar* scrollBar, CRenderingContext* context) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTheme_h
