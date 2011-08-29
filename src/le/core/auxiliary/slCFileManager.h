#if !defined SL_LE_core_auxiliary_slCFileManager_h
#define SL_LE_core_auxiliary_slCFileManager_h

#include <le/core/slCURL.h>

namespace sokira
{
	namespace le
	{

class CFileManager
{
	public:
		Bool fileExists(const CURL& url) const;
		Bool fileExists(const CURL& url, Bool* isDirectory) const;
		Bool createDirectoryAtURL(const CURL& url, Bool createIntermediateDirectories = false, void* parameters = NULL) const;
		Bool moveItem(const CURL& fromURL, const CURL& toURL) const;
		Bool copyItem(const CURL& fromURL, const CURL& toURL) const;
		Bool removeItem(const CURL& url) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCFileManager_h
