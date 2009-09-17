#if !defined SL_LE_gui_slCTimer_h
#define SL_LE_gui_slCTimer_h

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

class CTimerImpl;

class CTimer
{
	public:
		CTimer(UInt32 msInterval);


		void __onTimer_private();

	private:
		CTimerImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTimer_h
