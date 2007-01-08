#pragma once

#include <le/core/slCClass.h>

#define LE_IMPLEMENT_GRAPHIC_CONTROLLER(Class, themeClass, controlClass)\
	static TCGraphicControllerClass<Class> _le_##Class##_ClassInfo_(	\
								#Class, #themeClass, #controlClass);	\
	_LE_IMPLEMENT_RUNTIME_CLASS(Class)

#define LE_DECLARE_GRAPHIC_CONTROLLER(Class) \
	LE_DECLARE_RUNTIME_CLASS(Class)

void _le_register_graphic_controller(const char*,
									 const char*,
									 const char*);


namespace sokira
{
	namespace le
	{

template <class T>
class TCGraphicControllerClass : public TCClassImpl<T>
{
	public:
		TCGraphicControllerClass(const char* className,
						const char* themeClassName, const char* controlClassName);
};


template <class T>
TCGraphicControllerClass<T>::TCGraphicControllerClass(const char* className,
						const char* themeClassName, const char* controlClassName) :
	TCClassImpl<T>(className)
{
	_le_register_graphic_controller(className, themeClassName, controlClassName);
}


	} // namespace le
} // namespace sokira

