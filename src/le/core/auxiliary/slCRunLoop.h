#pragma once

#include <list>
#include <le/core/slTypes.h>
#include <le/core/thread/slCMutex.h>
#include <le/core/template/function/slTCFunction.h>

namespace sokira
{
	namespace le
	{

class CRunLoopSource;
class CRunLoopImpl;
class CEvent;
class CRunLoop;

/*! Another enum, with inline docs */
enum EEventMask
{
	eEventMaskMouse, /*!< value 1 */
	eEventMaskKeyboard /*!< value 2 */
};

class CRunLoop
/// Event handling core. The CRunLoop class declares the programmatic interface
/// to objects that manage input sources. A CRunLoop object processes input for
/// sources such as mouse and keyboard events from the window system, sockets,
/// timers, and other objects.
{
	public:
		/// Start the run loop.
		void run();

		/// Stop the run loop.
		void stop();

		/// Is the run loop stopped.
		bool isStopped() const;

		/// Get next event. Can be used in a loop.
		/// @param mask some param
		CEvent nextEventMatchingMask(EEventMask mask);

	private:
		friend class CThread;
		CRunLoop();
		CMutex mQueueMutex;
		bool mStopped;
		CRunLoopImpl* mImpl;
};

	} // namespace le
} // namespace sokira
