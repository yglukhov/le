#include "slTCClass.h"
#include <string.h>

LE_NAMESPACE_START

CString IClass::name() const
{
	return mName;
}

IClass::IClass(CString name) :
	mName(name)
{

}

bool IClass::operator == (const IClass& rhs) const
{
	return !strcmp(stdTypeInfoName(), rhs.stdTypeInfoName());
}

LE_NAMESPACE_END
