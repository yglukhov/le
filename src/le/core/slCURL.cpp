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

CURL::CURL(const CString& string)
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
	return CString();
}

CString CURL::extension() const
{
	return CString();
}

CString CURL::lastPathComponent() const
{
	return CString();
}

CString CURL::queryString() const
{
	return CString();
}

SInt32 CURL::portNumber() const
{
	return 0;
}

	} // namespace le
} // namespace sokira
