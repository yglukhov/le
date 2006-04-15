#pragma once

#include <config/slPrefix.h>
#include <class/slTCClass.h>

LE_NAMESPACE_START

template <class T>
class TCGraphicControllerClass : public TCClass<T>
{
	public:
		TCGraphicControllerClass(const char* className, const char* themeClassName, const char* controlClassName);
};


template <class T>
TCGraphicControllerClass<T>::TCGraphicControllerClass(const char* className,
						const char* themeClassName, const char* controlClassName) :
	TCClass<T>(className)
{

	void _le_register_graphic_controller(const char*, const char*, const char*);
	_le_register_graphic_controller(className, themeClassName, controlClassName);
}


LE_NAMESPACE_END
