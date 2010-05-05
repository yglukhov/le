#if !defined SL_LE_core_auxiliary_slCPreferences_h
#define SL_LE_core_auxiliary_slCPreferences_h

//#include <le/core/slCString.h>
#include <le/core/slCDictionary.h>
#include <le/core/slCURL.h>
//#include "slCBundle.h"
//#include "slCCommandLine.h"

namespace sokira
{
	namespace le
	{

class CPreferences : public CDictionary
{
	public:
		CPreferences(const CString& domain);
		~CPreferences();
		void flush() const;

	private:
		const NChar* filePath() const;
		CString mDomain;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCPreferences_h
