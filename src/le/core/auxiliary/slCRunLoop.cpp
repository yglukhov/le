#include "slCRunLoop.h"

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX || LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#include "base/slCRunLoopImplMac.hp"
#elif  LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include "base/slCRunloopImplWin.hp"
#else
#error No implementation
#endif

namespace sokira
{
	namespace le
	{

CEvent::CEvent() :
	mType(eEventTypeUnknown)
{

}

CEvent::CEvent(EEventType type, EKeyCode keyCode, EButtonState state) :
	mType(type),
	mKeyCode(keyCode),
	mButtonState(state)
{

}

CEvent::CEvent(EEventType type, const CPoint2D& mouseLocation, EButtonState state, EKeyCode button) :
	mLocation(mouseLocation),
	mType(type),
	mKeyCode(button),
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

EKeyCode CEvent::mouseButton() const
{
	return mKeyCode;
}

EKeyCode CEvent::keyCode() const
{
	return mKeyCode;
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

void CRunLoop::postEvent(const CEvent& event)
{
//	mImpl->postEvent(event);
}

CTimer CRunLoop::scheduledTimerWithInterval(UInt32 msInterval, TCFunction<> timerFunc)
{
	return mImpl->scheduledTimerWithInterval(msInterval, timerFunc);
}

	} // namespace le
} // namespace sokira
