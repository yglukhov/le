#pragma once

#include <common/types/slCString.h>
#include <file/slCFile.h>
#include <streambuf>

LE_NAMESPACE_START

class CLogControl : public std::basic_streambuf<Char>
{
	public:
		CLogControl(const CString& threadName);
		void attachToFile(const CString& name, UInt32 minPriority);
		void attachToScreen(UInt32 minPriority);
	private:
		CFile mLogFile;
};

LE_NAMESPACE_END
