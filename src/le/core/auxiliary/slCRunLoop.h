#if !defined SL_LE_core_auxiliary_slCRunloop_hp
#define SL_LE_core_auxiliary_slCRunloop_hp

#include <list>
#include <le/core/slTypes.h>
#include <le/core/thread/slCMutex.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/geometry/slTCPoint2D.h>
#include "slCTimer.h"

namespace sokira
{
	namespace le
	{

class CRunLoopImpl;
class CEvent;

/*! Another enum, with inline docs */
enum EEventType
{
	eEventTypeUnknown = 0,
	eEventTypeMouseDown = LE_SET_BIT(1),
	eEventTypeMouseUp = LE_SET_BIT(2),
	eEventTypeMouseMove = LE_SET_BIT(3),
	eEventTypeKeyDown = LE_SET_BIT(4),
	eEventTypeKeyUp = LE_SET_BIT(5),
	eEventTypeAll = 0xFFFFFFFF
};

class CEvent
{
	public:
		CEvent();
		CEvent(EEventType type, EKeyCode keyCode, EButtonState state);
		CEvent(EEventType type, const CPoint2D& mouseLocation, EButtonState state, EKeyCode button);

		CPoint2D mouseLocation() const;
		EButtonState buttonState() const;
		EKeyCode mouseButton() const;
		EKeyCode keyCode() const;

		EEventType type() const;

		Bool isMouseEvent() const;
		Bool isKeyboardEvent() const;

	private:
		CPoint2D mLocation;
		EEventType mType;
		EKeyCode mKeyCode;
		EButtonState mButtonState;
};

class CRunLoop
/// Event handling core. The CRunLoop class declares the programmatic interface
/// to objects that manage input sources. A CRunLoop object processes input for
/// sources such as mouse and keyboard events from the window system, sockets,
/// timers, and other objects.
{
	public:
		/// Start the run loop.
		void run();

		/// Stop the run loop.
		void stop();

		/// Get next event. Can be used in a loop.
		/// @param mask some param
		CEvent nextEventMatchingType(UInt32 mask);

		CTimer scheduledTimerWithInterval(UInt32 msInterval, TCFunction<> timerFunc);

	private:
		friend class CThreadImplBase;
		CRunLoop();
		~CRunLoop();
		CRunLoopImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCRunloop_hp
