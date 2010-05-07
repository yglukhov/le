#include <le/core/slCDictionary.h>
#include "slCBundle.h"

namespace sokira
{
	namespace le
	{

CBundle::CBundle() :
	mInfoDictionary(NULL)
{

}

CBundle::CBundle(const CURL& executableUrl) :
	mExecutableURL(executableUrl),
	mInfoDictionary(NULL)
{

}

CURL CBundle::url() const
{
	CURL result = contentsUrl();
	result.removeLastPathComponent();
	return result;
}

CURL CBundle::contentsUrl() const
{
	CURL result = executableUrl();
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	result.removeLastPathComponents(2);
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
	result.removeLastPathComponents(3);
	result.appendPathComponent("Contents");
#endif
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
	return infoDictionary().valueAsStringForKey("CFBundleIdentifier");
}

CDictionary CBundle::infoDictionary() const
{
	if (!mInfoDictionary)
		mInfoDictionary = new CDictionary(CDictionary::createWithContentsOfURL(infoPlistUrl()));
	return *mInfoDictionary;
}

	} // namespace le
} // namespace sokira
