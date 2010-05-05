#include <le/core/slCURL.h>
#include "slCWorkspace.h"

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
	char* home = getenv("HOME");
	if (home) return CURL(home);
	return CURL();
}

	} // namespace le
} // namespace sokira
