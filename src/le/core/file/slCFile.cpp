#include "slCFile.h"
#include "slCFolder.h"
#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

#define SWITCH_MAP1(expr, fromVal, toVal, def) ((expr == fromVal)?(toVal):(def))
#define SWITCH_MAP2(expr, fromVal, toVal, fromVal1, toVal1, def)\
	(SWITCH_MAP1(expr, fromVal, toVal, SWITCH_MAP1(expr, fromVal1, toVal1, def)))

CFile* CFile::createWithPath(const CString& filePath, unsigned openFlags)
{
	CFile* result = new CFile();
	if(result)
	{
		if(result->open(filePath.cString(), openFlags) == eStatusOK)
		{
			return result;
		}
	
		delete result;
	}

	return NULL;
}

EStatus CFile::open(const CString& filePath, unsigned openFlags)
{
	if(openFlags)
	{
		std::ios::openmode mode = ((openFlags & eOpenRead)?(std::ios::in):((std::ios::openmode)0)) |
								((openFlags & eOpenWrite)?(std::ios::out):((std::ios::openmode)0)) |
								((openFlags & eOpenTruncate)?(std::ios::trunc):((std::ios::openmode)0)) |
								((openFlags & eOpenAppend)?(std::ios::app):((std::ios::openmode)0));

		std::fstream::open(filePath.cString(), mode);
	}
	else
	{
		std::fstream::open(filePath.cString());
	}

	return (is_open())?(eStatusOK):(eStatusOpenFailed);
}

EStatus CFile::open(const CFolder& folder, unsigned openFlags)
{
	// TODO: Complete this
	return open(folder.curNodeName(), openFlags);
}

void CFile::close()
{
	std::fstream::close();
}

unsigned CFile::read(void* toBuffer, unsigned length)
{
	return std::fstream::read(static_cast<char*>(toBuffer), length).gcount();
}

std::string CFile::readLine(bool& endOfFile, EStatus*)
{

	// TODO: complete this
	return std::string();
}

unsigned CFile::write(const void* fromBuffer, unsigned length, EStatus* error)
{
	std::fstream::write(static_cast<const char*>(fromBuffer), length);
	if(error)
	{
		*error = eStatusOK;
	}
	return length;
}

unsigned CFile::writeLine(const char* fromString)
{
	LE_ASSERT(false);
	// TODO: complete this
	return 0;
}

void CFile::flush()
{
	std::fstream::flush();
}

void CFile::seekTo(unsigned position, ESeekFrom from)
{
	std::ios::seekdir seekfrom = SWITCH_MAP2(from, eSeekFromBegin, std::ios::beg,
																  eSeekFromEnd,	std::ios::end,
																						std::ios::cur);
	std::fstream::seekg(position, seekfrom);
}

void CFile::seekToEnd()
{
	std::fstream::seekg(0, std::ios::end);
}

void CFile::seekToBegin()
{
	std::fstream::seekg(0, std::ios::beg);
}

bool CFile::lineForward()
{
	return false;
}

bool CFile::lineBackward()
{
	return false;
}

unsigned CFile::size() const
{
	// TODO: complete this
	return 0;
}

	} // namespace le
} // namespace sokira
