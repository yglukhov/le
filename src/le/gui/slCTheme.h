#if !defined SL_LE_gui_slCTheme_h
#define SL_LE_gui_slCTheme_h

#include <le/core/slCString.h>
#include <le/gui/slConstants.h>

namespace sokira
{
	namespace le
	{

class CControl;
class CWindow;
class CButton;
class CStaticText;
class CRenderingContext;

class CTheme
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CTheme)
	LE_RTTI_END

	public:
		CTheme();

		void drawControl(const CControl* control, CRenderingContext* context) const;
		void drawButton(const CButton* button, CRenderingContext* context) const;
		void drawWindow(const CWindow* window, CRenderingContext* context) const;
		void drawStaticText(const CStaticText* text, CRenderingContext* context) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTheme_h
