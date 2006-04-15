#include "slTCClass.h"

LE_NAMESPACE_START

const char* IClass::name() const
{
	return mName.c_str();
}

IClass::IClass(const char* name) :
	mName(name)
{

}

LE_NAMESPACE_END
