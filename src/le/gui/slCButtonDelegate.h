#pragma once

#include <le/core/config/slPrefix.h>
LE_NAMESPACE_START

class CWindow;
class CButtonDelegate
{
	virtual void OnButtonPressed(CWindow& sender){};
	
};

LE_NAMESPACE_END
