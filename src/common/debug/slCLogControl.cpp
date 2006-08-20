#include "slCLogControl.h"
#include <common/types/slCNumber.h>

LE_NAMESPACE_START

CLogControl::CLogControl() :
	mCurrentEntry(NULL)
{
	static CNumber threadID;
	++threadID;
	CString threadName = CThread::thread().name();
	CString logFileName = LESTR("thread - ") + threadID.valueAsString();
	if (!threadName.isEmpty())
	{
		logFileName += " - " + threadName;
	}

	logFileName += LESTR(".runlog");

//	mLogFile.open(logFileName, eOpenWrite | eOpenTruncate);

	attachToStream(new std::ofstream(logFileName.cString()), 0);
}

CLogControl::~CLogControl()
{
	for (std::list<std::pair<UInt32, std::ostream*> >::iterator it = mStreams.begin(); it != mStreams.end(); ++it)
	{
		delete it->second;
	}
}

void CLogControl::attachToFile(const CString& name, UInt32 minPriority)
{

}

void CLogControl::attachToScreen(UInt32 minPriority)
{

}

void CLogControl::attachToStream(std::ostream* theStream, UInt32 severity)
{
	mStreams.push_back(std::make_pair(severity, theStream));
}

void CLogControl::currentEntry(CLogEntry* entry)
{
	mCurrentEntry = entry;
}

CLogEntry* CLogControl::currentEntry() const
{
	return mCurrentEntry;
}

///////////////////////////////////////////////////////////////////////////
// logstreambuf::sync
//
// Flush our buffer out to the log
//
// RESULT
//		int		EOF if there's an error
///////////////////////////////////////////////////////////////////////////
int CLogControl::sync(void)
{
	if (!mBuffer.empty())
	{
		LE_ASSERT(mCurrentEntry);
		for (std::list<std::pair<UInt32, std::ostream*> >::iterator it = mStreams.begin(); it != mStreams.end(); ++it)
		{
			if (it->first >= mCurrentEntry->severity())
			{
				*(it->second) << mWhiteSpace << mBuffer;
			}
		}
	}

	mBuffer = "";
	return 0;
}

///////////////////////////////////////////////////////////////////////////
// CLogControl::overflow
//
// Add a character to our buffer
//
// INPUTS
//		c			The character to add, or EOF to flush the buffer
//
// RESULT
//		int		EOF if there's an error
///////////////////////////////////////////////////////////////////////////
int CLogControl::overflow(int c)
{
	// Add the character to our buffer. Don't add EOFs.
	if (c != EOF)
		mBuffer += char(c);

	// If it's a newline, flush now. It's technically incorrect to flush on
	// a newline, but we're doing it because that will make LogEntry do the
	// right thing with his prefixes.
	if (c == '\n')
		sync();

	// Return something that's not EOF.
	return 0;
}

LE_NAMESPACE_END
