#pragma once

#include <le/core/config/slPrefix.h>
#include <glut/slGlut.h>

namespace sokira
{
	namespace le
	{

#define LE_SET_BIT(x) (1 << (x))

enum EStatus
{
	eStatusOK = 0, // Not an error
	eStatusErrorOpenFailed
};

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

enum EFolderNode
{
	eFolderNodeUnknown = 0,
	eFolderNodeFolder,
	eFolderNodeRegular,
	eFolderNodeLink,
	eFolderNodeFIFO, // DO NOT USE
	eFolderNodeChr, // DO NOT USE
	eFolderNodeBlk, // DO NOT USE
	eFolderNodeSocket, // DO NOT USE
	eFolderNodeWht // DO NOT USE
};

	} // namespace le
} // namespace sokira
