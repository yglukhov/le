#if !defined SL_LE_core_auxiliary_slCApplication_h
#define SL_LE_core_auxiliary_slCApplication_h

#include <le/core/slCString.h>
#include "slCBundle.h"
#include "slCCommandLine.h"

namespace sokira
{
	namespace le
	{

class CApplicationDelegate;

class CApplication
{
	public:
		CApplication();

		int run(int argc, const char * const argv[]);
		CCommandLine commandLine() const;

		void setDelegate(CApplicationDelegate& delegate);
		bool setDelegateClass(const CString& className);

	protected:
		virtual SInt32 runApplication();
		CApplicationDelegate* delegate();

	private:
		CApplicationDelegate* mDelegate;
		Bool mOwnDelegate;
		CCommandLine mCommandLine;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCApplication_h
