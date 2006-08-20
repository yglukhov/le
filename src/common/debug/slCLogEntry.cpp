
#include "slCLogEntry.h"
#include "slCLogControl.h"

LE_NAMESPACE_START

//CLogEntry::CLogStreamMap& CLogEntry::streamMap()
//{
//	static CLogStreamMap* map = new CLogStreamMap();
//	return *map;
//}
//
//std::ostream& CLogEntry::defaultStream()
//{
//	return std::clog;
//}
//
//std::string& CLogEntry::whiteSpace()
//{
//	static std::string* str = new std::string();
//	return *str;
//}
//
//std::ostream& CLogEntry::streamForMode()
//{
//	std::ostream* theStream = &defaultStream();
//
//	if(mMode)
//	{
//		CLogStreamMap::iterator it = streamMap().find(mMode);
//		if(it != streamMap().end())
//		{
//			theStream = &(it->second);
//		}
//	}
//
//	return *theStream;
//}

#define LE_LOG_MODE_SILENT 3

CLogEntry::CLogEntry(const char* func, UInt32 severity, SInt32 mode) :
	std::ostream(CLogControl::instance()),
	mFunc(func),
	mSeverity(mode),
	mMode(mode),
	mLogControl(CLogControl::instance()),
	mPrevEntry(mLogControl->currentEntry())
{
	mLogControl->currentEntry(this);

	if(mMode != LE_LOG_MODE_SILENT)
	{
		*this << mFunc << '\n' << '{' << std::endl;
		mLogControl->increaseWhiteSpace();
	}
}

CLogEntry::~CLogEntry()
{
	if(mMode != LE_LOG_MODE_SILENT)
	{
		mLogControl->decreaseWhiteSpace();
		*this << '}' << std::endl;
	}

	mLogControl->currentEntry(mPrevEntry);
}


LE_NAMESPACE_END
