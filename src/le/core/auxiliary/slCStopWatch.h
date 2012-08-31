#if !defined SL_LE_core_auxiliary_slCStopWatch_h
#define SL_LE_core_auxiliary_slCStopWatch_h

#include <le/core/slCTime.h>

namespace sokira
{
	namespace le
	{
		
class CStopWatch
{
	public:
		CStopWatch();
		void reset();
		void start();
		void pause();
		UInt64 milliseconds() const;

	private:
		UInt64 mMilliseconds;
		CTime mStartTime;
};
		
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCStopWatch_h
