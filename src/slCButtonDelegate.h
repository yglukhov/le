#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

class CWindow;
class CButtonDelegate
{
	virtual void OnButtonPressed(CWindow& sender){};
	
};

LE_NAMESPACE_END
