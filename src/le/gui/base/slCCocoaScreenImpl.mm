#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <le/gui/slCScreen.h>
//#import <le/core/slCString.h>
#import "slCCocoaScreenImpl.hp"

@interface SokiraLE_OpenGLView : NSOpenGLView
{
	::sokira::le::CScreen* mScreen;
	BOOL mMouseInView;
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
	return self;
}

- (void) drawRect: (NSRect) bounds
{
	LE_ASSERT(mScreen);

	mScreen->draw();
	if ([self inLiveResize])
		glFlush();
	else
		[[self openGLContext] flushBuffer];
//[[self openGLContext] 
	GLenum err = glGetError();
	if (GL_NO_ERROR != err)
		std::cout << gluErrorString (err) << std::endl;
}

- (void)keyDown:(NSEvent *)theEvent
{
	NSString* chars = [theEvent charactersIgnoringModifiers];
	const char * str = [chars cStringUsingEncoding: NSNonLossyASCIIStringEncoding];
	::sokira::le::CString characters = (str)?(str):(::sokira::le::CString());
	mScreen->onKeyDown(characters, ::sokira::le::eCharacterModifierNone);
}

- (void)keyUp:(NSEvent *)theEvent
{
	NSString* chars = [theEvent charactersIgnoringModifiers];
	const char * str = [chars cStringUsingEncoding: NSNonLossyASCIIStringEncoding];
	::sokira::le::CString characters = (str)?(str):(::sokira::le::CString());
	mScreen->onKeyUp(characters, ::sokira::le::eCharacterModifierNone);
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
			mScreen->onMouseOut(::sokira::le::CPoint(point.x, point.y));
		}
	}
	else
	{
		LE_ASSERT(mScreen);

		if (!mMouseInView)
		{
			mMouseInView = YES;
			mScreen->onMouseIn(::sokira::le::CPoint(point.x, point.y));
		}

		// On Mouse Hover
		mScreen->onMouse(::sokira::le::eMouseButtonUnknown, ::sokira::le::eButtonStateUnknown,
			::sokira::le::CPoint(point.x, point.y));

//		mScreen->onMouseHover(::sokira::le::CPoint(point.x, point.y));
	}
}

- (void) anyMouseDown: (NSEvent*) event button: (::sokira::le::EMouseButton) button
{
	NSPoint point = [event locationInWindow];

	// Invert Y coord
	point.y = [self frame].size.height - point.y;

	LE_ASSERT(mScreen);
	mScreen->onMouse(button, ::sokira::le::eButtonStateDown,
			::sokira::le::CPoint(point.x, point.y));
//
//	mScreen->onMouseDown(button, ::sokira::le::CPoint(point.x, point.y));
}

- (void) anyMouseUp: (NSEvent*) event button: (::sokira::le::EMouseButton) button
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
			::sokira::le::CPoint(point.x, point.y));
//	mScreen->onMouseUp(button, ::sokira::le::CPoint(point.x, point.y));
}

- (void) mouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eMouseButtonLeft];
}

- (void) mouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eMouseButtonLeft];
}

- (void)mouseDragged:(NSEvent *)event
{
	[self mouseMoved:event];
}

- (void) rightMouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eMouseButtonRight];
}

- (void) rightMouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eMouseButtonRight];
}

- (void) rightMouseDragged: (NSEvent*) event
{
	[self mouseMoved:event];
}

- (void) otherMouseDown: (NSEvent*) event
{
	[self anyMouseDown: event button: ::sokira::le::eMouseButtonMiddle];
}

- (void) otherMouseUp: (NSEvent*) event
{
	[self anyMouseUp: event button: ::sokira::le::eMouseButtonMiddle];
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
//	long swapInt = 1;

//	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; // set to vbl sync

	// init GL stuff here
//	glEnable(GL_DEPTH_TEST);

//	glShadeModel(GL_SMOOTH);    
//	glEnable(GL_CULL_FACE);
//	glFrontFace(GL_CCW);
//	glPolygonOffset (1.0f, 1.0f);

//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	[self resetCamera];
//	shapeSize = 7.0f; // max radius of of objects

	// init fonts for use with strings
//	NSFont * font =[NSFont fontWithName:@"Helvetica" size:12.0];
//	stanStringAttrib = [[NSMutableDictionary dictionary] retain];
//	[stanStringAttrib setObject:font forKey:NSFontAttributeName];
//	[stanStringAttrib setObject:[NSColor whiteColor] forKey:NSForegroundColorAttributeName];
//	[font release];
	
	// ensure strings are created
//	[self createHelpString];
//	[self createMessageString];

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
	LE_ASSERT(mScreen);
	mScreen->_screenWasResized();
}

- (void)viewDidEndLiveResize
{
	LE_ASSERT(mScreen);
	mScreen->_screenWasResized();
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

	mWindow = [[NSWindow alloc]
					initWithContentRect: frame
					styleMask: NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
					backing: NSBackingStoreBuffered
					defer: NO];

	[static_cast<NSWindow*>(mWindow) setTitle:@"Universe"];
	[static_cast<NSWindow*>(mWindow) setAcceptsMouseMovedEvents: YES];
	NSView* view = [[[SokiraLE_OpenGLView alloc] initWithFrame:frame andScreen: screen] autorelease];
	[static_cast<NSWindow*>(mWindow) setContentView: view];
	[static_cast<NSWindow*>(mWindow) makeKeyAndOrderFront: nil];
}

void CCocoaScreenImpl::screenWillBeRemovedFromApplication(CScreen* screen, CGuiApplication* app)
{
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

CSize CCocoaScreenImpl::size() const
{
	id view = [static_cast<NSWindow*>(mWindow) contentView];
	if (view)
	{
		NSRect rect = [view frame];
		return CSize(rect.size.width, rect.size.height);
	}
	return mRect.size();
}

void CCocoaScreenImpl::setSize(const CSize& Size)
{
	if (mWindow)
	{
		[static_cast<NSWindow*>(mWindow) setContentSize:NSMakeSize(Size.width(), Size.height())];
	}

	mRect.size(Size);
}

void CCocoaScreenImpl::setNeedsRedraw()
{
	[[static_cast<NSWindow*>(mWindow) contentView] setNeedsDisplay:YES];
}

	} // namespace le
} // namespace sokira
