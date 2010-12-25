#include <CoreFoundation/CoreFoundation.h>
#include <le/gui/slCWindow.h>
#include <le/core/auxiliary/slCRunLoop.h>
#include <le/core/thread/slCThread.h>
#include "slCX11WindowImpl.hp"

namespace sokira
{
	namespace le
	{

CWindow* __sokira_le_X11WindowCreateWithNative(Window* window, Display* display)
{
	return NULL;
}

CX11WindowImpl::CX11WindowImpl(bool fullScreen, const CString& title, const CRectangle& rect) :
	mFullScreen(fullScreen),
	mTitle(title),
	mRect(rect),
	mWindowDidResize(true),
	mMouseInWindow(false),
	mWindow(NULL),
	mDisplay(NULL)
{

}

void CX11WindowImpl::screenWillBeAddedToApplication(CWindow* screen, CGuiApplication* app)
{
	
}

CEvent CX11WindowImpl::eventWithXEvent(XEvent* xEvent)
{
	return CEvent();
}

void CX11WindowImpl::onSocket()
{
	XEvent event;
	XNextEvent(mDisplay, &event);
//	CThread::thread().runLoop().postEvent(eventWithXEvent(&event));

	switch (event.type)
	{
		case Expose :
			if (event.xexpose.count)
				break;
			
			mScreen->draw();
			break;

		case KeyPress :
			printf("KeyPress\n");
			//		running = false;
			break;
			
		case ConfigureNotify:
			break;
			
		case ButtonPress:
			break;
			
		case MotionNotify:
			break;
		case ClientMessage:
			printf("ClientMessage\n");
			//					running = false;
			break;
		default:
			printf("enent: %d\n", event.type);
	}
}

static void socketCallback(CFSocketRef s, CFSocketCallBackType callbackType, CFDataRef address, const void *data, void *info)
{
	((CX11WindowImpl*)data)->onSocket();
}

void CX11WindowImpl::screenWasAddedToApplication(CWindow* screen, CGuiApplication* app)
{
	mScreen = screen;

	if (!mWindow)
	{
		LE_ASSERT(false);
		// Create window
	}

	int socket = ConnectionNumber(mDisplay);
	CFSocketContext context;
	context.version = 0;
	context.info = this;
	context.retain = NULL;
	context.release = NULL;
	context.copyDescription = NULL;
	CFSocketRef cfSock = CFSocketCreateWithNative(kCFAllocatorDefault, socket, kCFSocketReadCallBack, socketCallback, &context);
	CFRunLoopSourceRef source = CFSocketCreateRunLoopSource(kCFAllocatorDefault, cfSock, 3);
	CFRunLoopAddSource(CFRunLoopGetMain(), source, kCFRunLoopDefaultMode);

	
	// Create window and add it to runloop
}

void CX11WindowImpl::screenWillBeRemovedFromApplication(CWindow* screen, CGuiApplication* app)
{
	// Remove window
}

void CX11WindowImpl::screenWasRemovedFromApplication(CWindow* screen, CGuiApplication* app)
{
	
}

Bool CX11WindowImpl::inLiveResize() const
{
	return mWindowDidResize;
}

CSize2D CX11WindowImpl::size() const
{

	
	return mRect.size();
}

void CX11WindowImpl::setSize(const CSize2D& size)
{
	// resize X11
	
	mRect.setSize(size);
}

void CX11WindowImpl::setNeedsRedraw()
{
//	InvalidateRect(mWindow, NULL, FALSE);
}

CString CX11WindowImpl::title() const
{
	return mTitle;
}
		
	} // namespace le
} // namespace sokira
