#pragma once

#include <common/config/slPrefix.h>
#include <common/class/slTCClass.h>

#define IMPLEMENT_GRAPHIC_CONTROLLER(Class, themeClass, controlClass)	\
static TCGraphicControllerClass<Class> _##Class##_controller_class(		\
								#Class, #themeClass, #controlClass)


void _le_register_graphic_controller(const char*, const char*, const char*);


LE_NAMESPACE_START

template <class T>
class TCGraphicControllerClass : public TCClass<T>
{
	public:
		TCGraphicControllerClass(const char* className, const char* themeClassName,
										 const char* controlClassName);
};


template <class T>
TCGraphicControllerClass<T>::TCGraphicControllerClass(const char* className,
						const char* themeClassName, const char* controlClassName) :
	TCClass<T>(className)
{
	_le_register_graphic_controller(className, themeClassName, controlClassName);
}


LE_NAMESPACE_END
