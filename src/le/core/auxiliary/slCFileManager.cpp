#include <le/core/config/slCompiler.h>
#include "slCFileManager.h"

#define LE_TARGET_PLATFORM_FAMILY_IS_MAC (LE_TARGET_PLATFORM == LE_PLATFORM_IOS || LE_TARGET_PLATFORM == LE_PLATFORM_MACOSX)
#define LE_TARGET_PLATFORM_FAMILY_IS_WINDOWS (LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS)

//#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
#include <sys/stat.h>
//#endif

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#include <direct.h>
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
#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
	struct stat buf;
	return !lstat(url.path().cString(), &buf);
#else
	struct _stat buf;
	return !_stat(url.path().cString(), &buf);
#endif
}

Bool CFileManager::fileExists(const CURL& url, Bool* isDirectory) const
{
#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
	struct stat buf;
	if (lstat(url.path().cString(), &buf))
	{
		return false;
	}

	if (isDirectory) *isDirectory = S_ISDIR(buf.st_mode);

#else
	struct _stat buf;
	if (_stat(url.path().cString(), &buf))
	{
		return false;
	}

	if (isDirectory) *isDirectory = buf.st_mode & _S_IFDIR;

#endif

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

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
	return !mkdir(url.path().cString(), 0777);
#else
	return !_mkdir(url.path().cString());
#endif
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
