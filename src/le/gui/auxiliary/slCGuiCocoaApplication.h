#if !defined SL_LE_gui_auxiliary_slCGuiCocoaApplication_h
#define SL_LE_gui_auxiliary_slCGuiCocoaApplication_h

#include <le/core/auxiliary/slCApplication.h>


namespace sokira
{
	namespace le
	{

class CWindow;

class CGuiCocoaApplication : public CApplication
{
	public:
		virtual ~CGuiCocoaApplication();

		//		void applicationWillFinishLaunching();
		void addWindow(CWindow* window);
		void removeWindow(CWindow* window);

		virtual void quit();
		virtual Bool canQuit() const;

	protected:
		virtual SInt32 runApplication();

	private:
		std::vector<CWindow*> mScreens;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_gui_auxiliary_slCGuiCocoaApplication_h
