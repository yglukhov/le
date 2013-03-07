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
		CResult(SInt32 errorCode);
		CResult(const CString& errorDescription, SInt32 errorCode = 1);
		CResult(const NChar* errorDescription, SInt32 errorCode = 1);
		CResult(const WChar* errorDescription, SInt32 errorCode = 1);
		CResult(const CResult& copy);

		const CResult& operator=(const CResult& copy);

		operator Bool() const;

		CString description() const;
		SInt32 errorCode() const;

		inline void throwIfFailure() const throw (CResult)
		{
			if (!*this)
			{
				throw *this;
			}
		}

		static CResult lastError();

	private:
		CString mErrorDescription;
		SInt32 mErrorCode;
};

inline std::ostream& operator << (std::ostream& o, const CResult& result)
{
	if (!result.description().isEmpty())
	{
		o << result.description() << ": ";
	}
	return o << result.errorCode(); 
}

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCRandomGenerator_h
