#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <le/gui/slCScreen.h>
#import <le/core/auxiliary/slCRunloop.h>
#import <le/core/auxiliary/base/slCRunloopImplMac.hp>
//#import <le/core/slCString.h>
#import "slCCocoaScreenImpl.hp"

@interface SokiraLE_OpenGLView : NSOpenGLView
{
	::sokira::le::CScreen* mScreen;
	BOOL mMouseInView;
	BOOL mViewDidResize;
}
@end

@implementation SokiraLE_OpenGLView

- (id) initWithFrame: (NSRect) frame andScreen: (::sokira::le::CScreen*) screen
{
	NSOpenGLPixelFormatAttribute attributes [] =
	{
		NSOpenGLPFAWindow,
		NSOpenGLPFADoubleBuffer,	// double buffered
		NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16, // 16 bit depth buffer
		(NSOpenGLPixelFormatAttribute)nil
	};

	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	self = [super initWithFrame: frame pixelFormat: pixelFormat];
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

CCocoaScreenImpl::CCocoaScreenImpl(bool fullScreen, const CString& title, const CRectangle& rect) :
	mFullScreen(fullScreen),
	mTitle(title),
	mRect(rect),
	mWindow(NULL)
{

}

void CCocoaScreenImpl::screenWillBeAddedToApplication(CScreen* screen, CGuiApplication* app)
{

}

void CCocoaScreenImpl::screenWasAddedToApplication(CScreen* screen, CGuiApplication* app)
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
	NSView* view = [[[SokiraLE_OpenGLView alloc] initWithFrame:frame andScreen: screen] autorelease];
	[[NSNotificationCenter defaultCenter] addObserver:view selector:@selector(parentWindowWillClose:) name:NSWindowWillCloseNotification object:static_cast<NSWindow*>(mWindow)];
	[(NSWindow*)mWindow setContentView: view];
	[(NSWindow*)mWindow makeKeyAndOrderFront: nil];
}

void CCocoaScreenImpl::screenWillBeRemovedFromApplication(CScreen* screen, CGuiApplication* app)
{
	std::cout << "screenWillBeRemovedFromApplication" << std::endl;
	if (mWindow)
	{
		[static_cast<NSWindow*>(mWindow) release];
	}

	mWindow = NULL;
}

void CCocoaScreenImpl::screenWasRemovedFromApplication(CScreen* screen, CGuiApplication* app)
{

}

Bool CCocoaScreenImpl::inLiveResize() const
{
	return _LE_BOOL_CAST([[static_cast<NSWindow*>(mWindow) contentView] inLiveResize]);
}

CSize2D CCocoaScreenImpl::size() const
{
	id view = [static_cast<NSWindow*>(mWindow) contentView];
	if (view)
	{
		NSRect rect = [view frame];
		return CSize2D(rect.size.width, rect.size.height);
	}
	return mRect.size();
}

void CCocoaScreenImpl::setSize(const CSize2D& size)
{
	if (mWindow)
	{
		[static_cast<NSWindow*>(mWindow) setContentSize:NSMakeSize(size.width(), size.height())];
	}

	mRect.setSize(size);
}

void CCocoaScreenImpl::setNeedsRedraw()
{
	[[static_cast<NSWindow*>(mWindow) contentView] setNeedsDisplay:YES];
}

CString CCocoaScreenImpl::title() const
{
	return mTitle;
}


	} // namespace le
} // namespace sokira
