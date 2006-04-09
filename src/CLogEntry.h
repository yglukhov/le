#pragma once

#include <iostream>
#include <map>

#ifdef LOG

#define ENTER_LOG CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, false);
#define ENTER_LOG_QUIET CLogEntry log(LE_PP_PRETTY_FUNCTION, 0, true);

#define IF_LOG(x) x


#else // defined LOG

#define ENTER_LOG
#define ENTER_LOG_QUIET

#define IF_LOG(x)


#endif // defined LOG


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
