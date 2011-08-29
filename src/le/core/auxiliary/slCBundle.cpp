#include <le/core/slCDictionary.h>
#include "slCBundle.h"
#include "slCFileManager.h"

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
#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	result.removeLastPathComponent();
#endif
	return result;
}

CURL CBundle::contentsUrl() const
{
	CURL result = executableUrl();
#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
	result.removeLastPathComponents(2);
#elif LE_TARGET_PLATFORM == LE_PLATFORM_IOS
	result.removeLastPathComponent();
#elif LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
	result.removeLastPathComponent();
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
#if LE_TARGET_PLATFORM != LE_PLATFORM_IOS
	result.appendPathComponent("Resources");
#endif
	return result;
}

CURL CBundle::executableUrl() const
{
	return mExecutableURL;
}

CURL CBundle::URLForResource(const CString& name, const CString& type) const
{
	CURL url = resourcesUrl();

	CString localization = LESTR("English.lproj"); // TODO: Aquire localization properly

	CString fileName = name;
	if (type.length())
	{
		fileName += ".";
		fileName += type;
	}

	CURL tempUrl = url;
	tempUrl.appendPathComponent(localization);
	tempUrl.appendPathComponent(fileName);

	CFileManager fileManager;
	if (fileManager.fileExists(tempUrl))
	{
		return tempUrl;
	}

	tempUrl = url;
	tempUrl.appendPathComponent(fileName);

	if (fileManager.fileExists(tempUrl))
	{
		return tempUrl;
	}

	return CURL();
}

CURL CBundle::URLForImageResource(const CString& name) const
{
	CURL result = URLForResource(name, LESTR("jpg"));
	if (result.isEmpty())
	{
		result = URLForResource(name, LESTR("jpeg"));
		if (result.isEmpty())
		{
			result = URLForResource(name, LESTR("gif"));
			if (result.isEmpty())
			{
				result = URLForResource(name, LESTR("bmp"));
			}
		}
	}

	return result;
}

CURL CBundle::URLForSoundResource(const CString& name) const
{
	CURL result = URLForResource(name, LESTR("ogg"));
	if (result.isEmpty())
	{
		result = URLForResource(name, LESTR("mp3"));
		if (result.isEmpty())
		{
			result = URLForResource(name, LESTR("wav"));
		}
	}

	return result;
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
