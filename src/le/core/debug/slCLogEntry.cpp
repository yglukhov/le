#include "slCLogEntry.h"
#include "slCLogControl.h"

LE_NAMESPACE_START

#define LE_LOG_MODE_NORMAL 1
#define LE_LOG_MODE_QUIET 2
#define LE_LOG_MODE_SILENT 3

CLogEntry::CLogEntry(const CBasicString& func, UInt32 severity, SInt32 mode) :
	std::ostream(CLogControl::instance()),
	mFunc(func),
	mSeverity(severity),
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