#include "slCColor.h"
#include "slCDictionary.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CColor);

static const CString cRedKey = LESTR("r");
static const CString cGreenKey = LESTR("g");
static const CString cBlueKey = LESTR("b");
static const CString cAlphaKey = LESTR("a");


void CColor::serialize(CDictionary& toDictionary) const
{
	toDictionary.setValueForKey(cRedKey, redAs<UInt8>());
	toDictionary.setValueForKey(cGreenKey, greenAs<UInt8>());
	toDictionary.setValueForKey(cBlueKey, blueAs<UInt8>());
	toDictionary.setValueForKey(cAlphaKey, alphaAs<UInt8>());
}

void CColor::deserialize(const CDictionary& fromDictionary)
{
	setRed(fromDictionary.valueAsUInt8ForKey(cRedKey));
	setGreen(fromDictionary.valueAsUInt8ForKey(cGreenKey));
	setBlue(fromDictionary.valueAsUInt8ForKey(cBlueKey));
	setAlpha(fromDictionary.valueAsUInt8ForKey(cAlphaKey));
}


	} // namespace le
} // namespace sokira
