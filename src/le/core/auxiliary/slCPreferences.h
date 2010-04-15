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

class CPreferences
{
	public:
		CPreferences();

		void setValueForKey(const CString& key, SInt64 value);
		void setValueForKey(const CString& key, SInt32 value);
		void setValueForKey(const CString& key, SInt16 value);
		void setValueForKey(const CString& key, SInt8 value);
		void setValueForKey(const CString& key, UInt64 value);
		void setValueForKey(const CString& key, UInt32 value);
		void setValueForKey(const CString& key, UInt16 value);
		void setValueForKey(const CString& key, UInt8 value);
		void setValueForKey(const CString& key, const CString& value);

		SInt64 valueForKey(const CString& key, SInt64 defaultValue) const;
		SInt32 valueForKey(const CString& key, SInt32 defaultValue) const;
		SInt16 valueForKey(const CString& key, SInt16 defaultValue) const;
		SInt8 valueForKey(const CString& key, SInt8 defaultValue) const;
		UInt64 valueForKey(const CString& key, UInt64 defaultValue) const;
		UInt32 valueForKey(const CString& key, UInt32 defaultValue) const;
		UInt16 valueForKey(const CString& key, UInt16 defaultValue) const;
		UInt8 valueForKey(const CString& key, UInt8 defaultValue) const;
		CString valueForKey(const CString& key, const CString& defaultValue) const;

		void flush() const;

	protected:

	private:
		CDictionary mPreferences;
		CURL mPrefsFileURL;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCPreferences_h
