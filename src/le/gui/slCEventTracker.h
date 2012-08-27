#if !defined SL_LE_gui_slCEventTracker_h
#define SL_LE_gui_slCEventTracker_h

#include <le/core/slCObject.h>
#include <le/core/auxiliary/slCRunLoop.h>


namespace sokira
{
	namespace le
	{

enum EEventTrackerState
{
	eEventTrackerStatePossible = 0,
	eEventTrackerStateBegan,
	eEventTrackerStateChanged,
	eEventTrackerStateEnded,
	eEventTrackerStateCancelled
};

class CEventTracker : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CEventTracker)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		virtual void reset();
		virtual EEventType acceptedEvents() const;
		virtual EEventTrackerState state() const;
		virtual void handleEvent(CEvent* event);
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_gui_slCEventTracker_h
