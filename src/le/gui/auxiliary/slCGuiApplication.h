#if !defined SL_LE_gui_auxiliary_slCGuiApplication_h
#define SL_LE_gui_auxiliary_slCGuiApplication_h

#include <vector>
#include <le/core/auxiliary/slCApplication.h>



namespace sokira
{
	namespace le
	{

class CScreen;

class CGuiApplication : public CApplication
{
	public:
		CGuiApplication();
		~CGuiApplication();

		void addScreen(CScreen* screen);

		virtual void quit();

	protected:
		virtual SInt32 runApplication();
		virtual void screenWillBeAddedToApplication(CScreen* screen);
		virtual void screenWasAddedToApplication(CScreen* screen);

	private:
		void* mImpl;
		std::vector<CScreen*> mScreens;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_auxiliary_slCGuiApplication_h
