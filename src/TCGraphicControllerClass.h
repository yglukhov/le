#pragma once

#include "TCClass.h"

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

	void _register_graphic_controller(const char*, const char*, const char*);
	_register_graphic_controller(className, themeClassName, controlClassName);
}