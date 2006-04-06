#pragma once

#include <iostream>
#include <string>

#if !defined __GNUC__
#define __PRETTY_FUNCTION__ "_function_unknown_"
#endif // !defined __GNUC__

////////////////////////////////////////////////////////////////////////////////
// ASSERTS
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

#define LOG

class CObject;

void _assert(bool, const char*, unsigned, const char*, const CObject*, const char*);

#  define ASSERT(x) _assert((x), #x, __LINE__, __FILE__, NULL, NULL)
#  define ASSERT_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, NULL, message)

#	define ASSERT_EX(x) _assert((x), #x, __LINE__, __FILE__, this, NULL)
#  define ASSERT_EX_MESSAGE(x, message) _assert((x), #x, __LINE__, __FILE__, this, message)

#else

#define ASSERT(x)
#define ASSERT_MESSAGE(x, message)

#define ASSERT_EX(x)
#define ASSERT_EX_MESSAGE(x, message)

#endif // defined DEBUG


class CFile;

////////////////////////////////////////////////////////////////////////////////
// LOG
////////////////////////////////////////////////////////////////////////////////
class _CLog
{
	public:
		_CLog(const std::string& func, bool quiet);
		~_CLog();

		template <typename T>
		std::ostream& operator << (T obj)
		{
			*sLogStream << sWhiteSpace;
			if(mQuiet)
			{
				*sLogStream << mFunc << ": ";
			}
			return (*sLogStream << obj);
		}

	private:
		const std::string mFunc;
		bool mQuiet;

		static std::ostream* sLogStream;
		static CFile* sLogFile;
		static std::string sWhiteSpace;
};

#ifdef LOG

#define ENTER_LOG _CLog log(__PRETTY_FUNCTION__, false);
#define ENTER_LOG_QUIET _CLog log(__PRETTY_FUNCTION__, true);

#define IF_LOG(x) x


#else // defined LOG

#define ENTER_LOG
#define ENTER_LOG_QUIET

#define IF_LOG(x)


#endif // defined LOG
