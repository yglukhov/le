#if !defined SL_LE_core_slCURL_h
#define SL_LE_core_slCURL_h

#include "slCString.h"


namespace sokira
{
	namespace le
	{

class CURL : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CURL)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CURL();
		CURL(const CString& string);

		CString hostName() const;
		CString scheme() const;
		CString netLocation() const;
		CString userName() const;
		CString password() const;
		CString path() const;
		CString extension() const;
		CString lastPathComponent() const;
		CString queryString() const;
		SInt32 portNumber() const;

		Bool operator == (const CURL& url) const;

		void removeLastPathComponents(UInt32 componentCount);
		void removeLastPathComponent();
		void appendPathComponent(const CString& component);

	private:
		CString mPath;
		CString mPathSeparator;
};

std::ostream& operator << (std::ostream& stream, const CURL& url);


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCURL_h
