#pragma once

#include <common/types/slBasic.h>
#include <iostream>
#include <string>
#include <map>

LE_NAMESPACE_START

#if defined __GNUC__
#define LE_PP_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define LE_PP_PRETTY_FUNCTION __FUNCSIG__
#else
#define LE_PP_PRETTY_FUNCTION "_ unknown function name _"
#endif


#if LE_FLAG_DEBUG
#define LE_ENABLE_LOG
#endif // LE_FLAG_DEBUG


#ifdef LE_ENABLE_LOG

#define LE_ENTER_LOG LE_NESTED_NAMESPACE CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, false);
#define LE_ENTER_LOG_QUIET LE_NESTED_NAMESPACE CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, true);
#define LE_ENTER_LOG_SILENT LE_NESTED_NAMESPACE CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, 3);

#define IF_LOG(x) x


#else // defined LE_ENABLE_LOG

#define LE_ENTER_LOG
#define LE_ENTER_LOG_QUIET
#define LE_ENTER_LOG_SILENT

#define IF_LOG(x)

#endif // not defined LE_ENABLE_LOG

class CLogControl;

////////////////////////////////////////////////////////////////////////////////
// CLogEntry
////////////////////////////////////////////////////////////////////////////////
class CLogEntry : public std::ostream
{
	public:
		CLogEntry(const char* func, UInt32 severity, SInt32 mode);
		~CLogEntry();

		UInt32 severity() const
		{
			return  mSeverity;
		}

	private:
//		typedef std::map<int /* mode */, std::ostream> CLogStreamMap;
//		static CLogStreamMap& streamMap();
//		static std::string& whiteSpace();
//		std::ostream& streamForMode();

		const std::string mFunc;
		UInt32 mSeverity;
		SInt32 mMode;
		CLogControl* mLogControl;
		CLogEntry* mPrevEntry;
};


LE_NAMESPACE_END
