#include <le/core/geometry/slTCRectangle.h>
#include "slCGeometryTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CGeometryTestSuite);

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeometryTestSuite::testRectangles()
{
	//
	// +---+
	// |   |
	// +---+
	//      +---+
	//      |   |
	//      +---+
	//

	CRectangle rect1(0, 0, 50, 50);
	CRectangle rect2(100, 100, 50, 50);
	LE_ASSERT(!rect1.intersectsRect(rect2));
	LE_ASSERT(!rect2.intersectsRect(rect1));

	//
	// +----+
	// |    |
	// |  +-----+
	// |  | |   |
	// |  +-----+
	// |    |
	// +----+
	//

	rect1 = CRectangle(0, 0, 50, 100);
	rect2 = CRectangle(25, 25, 50, 50);
	LE_ASSERT(rect1.intersectsRect(rect2));
	LE_ASSERT(rect2.intersectsRect(rect1));

	//
	//    +----+
	//    |    |
	// +----------+
	// |  |    |  |
	// +----------+
	//    |    |
	//    +----+
	//

	rect1 = CRectangle(25, 0, 50, 100);
	rect2 = CRectangle(0, 25, 100, 50);
	LE_ASSERT(rect1.intersectsRect(rect2));
	LE_ASSERT(rect2.intersectsRect(rect1));
}

	} // namespace le
} // namespace sokira
