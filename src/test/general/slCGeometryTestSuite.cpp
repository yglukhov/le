#include <le/core/geometry/slTCRectangle.h>
#include <le/core/geometry/slTCPolygon.h>
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

void CGeometryTestSuite::testPolygons()
{
	CPolygon poly;
	poly.addPoint(CPoint2D(0, 0));
	poly.addPoint(CPoint2D(1, 0));
	poly.addPoint(CPoint2D(0, 1));
	LE_ASSERT(poly.containsPoint(CPoint2D(0.3, 0.3)));
	LE_ASSERT(!poly.containsPoint(CPoint2D(1, 1)));
	LE_ASSERT(poly.isConvex());
	LE_ASSERT(poly.isCounterClockWise());

	poly.addPoint(CPoint2D(0.2, 0.2));
	LE_ASSERT(!poly.isConvex());
	LE_ASSERT(poly.isCounterClockWise());

//	poly.reverse();
//	LE_ASSERT(!poly.isCounterClockWise());

	std::vector<CPolygon> decomposedPolys = poly.decomposeToTriangles();
	LE_ASSERT(decomposedPolys.size() == 2);
	for (std::vector<CPolygon>::iterator it = decomposedPolys.begin(); it != decomposedPolys.end(); ++it)
	{
		std::cout << "Decomposed poly: " << *it << std::endl;
	}


	CPolygon triangle1;
	triangle1.addPoint(CPoint2D(0, 100));
	triangle1.addPoint(CPoint2D(100, 0));
	triangle1.addPoint(CPoint2D(0, 0));

	CPolygon triangle2;
	triangle2.addPoint(CPoint2D(0, 100));
	triangle2.addPoint(CPoint2D(0, 0));
	triangle2.addPoint(CPoint2D(100, 0));

	std::cout << "Triangle1 area: " << triangle1.area() << std::endl;
	std::cout << "Triangle2 area: " << triangle2.area() << std::endl;

	LE_ASSERT(!triangle2.isCounterClockWise());

	LE_ASSERT(triangle1.isCounterClockWise() != triangle2.isCounterClockWise());
}

	} // namespace le
} // namespace sokira
