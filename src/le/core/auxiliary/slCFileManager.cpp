#include <le/core/config/slCompiler.h>
#include "slCFileManager.h"

#define LE_TARGET_PLATFORM_FAMILY_IS_MAC (LE_TARGET_PLATFORM == LE_PLATFORM_IOS || LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX)
#define LE_TARGET_PLATFORM_FAMILY_IS_WINDOWS (LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS)

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
#include <sys/stat.h>
#endif

#if LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX
//#include <CoreServices/CoreServices.h>
#endif

namespace sokira
{
	namespace le
	{

Bool CFileManager::fileExists(const CURL& url) const
{
	struct stat buf;
	return !lstat(url.path().cString(), &buf);
}

Bool CFileManager::fileExists(const CURL& url, Bool* isDirectory) const
{
	struct stat buf;
	if (lstat(url.path().cString(), &buf))
	{
		return false;
	}

	if (isDirectory) *isDirectory = S_ISDIR(buf.st_mode);

	return true;
}

Bool CFileManager::createDirectoryAtURL(const CURL& url, Bool createIntermediateDirectories, void* parameters) const
{
	if (createIntermediateDirectories)
	{
		CURL parentURL = url;
		parentURL.removeLastPathComponent();
		if (!fileExists(parentURL))
		{
			createDirectoryAtURL(parentURL, true, parameters);
		}
	}

	return !mkdir(url.path().cString(), 0777);
}

Bool CFileManager::moveItem(const CURL& fromURL, const CURL& toURL) const
{
	return false;
}

Bool CFileManager::copyItem(const CURL& fromURL, const CURL& toURL) const
{
	return false;
}

Bool CFileManager::removeItem(const CURL& url) const
{
	return !remove(url.path().cString());
}

	} // namespace le
} // namespace sokira
