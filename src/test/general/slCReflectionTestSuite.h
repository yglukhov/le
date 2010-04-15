#if !defined H_slCReflectionTestSuite_included
#define H_slCReflectionTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CReflectionTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CReflectionTestSuite);

	public:
		virtual void runTest()
		{
			testSelectors();
		}

	private:
		void testSelectors();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCReflectionTestSuite_included
