#pragma once

#include <le/core/slTypes.h>
//#include <glut/slGlut.h>

namespace sokira
{
	namespace le
	{

enum EMouseButton
{
	eMouseButtonUnknown = 0,
	eMouseButtonLeft = LE_SET_BIT(1), // = GLUT_LEFT_BUTTON,
	eMouseButtonMiddle = LE_SET_BIT(2), // = GLUT_MIDDLE_BUTTON,
	eMouseButtonRight = LE_SET_BIT(3) // = GLUT_RIGHT_BUTTON
};

enum EButtonState
{
	eButtonStateUnknown = 0,
	eButtonStateDown = LE_SET_BIT(1), // = GLUT_DOWN,
	eButtonStateUp = LE_SET_BIT(2), // = GLUT_UP
};

	} // namespace le
} // namespace sokira
