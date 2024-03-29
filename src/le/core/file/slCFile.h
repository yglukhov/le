#pragma once

#include <le/core/slTypes.h>
#include <fstream>
#include <string>

namespace sokira
{
	namespace le
	{

class CFolder;
class CString;

enum ESeekFrom
{
	eSeekFromBegin = 1,
	eSeekFromEnd,
	eSeekFromCurPos
};

enum EOpenFlags
{
	eOpenRead = LE_SET_BIT(0),
	eOpenWrite = LE_SET_BIT(1),
	eOpenCreate = LE_SET_BIT(2),
	eOpenTruncate = LE_SET_BIT(3),
	eOpenAppend = LE_SET_BIT(4)
};

class CFile : private std::fstream
{
	public:
		static CFile* createWithPath(const CString& filePath, unsigned openFlags = 0);

		EStatus open(const CString& filePath, unsigned openFlags = 0);
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

	} // namespace le
} // namespace sokira
