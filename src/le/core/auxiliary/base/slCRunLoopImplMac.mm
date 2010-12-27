//
//  slCRunLoopImplMac.mm
//  le
//
//  Created by Yuriy Glukhov on 5/17/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <le/core/config/slCompiler.h>

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#import <Cocoa/Cocoa.h>
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#import <UIKit/UIKit.h>
#else
#error No target platform defined
#endif

#import <le/core/auxiliary/slCRunLoop.h>
#import "slCRunloopImplMac.hp"

namespace sokira
{
	namespace le
	{

		
template <typename TPoint>
static inline CPoint2D CocoaPointToCPoint(const TPoint& point)
{
	return CPoint2D(point.x, point.y);
}

CEvent nextEventMatchingMask(UInt32 type)
{
	CEvent result;

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	NSUInteger cocoaMask = 0;
	if (type & eEventTypeMouseDown)
	{
		cocoaMask |= NSLeftMouseDownMask | NSRightMouseDownMask | NSOtherMouseDownMask;
	}

	if (type & eEventTypeMouseUp)
	{
		cocoaMask |= NSLeftMouseUpMask | NSRightMouseUpMask | NSOtherMouseUpMask;
	}

	if (type & eEventTypeMouseMove)
	{
		cocoaMask |= NSMouseMovedMask | NSLeftMouseDraggedMask | NSRightMouseDraggedMask | NSOtherMouseDraggedMask | NSMouseEnteredMask | NSMouseExitedMask;
	}

	if (type & eEventTypeKeyDown)
	{
		cocoaMask |= NSKeyDownMask;
	}

	if (type & eEventTypeKeyUp)
	{
		cocoaMask |= NSKeyUpMask;
	}

	NSEvent* event = [NSApp nextEventMatchingMask: cocoaMask untilDate: [NSDate distantFuture] inMode: NSDefaultRunLoopMode dequeue: YES];

	switch ([event type])
	{
		case NSLeftMouseDown:
			result = CEvent(eEventTypeMouseDown, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseDown:
			result = CEvent(eEventTypeMouseDown, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseDown:
			result = CEvent(eEventTypeMouseDown, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonOther);
			break;

		case NSLeftMouseUp:
			result = CEvent(eEventTypeMouseUp, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseUp:
			result = CEvent(eEventTypeMouseUp, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseUp:
			result = CEvent(eEventTypeMouseUp, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonOther);
			break;

		case NSMouseMoved:
		case NSLeftMouseDragged:
		case NSRightMouseDragged:
		case NSOtherMouseDragged:
		case NSMouseEntered:
		case NSMouseExited:
			result = CEvent(eEventTypeMouseMove, CocoaPointToCPoint([NSEvent mouseLocation]), eButtonStateUnknown, eKeyCodeUnknown);
			break;

		case NSKeyDown:
			result = CEvent(eEventTypeKeyDown, CRunLoopImpl::keyCodeFromSystemCode([event keyCode]), eButtonStateDown);
			break;

		case NSKeyUp:
			result = CEvent(eEventTypeKeyDown, CRunLoopImpl::keyCodeFromSystemCode([event keyCode]), eButtonStateUp);
			break;

		default:
			LE_ASSERT(false);
	}

#endif
	return result;
}

void postEvent(const CEvent& event)
{
	union
	{
		struct
		{
			NSInteger data1;
			NSInteger data2;
		};
		CEvent* pEvent;
	} u;
	u.pEvent = new CEvent(event);
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	[NSApp postEvent: [NSEvent otherEventWithType: NSApplicationDefined location: NSZeroPoint modifierFlags: 0 timestamp: 0 windowNumber: 0 context: 0 subtype: 0 data1: u.data1 data2: u.data2] atStart: NO];
#endif
//	[NSApp postEvent:  atStart:<#(BOOL)flag#>
}
		
	} // namespace le
} // namespace sokira
