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
	mEntered(false),
	mLogControl(CLogControl::instance()),
	mPrevEntry(mLogControl->currentEntry())
{
	mLogControl->setCurrentEntry(this);

	if (!mFunc) mFunc = "_ unknown function name _";

	if (mMode == LE_LOG_MODE_NORMAL)
	{
		if (mPrevEntry) mPrevEntry->enterLog();
		mLogControl->mRespectEntries = false;
		*this << mFunc << '\n';
		mLogControl->mRespectEntries = true;
	}
}

void CLogEntry::enterLog()
{
	if (!mEntered)
	{
		mEntered = true;

		if (mPrevEntry) mPrevEntry->enterLog();
		mLogControl->mRespectEntries = false;
		if (mMode != LE_LOG_MODE_SILENT)
		{
			if (mMode == LE_LOG_MODE_QUIET)
			{
				*this << mFunc << '\n';
			}
			*this << '{' << std::endl;
			mLogControl->increaseWhiteSpace();
			flush();
		}

		mLogControl->mRespectEntries = true;
	}
}

CLogEntry::~CLogEntry()
{
	if (mEntered && mMode != LE_LOG_MODE_SILENT)
	{
		mLogControl->mRespectEntries = false;
		mLogControl->decreaseWhiteSpace();
		*this << '}' << std::endl;
		flush();
		mLogControl->mRespectEntries = true;
	}

	mLogControl->setCurrentEntry(mPrevEntry);
}


	} // namespace le
} // namespace sokira
