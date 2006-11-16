#pragma once

#include <le/core/slTCClass.h>

#define IMPLEMENT_GRAPHIC_CONTROLLER(Class, themeClass, controlClass)	\
static TCGraphicControllerClass<Class> _##Class##_controller_class(		\
								LESTR(#Class), LESTR(#themeClass), LESTR(#controlClass))


void _le_register_graphic_controller(const CBasicString&, const CBasicString&, const CBasicString&);


LE_NAMESPACE_START

template <class T>
class TCGraphicControllerClass : public TCClass<CObject, T>
{
	public:
		TCGraphicControllerClass(const CBasicString& className, const CBasicString& themeClassName,
										 const CBasicString& controlClassName);
};


template <class T>
TCGraphicControllerClass<T>::TCGraphicControllerClass(const CBasicString& className,
						const CBasicString& themeClassName, const CBasicString& controlClassName) :
	TCClass<CObject, T>(className)
{
	_le_register_graphic_controller(className, themeClassName, controlClassName);
}


LE_NAMESPACE_END

