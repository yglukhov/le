
#include <le/core/slCURL.h>
#include "slCWorkspace.h"

#if LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
#include <shlobj.h>
#endif

namespace sokira
{
	namespace le
	{

CURL CWorkspace::userPreferencesURL() const
{
	CURL result = userHomeURL();
	result.appendPathComponent(LESTR("Library/Preferences"));
	return result;
}

CURL CWorkspace::userHomeURL() const
{
#if LE_TARGET_PLATFORM == LE_PLATFORM_WINDOWS
	char buffer[MAX_PATH];
	if (SHGetSpecialFolderPath(NULL, buffer, CSIDL_PROFILE, FALSE)) return CURL(buffer);
#else
	char* home = getenv("HOME");
	if (home) return CURL(home);
#endif
	return CURL();
}

	} // namespace le
} // namespace sokira
