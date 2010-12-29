#include "slCCommandLine.h"
#include <le/core/slCString.h>


namespace sokira
{
	namespace le
	{

CCommandLine::CCommandLine() :
	mCount(0),
	mArgs(NULL)
{

}

CCommandLine::CCommandLine(int argc, const char * const argv[])
{
	setArguments(argc, argv);
}

void CCommandLine::setArguments(int argc, const char * const argv[])
{
	mCount = argc;
	mArgs = argv;
	if (!mArgs) mCount = 0;
	if (!mCount) mArgs = NULL;
}

UInt32 CCommandLine::argumentCount() const
{
	return mCount;
}

CString CCommandLine::argumentAtIndex(UInt32 index) const
{
	if (index < mCount)
		return CString(mArgs[index]);
	return CString();
}

CString CCommandLine::executableName() const
{
	return argumentAtIndex(0);
}

const char * const * CCommandLine::argv() const
{
	return mArgs;
}

	} // namespace le
} // namespace sokira
