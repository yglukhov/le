#if !defined SL_LE_TEST_general_slCGuiTestAppDelegate_h
#define SL_LE_TEST_general_slCGuiTestAppDelegate_h

#include <le/core/auxiliary/slCApplicationDelegate.h>

namespace sokira
{
	namespace le
	{
		
		class CGuiTestAppDelegate : public le::CApplicationDelegate
		{
			LE_RTTI_BEGIN
			LE_RTTI_SELF(CGuiTestAppDelegate)
			LE_RTTI_SINGLE_PUBLIC_PARENT
			LE_RTTI_END
			
		public:
			virtual void applicationDidFinishLaunching(le::CApplication& application);
			virtual le::Bool applicationShouldTerminateAfterLastWindowClosed(le::CApplication& application);
		};
		
	}
}

#endif // not defined SL_LE_TEST_general_slCGuiTestAppDelegate_h
