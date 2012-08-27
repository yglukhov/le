#include "slCEventTracker.h"


namespace sokira
{
	namespace le
	{
		
LE_IMPLEMENT_RUNTIME_CLASS(CEventTracker);

void CEventTracker::reset()
{

}

EEventType CEventTracker::acceptedEvents() const
{
	return eEventTypeUnknown;
}

EEventTrackerState CEventTracker::state() const
{
	return eEventTrackerStatePossible;
}
		
void CEventTracker::handleEvent(CEvent* event)
{

}

	} // namespace le
} // namespace sokira
