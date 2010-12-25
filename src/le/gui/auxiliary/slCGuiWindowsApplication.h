#if !defined SL_LE_gui_auxiliary_slCGuiWindowsApplication_h
#define SL_LE_gui_auxiliary_slCGuiWindowsApplication_h

#include <le/core/auxiliary/slCApplication.h>

namespace sokira
{
	namespace le
	{

class CWindow;

class CGuiWindowsApplication : public CApplication
{
	public:
		void addScreen(CWindow* screen);
		virtual void quit();

	protected:
		virtual SInt32 runApplication();

	private:
		std::vector<CWindow*> mScreens;
};
		
	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_gui_auxiliary_slCGuiWindowsApplication_h
