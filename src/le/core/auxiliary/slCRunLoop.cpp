#include "slCRunLoop.h"

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#include "base/slCRunloopImplMac.hp"
#elif  LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCRunloopImplWin.hp"
#else
#error No implementation
#endif

namespace sokira
{
	namespace le
	{

CEvent::CEvent()
{

}

CEvent::CEvent(EEventType type, WChar keyCode, EButtonState state) :
	mType(type),
	mKeyCode(keyCode),
	mButtonState(state)
{

}

CEvent::CEvent(EEventType type, const CPoint2D& mouseLocation, EButtonState state, EMouseButton button) :
	mLocation(mouseLocation),
	mType(type),
	mMouseButton(button),
	mButtonState(state)
{

}

CPoint2D CEvent::mouseLocation() const
{
	return mLocation;
}

EButtonState CEvent::buttonState() const
{
	return mButtonState;
}

EMouseButton CEvent::mouseButton() const
{
	return mMouseButton;
}

EEventType CEvent::type() const
{
	return mType;
}

Bool CEvent::isMouseEvent() const
{
	return _LE_BOOL_CAST(type() & (eEventTypeMouseDown | eEventTypeMouseUp | eEventTypeMouseMove));
}

Bool CEvent::isKeyboardEvent() const
{
	return _LE_BOOL_CAST(type() & (eEventTypeKeyDown | eEventTypeKeyUp));
}


CRunLoop::CRunLoop() :
	mImpl(new CRunLoopImpl())
{

}

CRunLoop::~CRunLoop()
{
	delete mImpl;
}

void CRunLoop::run()
{
	mImpl->run();
}

void CRunLoop::stop()
{
	mImpl->stop();
}

CEvent CRunLoop::nextEventMatchingType(UInt32 mask)
{
	return mImpl->nextEventMatchingMask(mask);
}

CTimer CRunLoop::scheduledTimerWithInterval(UInt32 msInterval, TCFunction<> timerFunc)
{
	return mImpl->scheduledTimerWithInterval(msInterval, timerFunc);
}

	} // namespace le
} // namespace sokira
