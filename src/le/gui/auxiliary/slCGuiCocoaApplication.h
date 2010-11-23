#if !defined SL_LE_gui_auxiliary_slCGuiCocoaApplication_h
#define SL_LE_gui_auxiliary_slCGuiCocoaApplication_h

#include <le/core/auxiliary/slCApplication.h>


namespace sokira
{
	namespace le
	{

class CScreen;

class CGuiCocoaApplication : public CApplication
{
	public:
		//		void applicationWillFinishLaunching();
		void addScreen(CScreen* screen);

		virtual void quit();

	protected:
		virtual SInt32 runApplication();

	private:
		std::vector<CScreen*> mScreens;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_gui_auxiliary_slCGuiCocoaApplication_h
