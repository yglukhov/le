#if !defined H_slCTestSuite_included
#define H_slCTestSuite_included

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CTestSuite : public CObject
{
	LE_DECLARE_RUNTIME_CLASS(CTestSuite);

	public:
		virtual bool runTest();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCTestSuite_included
