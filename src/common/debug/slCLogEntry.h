#pragma once

#include <common/config/slPrefix.h>
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


#ifdef LE_DEBUG
#define LE_ENABLE_LOG
#endif // defined LE_DEBUG


#ifdef LE_ENABLE_LOG

#define LE_ENTER_LOG LE_NESTED_NAMESPACE CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, false);
#define LE_ENTER_LOG_QUIET LE_NESTED_NAMESPACE CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, true);
#define LE_ENTER_LOG_SILENT LE_NESTED_NAMESPACE CLogEntry log("", 0, true);

#define IF_LOG(x) x


#else // defined LE_ENABLE_LOG

#define LE_ENTER_LOG
#define LE_ENTER_LOG_QUIET
#define LE_ENTER_LOG_SILENT

#define IF_LOG(x)

#endif // not defined LE_ENABLE_LOG


////////////////////////////////////////////////////////////////////////////////
// CLogEntry
////////////////////////////////////////////////////////////////////////////////
class CLogEntry
{
	public:
		CLogEntry(const char* func, int mode, bool quiet);
		~CLogEntry();

		template <typename T>
		std::ostream& operator << (T obj)
		{
			std::ostream& theStream = streamForMode();

			theStream << whiteSpace();
			if(mQuiet)
			{
				theStream << mFunc << ": ";
			}

			return (theStream << obj);
		}

		static std::ostream& defaultStream();

	private:
		typedef std::map<int /* mode */, std::ostream> CLogStreamMap;
		static CLogStreamMap& streamMap();
		static std::string& whiteSpace();
		std::ostream& streamForMode();

		const std::string mFunc;
		int mMode;
		bool mQuiet;
};


LE_NAMESPACE_END
