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

	logFileName += LESTR(".log");

	attachToFile(logFileName, 0);
}

CLogControl::~CLogControl()
{
	for (std::list<CStreamTuple>::iterator it = mStreams.begin(); it != mStreams.end(); ++it)
	{
		*(it->value<1>()) << "\n\n---------------------\nLog ended: [TODO: here must be curent time]\nS.O.K.I.R.A. labs." << std::endl;
		if (it->value<2>())
		{
			delete it->value<1>();
		}
	}
}

void CLogControl::attachToFile(const CString& name, UInt32 minPriority)
{
	attachToStream(new std::ofstream(name.cString()), minPriority);
}

void CLogControl::attachToStandardOutput(UInt32 minPriority)
{
	attachToStream(&std::cout, minPriority, false);
}

void CLogControl::attachToStream(std::ostream* theStream, UInt32 severity, bool deleteOnEnd)
{
	CStreamTuple t;
	t.setValue<0>(severity);
	t.setValue<1>(theStream);
	t.setValue<2>(deleteOnEnd);
	mStreams.push_back(t);
	*theStream << "S.O.K.I.R.A. labs.\nLog started: [TODO: here must be current time]\n---------------------\n\n" << std::endl;
}

void CLogControl::setCurrentEntry(CLogEntry* entry)
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
int CLogControl::sync()
{
	if (!mBuffer.empty())
	{
		LE_ASSERT(mCurrentEntry);
		for (std::list<CStreamTuple>::iterator it = mStreams.begin(); it != mStreams.end(); ++it)
		{
			if (it->value<0>() <= mCurrentEntry->severity())
			{
				*(it->value<1>()) << mWhiteSpace << mBuffer;
				it->value<1>()->flush();
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
	if (mRespectEntries)
	{
		LE_ASSERT(mCurrentEntry);
		mCurrentEntry->enterLog();
	}

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
