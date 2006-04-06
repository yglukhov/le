#pragma once

#include "TCClass.h"

class CObject;



////////////////////////////////////////////////////////////////////////////////
// This macro must be used in class implementation section in global namespace.
// The class must be inherited from CObject.
#define IMPLEMENT_RUNTIME_CLASS(Class)									\
																					\
static TCClass<Class> _##Class##_class_description_(#Class);	\
																					\
IClass* Class::staticClass()												\
{																					\
	return &_##Class##_class_description_;								\
}																					\
																					\
IClass* Class::objectClass() const										\
{																					\
	return &_##Class##_class_description_;								\
}
