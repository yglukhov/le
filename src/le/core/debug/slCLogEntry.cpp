#include "slCLogEntry.h"
#include "slCLogControl.h"

namespace sokira
{
	namespace le
	{

#define LE_LOG_MODE_NORMAL 1
#define LE_LOG_MODE_QUIET 2
#define LE_LOG_MODE_SILENT 3

CLogEntry::CLogEntry(const NChar* func, UInt32 severity, SInt32 mode) :
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


	} // namespace le
} // namespace sokira
