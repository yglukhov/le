
#include "slCLogEntry.h"

LE_NAMESPACE_START

CLogEntry::CLogStreamMap& CLogEntry::streamMap()
{
	static CLogStreamMap* map = new CLogStreamMap();
	return *map;
}

std::ostream& CLogEntry::defaultStream()
{
	return std::clog;
}

std::string& CLogEntry::whiteSpace()
{
	static std::string* str = new std::string();
	return *str;
}

std::ostream& CLogEntry::streamForMode()
{
	std::ostream* theStream = &defaultStream();

	if(mMode)
	{
		CLogStreamMap::iterator it = streamMap().find(mMode);
		if(it != streamMap().end())
		{
			theStream = &(it->second);
		}
	}

	return *theStream;
}

CLogEntry::CLogEntry(const char* func, int mode, bool quiet) :
	mFunc(func), mMode(mode), mQuiet(quiet)
{

	if(!mQuiet)
	{
		streamForMode() << whiteSpace() << mFunc << '\n' << whiteSpace() << '{' << std::endl;
		whiteSpace().push_back('\t');
	}
}

CLogEntry::~CLogEntry()
{
	if(!mQuiet)
	{
		whiteSpace().erase(0, 1);
		streamForMode() << whiteSpace() << '}' << std::endl;
	}
}


LE_NAMESPACE_END
