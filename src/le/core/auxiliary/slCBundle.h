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
		CBundle(const CString& executablePath);
		CBundle(const CURL& executableUrl);

		CURL url() const;
		CURL contentsUrl() const;
		CURL infoPlistUrl() const;
		CURL resourcesUrl() const;
		CURL executableUrl() const;

		CString identifier() const;

	private:
		CURL mExecutableURL;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_auxiliary_slCBundle_h
