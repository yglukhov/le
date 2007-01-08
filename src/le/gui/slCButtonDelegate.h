#pragma once

#include <le/core/config/slPrefix.h>
namespace sokira
{
	namespace le
	{

class CWindow;
class CButtonDelegate
{
	virtual void OnButtonPressed(CWindow& sender){};
	
};

	} // namespace le
} // namespace sokira
