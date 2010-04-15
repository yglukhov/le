#include "slCStaticText.h"
#include "slCTheme.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CStaticText);

CStaticText::CStaticText()
{

}

CStaticText::CStaticText(const CString& text) :
	mText(text)
{

}

CStaticText::CStaticText(const CString& text, const CRectangle& rect) :
	CControl(rect),
	mText(text)
{

}

void CStaticText::setText(const CString& text)
{
	mText = text;
}

CString CStaticText::text() const
{
	return mText;
}

void CStaticText::draw(const CTheme* theme, CRenderingContext* context) const
{
	theme->drawStaticText(this, context);
}

	} // namespace le
} // namespace sokira

