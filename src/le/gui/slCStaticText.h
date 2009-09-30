#if !defined SL_LE_gui_slCStaticText_h
#define SL_LE_gui_slCStaticText_h

#include <le/core/slCString.h>
#include "slCControl.h"

namespace sokira
{
	namespace le
	{

class CStaticText : public CControl
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CStaticText)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CStaticText();
		CStaticText(const CString& text);
		CStaticText(const CString& text, const CRectangle& rect);

		void setText(const CString& text);
		CString text() const;

		virtual void draw(const CTheme* theme, CRenderingContext* context) const;

	private:
		CString mText;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCStaticText_h
