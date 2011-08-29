#if !defined H_slCRandomTestSuite_included
#define H_slCRandomTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CRandomTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CRandomTestSuite);

	public:
		virtual void runTest()
		{
			testRandom();
		}

	private:
		void testRandom();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCRandomTestSuite_included
