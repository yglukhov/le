#pragma once

#include <fstream>
#include <string>
#include "Constants.h"

class CFolder;

enum ESeekFrom
{
	eSeekFromBegin = 1,
	eSeekFromEnd,
	eSeekFromCurPos
};

enum EOpenFlags
{
	eOpenRead = SET_BIT(0),
	eOpenWrite = SET_BIT(1),
	eOpenCreate = SET_BIT(2),
	eOpenTruncate = SET_BIT(3),
	eOpenAppend = SET_BIT(4)
};

class CFile : private std::fstream
{
	public:
		static CFile* createWithPath(const char* filePath, unsigned openFlags = 0);

		EStatus open(const char* filePath, unsigned openFlags = 0);
		EStatus open(const CFolder& folder, unsigned openFlags = 0);
		void close();

		unsigned read(void* toBuffer, unsigned length);
		std::string readLine(bool& endOfFile, EStatus* = NULL);

		unsigned write(const void* fromBuffer, unsigned length, EStatus* = NULL);
		unsigned writeLine(const char* fromString);

		void flush();

		void seekTo(unsigned position, ESeekFrom from = eSeekFromCurPos);
		void seekToEnd();
		void seekToBegin();

		bool lineForward();
		bool lineBackward();

		unsigned size() const;

		template<typename T>
		std::istream& operator >> (T& obj)
		{
			return (static_cast<std::istream&>(*this) >> obj);
		}

		template<typename T>
		std::ostream& operator << (const T& obj)
		{
			return (static_cast<std::ostream&>(*this) << obj);
		}
};

