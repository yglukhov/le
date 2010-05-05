#if !defined SL_LE_core_auxiliary_slCApplication_h
#define SL_LE_core_auxiliary_slCApplication_h

//#include <le/core/slCString.h>
//#include "slCBundle.h"
#include "slCCommandLine.h"
#include "slCPreferences.h"

namespace sokira
{
	namespace le
	{

class CApplicationDelegate;
class CBundle;

class CApplication
/// Basic application implementation. Usually this object is a singletone within
/// a process. This object manages all application related properties, such as
/// command line arguments, application bundle and user preferences.
{
	public:
		CApplication();
		virtual ~CApplication();

		int run(int argc, const char * const argv[]);
		virtual void quit();

		CCommandLine commandLine() const;
		CPreferences* preferences();

		void setDelegate(CApplicationDelegate& delegate);
		bool setDelegateClass(const CString& className);

		CBundle mainBundle() const;

	protected:
		virtual SInt32 runApplication();
		CApplicationDelegate* delegate();

	private:
		CApplicationDelegate* mDelegate;
		Bool mOwnDelegate;
		CCommandLine mCommandLine;
		CPreferences mPreferences;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCApplication_h
