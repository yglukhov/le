#if !defined H_slCGeometryTestSuite_included
#define H_slCGeometryTestSuite_included

#include "slCTestSuite.h"

namespace sokira
{
	namespace le
	{

class CGeometryTestSuite : public CTestSuite
{
	LE_DECLARE_RUNTIME_CLASS(CGeometryTestSuite);

	public:
		virtual void runTest()
		{
			testRectangles();
			testPolygons();
		}

	private:
		void testRectangles();
		void testPolygons();
};

	} // namespace le
} // namespace sokira

#endif // not defined H_slCGeometryTestSuite_included
