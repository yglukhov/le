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
	return CURL(contentsUrl().path() + "/Info.plist");
}

CURL CBundle::resourcesUrl() const
{
	return CURL(contentsUrl().path() + "/Resources");
}

CURL CBundle::executableUrl() const
{
	return mExecutableURL;
}

	} // namespace le
} // namespace sokira
