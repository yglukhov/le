#pragma once

#include <common/class/slTCClass.h>

#define IMPLEMENT_GRAPHIC_CONTROLLER(Class, themeClass, controlClass)	\
static TCGraphicControllerClass<Class> _##Class##_controller_class(		\
								LESTR(#Class), LESTR(#themeClass), LESTR(#controlClass))


void _le_register_graphic_controller(const CString&, const CString&, const CString&);


LE_NAMESPACE_START

template <class T>
class TCGraphicControllerClass : public TCClass<CObject, T>
{
	public:
		TCGraphicControllerClass(const CString& className, const CString& themeClassName,
										 const CString& controlClassName);
};


template <class T>
TCGraphicControllerClass<T>::TCGraphicControllerClass(const CString& className,
						const CString& themeClassName, const CString& controlClassName) :
	TCClass<CObject, T>(className)
{
	_le_register_graphic_controller(className, themeClassName, controlClassName);
}


LE_NAMESPACE_END

