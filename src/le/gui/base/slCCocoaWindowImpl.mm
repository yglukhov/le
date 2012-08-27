#import <QuartzCore/QuartzCore.h>
#import <le/gui/slOpenGL.h>
#import <le/gui/slCWindow.h>
#import <le/core/auxiliary/slCRunloop.h>
#import <le/core/auxiliary/base/slCRunloopImplMac.hp>
//#import <le/core/slCString.h>
#import "slCCocoaWindowImpl.hp"

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
#import <Cocoa/Cocoa.h>
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#else
#error Target platform not defined
#endif

using namespace sokira::le;

template <typename TPoint>
static inline CPoint2D CocoaPointToCPoint(const TPoint& point)
{
	return CPoint2D(point.x, point.y);
}

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX

static CPoint2D locationInWindowFromNSEvent(NSEvent* event)
{
	NSPoint point = [event locationInWindow];
	NSWindow* window = [event window];
	if (window)
	{
		NSView* contentView = [window contentView];
		point = [contentView convertPointFromBase: point];
		// Invert Y coord
		point.y = [contentView frame].size.height - point.y;
	}
	return CPoint2D(point.x, point.y);
}

static inline CEvent createEventWithNSEvent(NSEvent* event)
{
	CEvent result;
	switch ([event type])
	{
		case NSLeftMouseDown:
			result = CEvent(eEventTypeMouseDown, locationInWindowFromNSEvent(event), eButtonStateDown, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseDown:
			result = CEvent(eEventTypeMouseDown, locationInWindowFromNSEvent(event), eButtonStateDown, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseDown:
			result = CEvent(eEventTypeMouseDown, locationInWindowFromNSEvent(event), eButtonStateDown, eKeyCodeMouseButtonOther);
			break;

		case NSLeftMouseUp:
			result = CEvent(eEventTypeMouseUp, locationInWindowFromNSEvent(event), eButtonStateUp, eKeyCodeMouseButtonPrimary);
			break;

		case NSRightMouseUp:
			result = CEvent(eEventTypeMouseUp, locationInWindowFromNSEvent(event), eButtonStateUp, eKeyCodeMouseButtonSecondary);
			break;

		case NSOtherMouseUp:
			result = CEvent(eEventTypeMouseUp, locationInWindowFromNSEvent(event), eButtonStateUp, eKeyCodeMouseButtonOther);
			break;

		case NSMouseMoved:
		case NSLeftMouseDragged:
		case NSRightMouseDragged:
		case NSOtherMouseDragged:
		case NSMouseEntered:
		case NSMouseExited:
			result = CEvent(eEventTypeMouseMove, locationInWindowFromNSEvent(event), eButtonStateUnknown, eKeyCodeUnknown);
			break;

		case NSKeyDown:
			result = CEvent(eEventTypeKeyDown, CRunLoopImpl::keyCodeFromSystemCode([event keyCode]), eButtonStateDown);
			break;

		case NSKeyUp:
			result = CEvent(eEventTypeKeyUp, CRunLoopImpl::keyCodeFromSystemCode([event keyCode]), eButtonStateUp);
			break;
	}
	return result;
}

@interface SokiraLE_Window : NSWindow
{
	CWindow* leWindow;
}

@property (assign) CWindow* leWindow;

@end

@implementation SokiraLE_Window

@synthesize leWindow;

- (BOOL) canBecomeKeyWindow
{
	return YES;
}

- (void) sendEvent:(NSEvent *)theEvent
{
	[super sendEvent: theEvent];
	CEvent event = createEventWithNSEvent(theEvent);
	leWindow->handleEvent(&event);
}

@end



@interface SokiraLE_OpenGLView : NSOpenGLView
{
	::sokira::le::CWindow* mScreen;
	BOOL mMouseInView;
	BOOL mViewDidResize;
}
@end

static NSOpenGLContext* gOpenGLContext = nil;

@implementation SokiraLE_OpenGLView

- (id) initWithScreen: (::sokira::le::CWindow*) screen
{
	NSOpenGLPixelFormatAttribute attributes [] =
	{
		NSOpenGLPFAWindow,
		NSOpenGLPFADoubleBuffer,	// double buffered
		NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16, // 16 bit depth buffer
		NSOpenGLPFAStencilSize, (NSOpenGLPixelFormatAttribute)8,
		(NSOpenGLPixelFormatAttribute)nil
	};

	NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
	self = [super initWithFrame: NSZeroRect pixelFormat: pixelFormat];

	if (gOpenGLContext)
	{
		NSOpenGLContext* newContext = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: gOpenGLContext];
		[self setOpenGLContext: newContext];
		[newContext setView: self];
		[newContext release];
	}
	else
	{
		gOpenGLContext = [self openGLContext];
	}

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
		std::cout << "ERROR in OpenGL: " << gluErrorString(err) << std::endl;
}

#if 0
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
	NSLog(@"keyUp: %@", theEvent);
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
#endif


- (BOOL) acceptsFirstResponder
{
	return YES;
}

- (void) prepareOpenGL
{
	LE_ASSERT(mScreen);
	mScreen->prepareRenderingContext();
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
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
@interface SokiraLE_OpenGLView : UIWindow
{
	::sokira::le::CWindow* mScreen;
	EAGLContext* context;
	BOOL mMouseInView;
	BOOL mViewDidResize;

	// The pixel dimensions of the CAEAGLLayer.
	GLint framebufferWidth;
	GLint framebufferHeight;

	// The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
	GLuint defaultFramebuffer, colorRenderbuffer;
}
@end

@implementation SokiraLE_OpenGLView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithScreen: (::sokira::le::CWindow*) screen
{
	if (self = [super initWithFrame: [[UIScreen mainScreen] bounds]])
	{
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];

		if (!context)
		{
			context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
		}

		mScreen = screen;
		mMouseInView = NO;
		mViewDidResize = YES;
		[(id)self.layer setDrawableProperties: [NSDictionary dictionaryWithObjectsAndKeys:
												[NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
												kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
												nil]];
		[EAGLContext setCurrentContext: context];
		mScreen->prepareRenderingContext();
	}
	return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [touches anyObject];
	if (touch)
	{
		CGPoint point = [touch locationInView: self];
		LE_ASSERT(mScreen);
		mScreen->onMouse(::sokira::le::eKeyCodeMouseButtonPrimary, ::sokira::le::eButtonStateDown,
			::sokira::le::CPoint2D(point.x, point.y));
	}
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{

}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	UITouch* touch = [touches anyObject];
	if (touch)
	{
		CGPoint point = [touch locationInView: self];
		LE_ASSERT(mScreen);
		mScreen->onMouse(::sokira::le::eKeyCodeMouseButtonPrimary, ::sokira::le::eButtonStateUp,
			::sokira::le::CPoint2D(point.x, point.y));
	}
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{

}

- (void)createFramebuffer
{
	if (context && !defaultFramebuffer)
	{
		[EAGLContext setCurrentContext:context];
		
		// Create default framebuffer object.
		glGenFramebuffers(1, &defaultFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
		
		// Create color render buffer and allocate backing store.
		glGenRenderbuffers(1, &colorRenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
		[context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
		glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
		glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
		
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}
}

- (void) deleteFramebuffer
{
	if (context)
	{
		[EAGLContext setCurrentContext:context];

		if (defaultFramebuffer)
		{
			glDeleteFramebuffers(1, &defaultFramebuffer);
			defaultFramebuffer = 0;
		}

		if (colorRenderbuffer)
		{
			glDeleteRenderbuffers(1, &colorRenderbuffer);
			colorRenderbuffer = 0;
		}
	}
}

- (void) setFramebuffer
{
    if (context)
    {
		[EAGLContext setCurrentContext:context];

		if (!defaultFramebuffer)
			[self createFramebuffer];

		glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);

		glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (void) presentFramebuffer
{
	if (context)
	{
		[EAGLContext setCurrentContext:context];
		glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
		[context presentRenderbuffer:GL_RENDERBUFFER];
	}
}

- (void) drawFrame
{
	[self setFramebuffer];

	if (mViewDidResize)
	{
		mScreen->onResize();
		mViewDidResize = NO;
	}

	mScreen->draw();
	[self presentFramebuffer];
}

- (void) dealloc
{
	[context release];
	[super dealloc];
}

@end
#endif


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
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX

	NSUInteger styleMask = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
	if (mFullScreen)
	{
		styleMask = NSBorderlessWindowMask;
//		frame = [[NSScreen mainScreen] frame];
//		mRect.setX(frame.origin.x);
//		mRect.setY(frame.origin.y);
//		mRect.setWidth(frame.size.width);
//		mRect.setHeight(frame.size.height);
	
		mRect = CRectangle(0, 0, 1024, 768);
	}

	NSRect frame = NSMakeRect(mRect.x(), mRect.y(), mRect.width(), mRect.height());

	mWindow = (void*)[[SokiraLE_Window alloc]
					initWithContentRect: frame
					styleMask: styleMask
					backing: NSBackingStoreBuffered
					defer: YES];

	[(id)mWindow setLeWindow: screen];

	if (mFullScreen)
	{
//		[(id)mWindow setLevel:NSMainMenuWindowLevel+1];
	}

	[(id)mWindow setOpaque: YES];
	

	NSString* title = [NSString stringWithUTF8String: mTitle.UTF8String()];

	[(id)mWindow setTitle: title];
	[(id)mWindow setAcceptsMouseMovedEvents: YES];
	id view = [[SokiraLE_OpenGLView alloc] initWithScreen: screen];
	[[NSNotificationCenter defaultCenter] addObserver:view selector:@selector(parentWindowWillClose:) name:NSWindowWillCloseNotification object: (id) mWindow];
	[(id)mWindow setContentView: view];
//	[(id)mWindow makeFirstResponder: view];
	[view release];
	[(id)mWindow makeKeyAndOrderFront: nil];
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	mWindow = (void*)[[SokiraLE_OpenGLView alloc] initWithScreen: screen];
	[(id)mWindow makeKeyAndVisible];
	CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget: (id) mWindow selector: @selector(drawFrame)];
	[displayLink addToRunLoop: [NSRunLoop currentRunLoop] forMode: NSDefaultRunLoopMode];
#endif
}

void CCocoaWindowImpl::screenWillBeRemovedFromApplication(CWindow* screen, CGuiCocoaApplication* app)
{
	std::cout << "screenWillBeRemovedFromApplication" << std::endl;
	if (mWindow)
	{
		[(id)mWindow release];
	}

	mWindow = NULL;
}

void CCocoaWindowImpl::screenWasRemovedFromApplication(CWindow* screen, CGuiCocoaApplication* app)
{

}

Bool CCocoaWindowImpl::inLiveResize() const
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	return _LE_BOOL_CAST([[(id)mWindow contentView] inLiveResize]);
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	return false;
#endif
}

CSize2D CCocoaWindowImpl::size() const
{
	if (mWindow)
	{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
		NSSize result = [(NSView*)[(id)mWindow contentView] frame].size;
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
		CGSize result = [(id)mWindow frame].size;
#endif
		return CSize2D(result.width, result.height);
	}

	return mRect.size();
}

void CCocoaWindowImpl::setSize(const CSize2D& size)
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	if (mWindow)
	{
		[(id)mWindow setContentSize: NSMakeSize(size.width(), size.height())];
	}
#endif

	mRect.setSize(size);
}

void CCocoaWindowImpl::setNeedsRedraw()
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	[[(id)mWindow contentView] setNeedsDisplay: YES];
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
//	[(id)mWindow setNeedsDisplay];
#endif
}

CString CCocoaWindowImpl::title() const
{
	return mTitle;
}


	} // namespace le
} // namespace sokira
