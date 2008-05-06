#pragma once

#include <le/core/config/slPrefix.h>
#include <glut/slGlut.h>

namespace sokira
{
	namespace le
	{

enum EMouseButton
{
	eMouseButtonUnknown = -1,
	eMouseButtonLeft = GLUT_LEFT_BUTTON,
	eMouseButtonMiddle = GLUT_RIGHT_BUTTON,
	eMouseButtonRight = GLUT_MIDDLE_BUTTON
};

enum EButtonState
{
	eButtonStateUnknown = -1,
	eButtonStateDown = GLUT_DOWN,
	eButtonStateUp = GLUT_UP
};

	} // namespace le
} // namespace sokira
