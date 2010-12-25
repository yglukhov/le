//
//  slCRunLoopImplMac.mm
//  le
//
//  Created by Yuriy Glukhov on 5/17/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <le/core/auxiliary/slCRunLoop.h>
#import "slCRunloopImplMac.hp"

namespace sokira
{
	namespace le
	{

static inline CPoint2D NSPointToCPoint(const NSPoint& point)
{
	return CPoint2D(point.x, point.y);
}

CEvent nextEventMatchingMask(UInt32 type)
{
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

	CEvent result;

	switch ([event type])
	{
		case NSLeftMouseDown:
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseDown:
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseDown:
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eKeyCodeMouseButtonOther);
			break;

		case NSLeftMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eKeyCodeMouseButtonOther);
			break;

		case NSMouseMoved:
		case NSLeftMouseDragged:
		case NSRightMouseDragged:
		case NSOtherMouseDragged:
		case NSMouseEntered:
		case NSMouseExited:
			result = CEvent(eEventTypeMouseMove, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUnknown, eKeyCodeUnknown);
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
	[NSApp postEvent: [NSEvent otherEventWithType: NSApplicationDefined location: NSZeroPoint modifierFlags: 0 timestamp: 0 windowNumber: 0 context: 0 subtype: 0 data1: u.data1 data2: u.data2] atStart: NO];
//	[NSApp postEvent:  atStart:<#(BOOL)flag#>
}
		
	} // namespace le
} // namespace sokira
