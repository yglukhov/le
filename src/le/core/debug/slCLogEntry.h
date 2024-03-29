#if !defined SL_LE_core_debug_slCLogEntry_h
#define SL_LE_core_debug_slCLogEntry_h

#include <iostream>
#include <string>
#include <map>
#include <le/core/base/slCBasicString.h>

namespace sokira
{
	namespace le
	{

#if defined __GNUC__
#define LE_PP_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define LE_PP_PRETTY_FUNCTION __FUNCSIG__
#else
#define LE_PP_PRETTY_FUNCTION NULL
#endif


#if LE_FLAG_DEBUG
#define LE_ENABLE_LOG
#endif // LE_FLAG_DEBUG


#ifdef LE_ENABLE_LOG

#define LE_ENTER_LOG ::sokira::le::CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, 1);
#define LE_ENTER_LOG_QUIET ::sokira::le::CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, 2);
#define LE_ENTER_LOG_SILENT ::sokira::le::CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, 3);

#define LE_IF_LOG(x) x

#else // defined LE_ENABLE_LOG

#define LE_ENTER_LOG
#define LE_ENTER_LOG_QUIET
#define LE_ENTER_LOG_SILENT

#define LE_IF_LOG(x)

#endif // not defined LE_ENABLE_LOG

class CLogControl;

////////////////////////////////////////////////////////////////////////////////
// CLogEntry
////////////////////////////////////////////////////////////////////////////////
class CLogEntry : public std::ostream
{
	public:
		CLogEntry(const NChar* func, UInt32 severity, SInt32 mode);
		~CLogEntry();

		inline UInt32 severity() const
		{
			return  mSeverity;
		}

		void enterLog();

	private:
		const NChar* mFunc;
		UInt32 mSeverity;
		SInt32 mMode;
		Bool mEntered;
		CLogControl* mLogControl;
		CLogEntry* mPrevEntry;
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_debug_slCLogEntry_h
