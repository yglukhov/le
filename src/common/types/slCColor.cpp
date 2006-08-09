#include "slCColor.h"
#include "slCDictionary.h"

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CColor);

static const CString cRedKey = LESTR("r");
static const CString cGreenKey = LESTR("g");
static const CString cBlueKey = LESTR("b");
static const CString cAlphaKey = LESTR("a");


void CColor::serialize(CDictionary& toDictionary) const
{
	toDictionary.valueForKey(cRedKey, redAs<UInt8>());
	toDictionary.valueForKey(cGreenKey, greenAs<UInt8>());
	toDictionary.valueForKey(cBlueKey, blueAs<UInt8>());
	toDictionary.valueForKey(cAlphaKey, alphaAs<UInt8>());
}

void CColor::deserialize(const CDictionary& fromDictionary)
{
	red(fromDictionary.valueAsUInt8ForKey(cRedKey));
	green(fromDictionary.valueAsUInt8ForKey(cGreenKey));
	blue(fromDictionary.valueAsUInt8ForKey(cBlueKey));
	alpha(fromDictionary.valueAsUInt8ForKey(cAlphaKey));
}


LE_NAMESPACE_END
