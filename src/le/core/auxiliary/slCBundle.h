#if !defined SL_LE_core_auxiliary_slCBundle_h
#define SL_LE_core_auxiliary_slCBundle_h

#include <le/core/slCURL.h>

namespace sokira
{
	namespace le
	{

class CBundle
{
	public:
		CBundle();
		CBundle(const CString& path);
		CBundle(const CURL& url);

		CURL url() const;
		CURL infoPlistUrl() const;
		CURL resourcesUrl() const;
		CURL executableUrl() const;

};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_auxiliary_slCBundle_h
