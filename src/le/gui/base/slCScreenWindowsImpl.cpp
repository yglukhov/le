#include <le/gui/slCScreen.h>
#include "slCScreenWindowsImpl.hp"


namespace sokira
{
	namespace le
	{

static UInt32 windowClassRefCount = 0;

CScreenWindowsImpl::CScreenWindowsImpl(bool fullScreen, const CString& title, const CRectangle& rect) :
	mFullScreen(fullScreen),
	mTitle(title),
	mRect(rect),
	mWindow(NULL),
	mWindowDidResize(true),
	mMouseInWindow(false)
{

}

void CScreenWindowsImpl::screenWillBeAddedToApplication(CScreen* screen, CGuiApplication* app)
{

}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScreenWindowsImpl* impl = (CScreenWindowsImpl*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (impl)
	{
		return impl->wndProc(uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CScreenWindowsImpl::wndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	union KeyParam
	{
		LPARAM param;
		struct
		{
			UInt32 repeatCount : 16;
			UInt32 scanCode : 8;
			UInt32 extended : 1;
			UInt32 reserved : 4;
			UInt32 contextCode : 1;
			UInt32 previousDown : 1;
			UInt32 transitionState: 1;
		};
	};

	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
			std::cout << "ACTIVATE" << std::endl;
			return 0;								// Return To The Message Loop

		case WM_SYSCOMMAND:							// Intercept System Commands
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit

		case WM_CLOSE:								// Did We Receive A Close Message?
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back

		case WM_PAINT:
			if (mWindowDidResize)
			{
				mScreen->onResize();
				mWindowDidResize = false;
			}

			mScreen->draw();
			SwapBuffers(GetDC(mWindow));
			return 0;

		case WM_KEYDOWN:
		{
			KeyParam param;
			param.param = lParam;
			if (!param.previousDown)
			{
				if (!param.extended)
				{
					char chars[2];
					chars[0] = (char)wParam;
					chars[1] = 0;
					CString characters(chars);
					mScreen->onKeyDown(characters, eCharacterModifierNone);
				}
			}
			return 0;
		}

		case WM_KEYUP:
		{
			KeyParam param;
			param.param = lParam;
			if (!param.extended)
			{
				char chars[2];
				chars[0] = (char)wParam;
				chars[1] = 0;
				CString characters(chars);
				mScreen->onKeyUp(characters, eCharacterModifierNone);
			}
			return 0;
		}

		case WM_LBUTTONDOWN:
			onMouseButton(eMouseButtonLeft, eButtonStateDown, lParam);
			return 0;
		case WM_LBUTTONUP:
			onMouseButton(eMouseButtonLeft, eButtonStateUp, lParam);
			return 0;
		case WM_RBUTTONDOWN:
			onMouseButton(eMouseButtonRight, eButtonStateDown, lParam);
			return 0;
		case WM_RBUTTONUP:
			onMouseButton(eMouseButtonRight, eButtonStateUp, lParam);
			return 0;
		case WM_MBUTTONDOWN:
			onMouseButton(eMouseButtonMiddle, eButtonStateDown, lParam);
			return 0;
		case WM_MBUTTONUP:
			onMouseButton(eMouseButtonMiddle, eButtonStateUp, lParam);
			return 0;

		case WM_MOUSEMOVE:
			if (!mMouseInWindow)
			{
				TRACKMOUSEEVENT eventTrack;
				eventTrack.cbSize = sizeof(eventTrack);
				eventTrack.dwFlags = TME_LEAVE;
				eventTrack.dwHoverTime = HOVER_DEFAULT;
				eventTrack.hwndTrack = mWindow;
				TrackMouseEvent(&eventTrack);
				mMouseInWindow = true;
				POINTS point = MAKEPOINTS(lParam);
				mScreen->onMouseIn(CPoint2D(point.x, point.y));
			}
			else
			{
				onMouseButton(eMouseButtonUnknown, eButtonStateUnknown, lParam);
			}
			return 0;

		case WM_MOUSELEAVE:
			if (mMouseInWindow)
			{
				mMouseInWindow = false;
				POINTS point = MAKEPOINTS(lParam);
				mScreen->onMouseOut(CPoint2D(point.x, point.y));
			}
			return 0;

		case WM_SIZE:
			mWindowDidResize = true;
			return 0;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(mWindow, uMsg, wParam, lParam);
}

void CScreenWindowsImpl::onMouseButton(EMouseButton button, EButtonState state, LPARAM coords)
{
	POINTS point = MAKEPOINTS(coords);
	mScreen->onMouse(button, state, CPoint2D(point.x, point.y));
}

void CScreenWindowsImpl::screenWasAddedToApplication(CScreen* screen, CGuiApplication* app)
{
	mScreen = screen;

	std::cout << "hi " << std::endl;

	HINSTANCE inst = GetModuleHandle(NULL);
	if (windowClassRefCount == 0)
	{
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
		wc.cbClsExtra		= 0;									// No Extra Window Data
		wc.cbWndExtra		= 0;									// No Extra Window Data
		wc.hInstance		= inst;									// Set The Instance
		wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
		wc.hbrBackground	= NULL;									// No Background Required For GL
		wc.lpszMenuName		= NULL;									// We Don't Want A Menu
		wc.lpszClassName	= "le_window";							// Set The Class Name

		if (!RegisterClass(&wc))
		{
			std::cout << "ERROR: Could not register window class: " << GetLastError() << std::endl;
		}
		else
		{
			std::cout << "WND CLASS REGISTERED" << std::endl;
		}
	}

	++windowClassRefCount;

	mWindow = CreateWindow(
		"le_window",
		mTitle.cString(),
		WS_THICKFRAME | WS_SYSMENU,
		0, 0, 200, 200,
		NULL,
		NULL,
		inst,
		NULL);

	if (!mWindow)
	{
		std::cout << "success!" << std::endl;
	}
	else
		std::cout << "error: " << GetLastError() << std::endl;

	// Adjust client rect to mRect
	RECT newRect;
	GetClientRect(mWindow, &newRect);
	POINT point = { 0, 0 };
	ClientToScreen(mWindow, &point);
	newRect.left = (LONG)mRect.x() - newRect.left - point.x;
	newRect.top = (LONG)mRect.y() - newRect.top - point.y;
	newRect.right = 200 - newRect.right + (LONG)mRect.width();
	newRect.bottom = 200 - newRect.bottom + (LONG)mRect.height();
	MoveWindow(mWindow, newRect.left, newRect.top, newRect.right, newRect.bottom, FALSE);

	SetWindowLongPtr(mWindow, GWLP_USERDATA, (LONG_PTR)this);

	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};


	bool result = false;
	HDC hdc = GetDC(mWindow);
	if (hdc)
	{
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		if (pixelFormat)
		{
			if (SetPixelFormat(hdc, pixelFormat, &pfd))
			{
				std::cout << "preparing opengl" << std::endl;

				HGLRC hRC = wglCreateContext(hdc);
				if (hRC)
				{
					wglMakeCurrent(hdc, hRC);
					mScreen->_prepareOpenGL();
					ShowWindow(mWindow, SW_SHOW);
					UpdateWindow(mWindow);
					result = true;
				}
			}
		}
	}

	if (!result)
	{
		std::cout << "Could not set pixel format" << std::endl;
	}
}

void CScreenWindowsImpl::screenWillBeRemovedFromApplication(CScreen* screen, CGuiApplication* app)
{
	DestroyWindow(mWindow);
	mWindow = NULL;

	--windowClassRefCount;
	if (!windowClassRefCount)
	{
		UnregisterClass("le_window", NULL);
	}
}

void CScreenWindowsImpl::screenWasRemovedFromApplication(CScreen* screen, CGuiApplication* app)
{

}

Bool CScreenWindowsImpl::inLiveResize() const
{
	return mWindowDidResize;
}

CSize2D CScreenWindowsImpl::size() const
{
	if (mWindow)
	{
		RECT rect;
		GetClientRect(mWindow, &rect);
		return CSize2D((Float32)rect.right, (Float32)rect.bottom);
	}

	return mRect.size();
}

void CScreenWindowsImpl::setSize(const CSize2D& size)
{
	if (mWindow)
	{
		// TODO: recalculate window size according to client size
	}

	mRect.setSize(size);
}

void CScreenWindowsImpl::setNeedsRedraw()
{
	InvalidateRect(mWindow, NULL, FALSE);
}

CString CScreenWindowsImpl::title() const
{
	return mTitle;
}

	} // namespace le
} // namespace sokira