#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <le/gui/slCWindow.h>
#import <le/core/auxiliary/slCRunloop.h>
#import <le/core/auxiliary/base/slCRunloopImplMac.hp>
//#import <le/core/slCString.h>
#import "slCCocoaWindowImpl.hp"

@interface SokiraLE_OpenGLView : NSOpenGLView
{
	::sokira::le::CWindow* mScreen;
	BOOL mMouseInView;
	BOOL mViewDidResize;
}
@end

@implementation SokiraLE_OpenGLView

- (id) initWithScreen: (::sokira::le::CWindow*) screen
{
	NSOpenGLPixelFormatAttribute attributes [] =
	{
		NSOpenGLPFAWindow,
		NSOpenGLPFADoubleBuffer,	// double buffered
		NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16, // 16 bit depth buffer
		(NSOpenGLPixelFormatAttribute)nil
	};

	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	self = [super initWithFrame: NSZeroRect pixelFormat: pixelFormat];
	[pixelFormat release];

	mScreen = screen;
	mMouseInView = NO;
	mViewDidResize = YES;
	return self;
}

- (void) drawRect: (NSRect) bounds
{
	LE_ASSERT(mScreen);

	BOOL liveResize = [self inLiveResize];
	if (!mViewDidResize)
	{
		mViewDidResize = liveResize;
	}

	if (mViewDidResize)
	{
		mScreen->onResize();
		mViewDidResize = NO;
	}

	mScreen->draw();
	[[self openGLContext] flushBuffer];
	GLenum err = glGetError();
	if (GL_NO_ERROR != err)
		std::cout << gluErrorString (err) << std::endl;
}

- (void)keyDown:(NSEvent *)theEvent
{
//	NSString* chars = [theEvent charactersIgnoringModifiers];
//	NSLog(@"keydown: %@", [theEvent characters]);
//	NSLog(@"nomodif: %@", chars);
//	NSLog(@"keycode: %d", (int)[theEvent keyCode]);

//	const char * str = [chars cStringUsingEncoding: NSNonLossyASCIIStringEncoding];
//	::sokira::le::CString characters = (str)?(str):(::sokira::le::CString());
	mScreen->onKeyDown(::sokira::le::CRunLoopImpl::keyCodeFromSystemCode([theEvent keyCode]));
}

- (void)keyUp:(NSEvent *)theEvent
{
//	NSString* chars = [theEvent charactersIgnoringModifiers];
//	const char * str = [chars cStringUsingEncoding: NSNonLossyASCIIStringEncoding];
//	::sokira::le::CString characters = (str)?(str):(::sokira::le::CString());
	mScreen->onKeyUp(::sokira::le::CRunLoopImpl::keyCodeFromSystemCode([theEvent keyCode]));
}

- (void)flagsChanged:(NSEvent *)theEvent
{
	std::cout << "flagsChanged:" << std::endl;
	NSLog(@"%@", theEvent);
}

- (void) mouseMoved: (NSEvent *) event
{
	NSPoint point = [event locationInWindow];
	NSSize size = [self frame].size;

	// Invert Y coord
	point.y = size.height - point.y;

	if (point.x < 0.0 || point.y < 0.0 || point.x > size.width || point.y > size.height)
	{
		if (mMouseInView)
		{
			mMouseInView = NO;

			if (point.x < 0.0) point.x = 0.0;
			if (point.y < 0.0) point.y = 0.0;
			if (point.x > size.width) point.x = size.width;
			if (point.y > size.height) point.y = size.height;

			LE_ASSERT(mScreen);
			mScreen->onMouseOut(::sokira::le::CPoint2D(point.x, point.y));
		}
	}
	else
	{
		LE_ASSERT(mScreen);

		if (!mMouseInView)
		{
			mMouseInView = YES;
			mScreen->onMouseIn(::sokira::le::CPoint2D(point.x, point.y));
		}

		// On Mouse Hover
		mScreen->onMouse(::sokira::le::eKeyCodeUnknown, ::sokira::le::eButtonStateUnknown,
			::sokira::le::CPoint2D(point.x, point.y));

//		mScreen->onMouseHover(::sokira::le::CPoint(point.x, point.y));
	}
}

- (void) anyMouseDown: (NSEvent*) event button: (::sokira::le::EKeyCode) button
{
	NSPoint point = [event locationInWindow];

	// Invert Y coord
	point.y = [self frame].size.height - point.y;

	LE_ASSERT(mScreen);
	mScreen->onMouse(button, ::sokira::le::eButtonStateDown,
			::sokira::le::CPoint2D(point.x, point.y));
//
//	mScreen->onMouseDown(button, ::sokira::le::CPoint(point.x, point.y));
}

- (void) anyMouseUp: (NSEvent*) event button: (::sokira::le::EKeyCode) button
{
	NSPoint point = [event locationInWindow];
	NSSize size = [self frame].size;

	// Invert Y coord
	point.y = size.height - point.y;

	if (point.x < 0.0) point.x = 0.0;
	else if (point.x > size.width) point.x = size.width;
	if (point.y < 0.0) point.y = 0.0;
	else if (point.y > size.height) point.y = size.height;

	LE_ASSERT(mScreen);
	mScreen->onMouse(button, ::sokira::le::eButtonStateUp,
			::sokira::le::CPoint2D(point.x, point.y));
//	mScreen->onMouseUp(button, ::sokira::le::CPoint(point.x, point.y));
}

- (void) mouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eKeyCodeMouseButtonPrimary];
}

- (void) mouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eKeyCodeMouseButtonPrimary];
}

- (void)mouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void) rightMouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eKeyCodeMouseButtonSecondary];
}

- (void) rightMouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eKeyCodeMouseButtonSecondary];
}

- (void) rightMouseDragged: (NSEvent*) event
{
	[self mouseMoved:event];
}

- (void) otherMouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eKeyCodeMouseButtonOther];
}

- (void) otherMouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eKeyCodeMouseButtonOther];
}

- (void) otherMouseDragged: (NSEvent*) event
{
	[self mouseMoved:event];
}

- (BOOL) acceptsFirstResponder
{
	return YES;
}

- (void) prepareOpenGL
{
	LE_ASSERT(mScreen);
	mScreen->_prepareOpenGL();
}

- (void) swipeWithEvent: (NSEvent *) event
{
	NSLog(@"Swipe: %@", event);
}

- (void) rotateWithEvent: (NSEvent *) event
{
	NSLog(@"Rotate: %@", event);
}

- (void) magnifyWithEvent: (NSEvent *) event
{
	NSLog(@"Magnify: %@", event);
}

- (void)viewWillStartLiveResize
{
//	LE_ASSERT(mScreen);
//	mScreen->_screenWasResized();
	mViewDidResize = YES;
}

- (void)viewDidEndLiveResize
{
//	LE_ASSERT(mScreen);
//	mScreen->_screenWasResized();
	mViewDidResize = YES;
}

- (void) parentWindowWillClose: (NSNotification*) notification
{
	mScreen->_screenWillBeClosed();
//	std::cout << "parentWindowWillClose!" << std::endl;
}

@end


namespace sokira
{
	namespace le
	{

CCocoaWindowImpl::CCocoaWindowImpl(bool fullScreen, const CString& title, const CRectangle& rect) :
	mFullScreen(fullScreen),
	mTitle(title),
	mRect(rect),
	mWindow(NULL)
{

}

void CCocoaWindowImpl::screenWillBeAddedToApplication(CWindow* screen, CGuiCocoaApplication* app)
{

}

void CCocoaWindowImpl::screenWasAddedToApplication(CWindow* screen, CGuiCocoaApplication* app)
{
	NSRect frame = NSMakeRect(mRect.x(), mRect.y(), mRect.width(), mRect.height());

	mWindow = (void*)[[NSWindow alloc]
					initWithContentRect: frame
					styleMask: NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
					backing: NSBackingStoreBuffered
					defer: NO];

	NSString* title = [NSString stringWithCString: mTitle.cString() encoding: NSASCIIStringEncoding];

	[(NSWindow*)mWindow setTitle: title];
	[(NSWindow*)mWindow setAcceptsMouseMovedEvents: YES];
	NSView* view = [[SokiraLE_OpenGLView alloc] initWithScreen: screen];
	[[NSNotificationCenter defaultCenter] addObserver:view selector:@selector(parentWindowWillClose:) name:NSWindowWillCloseNotification object:static_cast<NSWindow*>(mWindow)];
	[(NSWindow*)mWindow setContentView: view];
	[view release];
	[(NSWindow*)mWindow makeKeyAndOrderFront: nil];
}

void CCocoaWindowImpl::screenWillBeRemovedFromApplication(CWindow* screen, CGuiCocoaApplication* app)
{
	std::cout << "screenWillBeRemovedFromApplication" << std::endl;
	if (mWindow)
	{
		[(NSWindow*)mWindow release];
	}

	mWindow = NULL;
}

void CCocoaWindowImpl::screenWasRemovedFromApplication(CWindow* screen, CGuiCocoaApplication* app)
{

}

Bool CCocoaWindowImpl::inLiveResize() const
{
	return _LE_BOOL_CAST([[(NSWindow*)mWindow contentView] inLiveResize]);
}

CSize2D CCocoaWindowImpl::size() const
{
	id view = [static_cast<NSWindow*>(mWindow) contentView];
	if (view)
	{
		NSSize result = [view frame].size;
		return CSize2D(result.width, result.height);
	}
	return mRect.size();
}

void CCocoaWindowImpl::setSize(const CSize2D& size)
{
	if (mWindow)
	{
		[(NSWindow*)mWindow setContentSize: NSMakeSize(size.width(), size.height())];
	}

	mRect.setSize(size);
}

void CCocoaWindowImpl::setNeedsRedraw()
{
	[[(NSWindow*)mWindow contentView] setNeedsDisplay: YES];
}

CString CCocoaWindowImpl::title() const
{
	return mTitle;
}


	} // namespace le
} // namespace sokira
