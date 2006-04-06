#pragma once

#include "TCGraphicControllerClass.h"

#define IMPLEMENT_GRAPHIC_CONTROLLER(Class, themeClass, controlClass)	\
static TCGraphicControllerClass<Class> _##Class##_controller_class(#Class, #themeClass, #controlClass);
