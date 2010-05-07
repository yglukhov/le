#include "slCURL.h"
#include "slCString.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CURL);

#if LE_TARGET_PLATFORM == LE_PLATFORM_UNIX || LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
static const CString cPathSeparator = LESTR("/");
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
static const CString cPathSeparator = LESTR("/");
#endif

CURL::CURL()
{

}

CURL::CURL(const CString& string) :
	mPath(string)
{

}


CString CURL::hostName() const
{
	return CString();
}

CString CURL::scheme() const
{
	return CString();
}

CString CURL::netLocation() const
{
	return CString();
}

CString CURL::userName() const
{
	return CString();
}

CString CURL::password() const
{
	return CString();
}

CString CURL::path() const
{
	return mPath;
}

CString CURL::extension() const
{
	return CString();
}

CString CURL::lastPathComponent() const
{
	return mPath.subString(mPath.findLast(cPathSeparator) + 1, 0);
}

CString CURL::queryString() const
{
	return CString();
}

SInt32 CURL::portNumber() const
{
	return 0;
}

Bool CURL::operator == (const CURL& url) const
{
	return mPath == url.mPath;
}

void CURL::removeLastPathComponents(UInt32 componentCount)
{
	for (UInt32 i = 0; i < componentCount; ++i)
	{
		SInt32 res = mPath.findLast(cPathSeparator);
		if (res)
			mPath = mPath.subString(0, mPath.findLast(cPathSeparator));
		else
		{
			mPath = CString();
			break;
		}
	}
}

void CURL::removeLastPathComponent()
{
	removeLastPathComponents(1);
}

void CURL::appendPathComponent(const CString& component)
{
	mPath += "/";
	mPath += component;
}

std::ostream& operator << (std::ostream& stream, const CURL& url)
{
	return stream << url.path();
}

	} // namespace le
} // namespace sokira
