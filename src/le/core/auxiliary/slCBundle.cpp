#include "slCBundle.h"

namespace sokira
{
	namespace le
	{

CBundle::CBundle()
{

}

CBundle::CBundle(const CString& executablePath) :
	mExecutableURL(executablePath)
{

}

CBundle::CBundle(const CURL& executableUrl) :
	mExecutableURL(executableUrl)
{

}


CURL CBundle::url() const
{
	return CURL();
}

CURL CBundle::contentsUrl() const
{
	CURL result = executableUrl();
	result.removeLastPathComponents(2);
	return result;
}

CURL CBundle::infoPlistUrl() const
{
	CURL result = contentsUrl();
	result.appendPathComponent("Info.plist");
	return result;
}

CURL CBundle::resourcesUrl() const
{
	CURL result = contentsUrl();
	result.appendPathComponent("Resources");
	return result;
}

CURL CBundle::executableUrl() const
{
	return mExecutableURL;
}

CString CBundle::identifier() const
{
	return LESTR("org.7lifes.le.app");
}

	} // namespace le
} // namespace sokira
