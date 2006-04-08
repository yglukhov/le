#pragma once

#include <iostream>
#include <string>

#if defined __GNUC__
#define LE_PP_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define LE_PP_PRETTY_FUNCTION __FUNCSIG__
#else
#define LE_PP_PRETTY_FUNCTION "_ unknown function name _"
#endif


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
			//if(mQuiet)
			//{
			//	*sLogStream /*<< mFunc */<< ": ";
			//}
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

#define ENTER_LOG _CLog log(LE_PP_PRETTY_FUNCTION, false);
#define ENTER_LOG_QUIET _CLog log(LE_PP_PRETTY_FUNCTION, true);

#define IF_LOG(x) x


#else // defined LOG

#define ENTER_LOG
#define ENTER_LOG_QUIET

#define IF_LOG(x)


#endif // defined LOG
