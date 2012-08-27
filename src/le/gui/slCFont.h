#if !defined SL_LE_gui_slCFont_h
#define SL_LE_gui_slCFont_h

//#include <vector>
#include <le/core/slCURL.h>
#include <le/core/slCImage.h>
#include <le/core/slCResult.h>

namespace sokira
{
	namespace le
	{

class CFont : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CFont)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CFont();
		CFont(const CURL& fontURL, Float32 fontSize);

		Float32 size() const;
		void setSize(Float32 size);

		typedef std::vector<std::pair<Float32, Float32> > CGlyphPositions;
		CResult getGlyphDataForString(const CString& string, CImage& image, CGlyphPositions& glyphPositions) const;

		void setRendererInfo(CObject::Ptr rendererInfo);
		CObject::Ptr rendererInfo() const;

	private:
		CURL mFontURL;
		Float32 mSize;
		CObject::Ptr mRendererInfo;
		Bool mNeedsRecomputeRendererInfo;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCFont_h
