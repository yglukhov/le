#include <fstream>
#include "slCLogControl.h"
#include <le/core/slCNumber.h>

namespace sokira
{
	namespace le
	{

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

	attachToFile(logFileName, 0);
}

CLogControl::~CLogControl()
{
	for (std::list<std::pair<UInt32, std::ostream*> >::iterator it = mStreams.begin(); it != mStreams.end(); ++it)
	{
		(*it->second) << "\n\n---------------------\nLog ended: [TODO: here must be curent time]\nS.O.K.I.R.A. labs." << std::endl;
		delete it->second;
	}
}

void CLogControl::attachToFile(const CString& name, UInt32 minPriority)
{
	attachToStream(new std::ofstream(name.cString()), minPriority);
}

void CLogControl::attachToScreen(UInt32 minPriority)
{
//	attachToStream(new std::ostream(std::cout), minPriority);
}

void CLogControl::attachToStream(std::ostream* theStream, UInt32 severity)
{
	mStreams.push_back(std::make_pair(severity, theStream));
	*theStream << "S.O.K.I.R.A. labs.\nLog started: [TODO: here must be current time]\n---------------------\n\n" << std::endl;
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
// CLogControl::sync
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
			if (it->first <= mCurrentEntry->severity())
			{
				*(it->second) << mWhiteSpace << mBuffer;
			}
		}
	}

	mBuffer.clear();
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

	} // namespace le
} // namespace sokira
