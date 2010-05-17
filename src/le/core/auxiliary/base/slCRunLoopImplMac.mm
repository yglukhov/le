//
//  slCRunLoopImplMac.mm
//  le
//
//  Created by Yuriy Glukhov on 5/17/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <le/core/auxiliary/slCRunLoop.h>

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
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eMouseButtonLeft);
			break;

		case NSRightMouseDown:
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eMouseButtonRight);
			break;

		case NSOtherMouseDown:
			result = CEvent(eEventTypeMouseDown, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateDown, eMouseButtonMiddle);
			break;

		case NSLeftMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eMouseButtonLeft);
			break;

		case NSRightMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eMouseButtonRight);
			break;

		case NSOtherMouseUp:
			result = CEvent(eEventTypeMouseUp, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUp, eMouseButtonMiddle);
			break;

		case NSMouseMoved:
		case NSLeftMouseDragged:
		case NSRightMouseDragged:
		case NSOtherMouseDragged:
		case NSMouseEntered:
		case NSMouseExited:
			result = CEvent(eEventTypeMouseMove, NSPointToCPoint([NSEvent mouseLocation]), eButtonStateUnknown, eMouseButtonUnknown);
			break;

		case NSKeyDown:
			result = CEvent(eEventTypeKeyDown, 0, eButtonStateDown);
			break;

		case NSKeyUp:
			result = CEvent(eEventTypeKeyDown, 0, eButtonStateUp);
			break;

		default:
			LE_ASSERT(false);
	}

	return result;
}

	} // namespace le
} // namespace sokira
