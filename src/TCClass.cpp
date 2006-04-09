
#include "TCClass.h"

const char* IClass::name() const
{
	return mName.c_str();
}

IClass::IClass(const char* name) :
	mName(name)
{

}