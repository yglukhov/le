#if !defined SL_LE_core_auxiliary_slCApplication_h
#define SL_LE_core_auxiliary_slCApplication_h

//#include <le/core/slCString.h>
//#include "slCBundle.h"
#include "slCCommandLine.h"
#include "slCPreferences.h"
#include "slCApplicationDelegate.h"

namespace sokira
{
	namespace le
	{

class CPreferences;
class CBundle;

class CApplication : public CObject
/// Basic application implementation. Usually this object is a singletone within
/// a process. This object manages all application related properties, such as
/// command line arguments, application bundle and user preferences.
{
	public:
		CApplication();
		virtual ~CApplication();

		static CApplication* currentApplication();

		int run(int argc, const char * const argv[]);
		virtual void quit();
		virtual Bool canQuit() const;

		CCommandLine commandLine() const;
		CPreferences* preferences();

		void setDelegate(CApplicationDelegate::Ptr delegate);
		bool setDelegateClass(const CString& className);

		CBundle mainBundle() const;

		CApplicationDelegate::Ptr delegate();

	protected:
		virtual SInt32 runApplication();

	private:
		CApplicationDelegate::Ptr mDelegate;
		CCommandLine mCommandLine;
		CPreferences* mPreferences;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCApplication_h
