#if !defined SL_LE_core_auxiliary_slCApplicationDelegate_h
#define SL_LE_core_auxiliary_slCApplicationDelegate_h

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CApplication;

class CApplicationDelegate : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CApplicationDelegate)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CApplicationDelegate();
		CApplication* application();

		virtual void applicationWillFinishLaunching(CApplication& application);
		virtual void applicationDidFinishLaunching(CApplication& application);
		virtual Bool applicationShouldTerminateAfterLastWindowClosed(CApplication& application);

	// private:
		void _setApplication(CApplication* application);

	private:
		CApplication* mApplication;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCApplicationDelegate_h
