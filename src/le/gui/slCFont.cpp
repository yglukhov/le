#include <le/core/config/slCompiler.h>
#include "slCFont.h"

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#include "base/slCFontGlyphGeneratorMac.hp"
//#include "base/slCFontGlyphGeneratorInline.hp"
//#include "base/slCFontGlyphGeneratorFreetype.hp"
#elif LE_TARGET_PLATWORM == LE_PLATPORM_WINDOWS
#include "base/slCFontGlyphGeneratorInline.hp"
//#include "base/slCFontGlyphGeneratorWindows.hp"
#endif

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CFont);

CFont::CFont()
{

}

CFont::CFont(const CURL& fontURL, Float32 fontSize)
{

}

Float32 CFont::size() const
{
	return mSize;
}

void CFont::setSize(Float32 size)
{
	mSize = size;
}

CResult CFont::getGlyphDataForString(const CString& string, CImage& image, CGlyphPositions& glyphPositions) const
{
	CFontGlyphGenerator generator;
	return generator.getGlyphDataForString(*this, string, image, glyphPositions);
}

void CFont::setRendererInfo(CObject::Ptr rendererInfo)
{
	mRendererInfo = rendererInfo;
}

CObject::Ptr CFont::rendererInfo() const
{
	return mRendererInfo;
}

	} // namespace le
} // namespace sokira
