#if !defined H_included_slCAssertControl
#define H_included_slCAssertControl

#include <le/core/thread/slTCThreadSingletone.h>


namespace sokira
{
	namespace le
	{

class CAssertionPolicy;

class CAssertControl : public TCThreadSingletone<CAssertControl>
{
	public:
		CAssertControl();
		~CAssertControl();

		CAssertionPolicy *assertionPolicy() const;
		void setAssertionPolicy(CAssertionPolicy *policy);

	private:
		CAssertionPolicy *mPolicy;
};

	} // namespace le
} // namespace sokira


#endif // not defined H_included_slCAssertControl
