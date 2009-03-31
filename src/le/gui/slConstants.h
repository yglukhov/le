#if !defined SL_LE_gui_slCConstants_h
#define SL_LE_gui_slCConstants_h

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

enum EMouseButton
{
	eMouseButtonUnknown = 0,
	eMouseButtonLeft = LE_SET_BIT(1),
	eMouseButtonMiddle = LE_SET_BIT(2),
	eMouseButtonRight = LE_SET_BIT(3)
};

enum EButtonState
{
	eButtonStateUnknown = 0,
	eButtonStateDown = LE_SET_BIT(1),
	eButtonStateUp = LE_SET_BIT(2),
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCConstants_h
