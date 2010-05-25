#include "slCURL.h"
#include "slCString.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CURL);

CURL::CURL()
{

}

CURL::CURL(const CString& string) :
	mPath(string)
{
	char char1 = (char)string.characterAtIndex(1);
	char char2 = (char)string.characterAtIndex(2);

	if (string.length() > 2 && char1 == ':' && char2 == '\\')
	{
		// Windows file path
		mPathSeparator = (NChar)'\\';
	}
	else
	{
		// Other path
		mPathSeparator = '/';
	}
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
	return mPath.subString(mPath.findLast(mPathSeparator) + 1, 0);
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
		SInt32 res = mPath.findLast(mPathSeparator);
		if (res)
			mPath = mPath.subString(0, mPath.findLast(mPathSeparator));
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
	mPath += mPathSeparator;
	mPath += component;
}

std::ostream& operator << (std::ostream& stream, const CURL& url)
{
	return stream << url.path();
}

	} // namespace le
} // namespace sokira
