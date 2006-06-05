#include "slTCClass.h"

LE_NAMESPACE_START

CString IClass::name() const
{
	return mName;
}

IClass::IClass(CString name) :
	mName(name)
{

}

LE_NAMESPACE_END
