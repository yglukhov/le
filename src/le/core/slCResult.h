#if !defined SL_LE_core_slCResult_h
#define SL_LE_core_slCResult_h

#include "slCString.h"

namespace sokira
{
	namespace le
	{

class CResult
{
	public:
		CResult(Bool success);
		CResult(const CString& errorDescription);
		operator Bool() const;

		CString description() const;

		inline void throwIfFailure() const throw (CResult)
		{
			if (!mSuccess)
			{
				throw *this;
			}
		}

		static CResult lastError();

	private:
		Bool mSuccess;
		CString mErrorDescription;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCRandomGenerator_h
