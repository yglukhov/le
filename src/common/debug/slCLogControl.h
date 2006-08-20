#pragma once

#include <streambuf>
#include <list>

#include <common/types/slCString.h>
#include <file/slCFile.h>
#include <thread/slTCThreadSingletone.h>

LE_NAMESPACE_START

class CLogEntry;

class CLogControl :
	public std::streambuf,
	public TCThreadSingletone<CLogControl>
{
	public:
		CLogControl();
		~CLogControl();

		void attachToFile(const CString& name, UInt32 minPriority);
		void attachToScreen(UInt32 minPriority);

		void currentEntry(CLogEntry* entry);
		CLogEntry* currentEntry() const;

		void attachToStream(std::ostream* theStream, UInt32 severity);

		void increaseWhiteSpace()
		{
			mWhiteSpace += '\t';
		}

		void decreaseWhiteSpace()
		{
			mWhiteSpace.erase(0, 1);
		}

	protected:
		virtual int sync();
		virtual int overflow(int c = EOF);

	private:
		CFile mLogFile;
		CLogEntry* mCurrentEntry;
		std::list<std::pair<UInt32, std::ostream*> > mStreams;
		std::string mWhiteSpace;
		std::string mBuffer;
};

LE_NAMESPACE_END
