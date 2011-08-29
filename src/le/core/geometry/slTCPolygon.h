#if !defined SL_LE_core_geometry_slTCPolygon_h
#define SL_LE_core_geometry_slTCPolygon_h

#include <vector>
#include <le/core/debug/slAssert.h>
#include "slTCSegment2D.h"

namespace sokira
{
	namespace le
	{

template <typename T>
class TCPolygon
{
	typedef TCPoint2D<T> TPoint;
	typedef std::vector<TPoint> TPoints;
	typedef TCPolygon<T> TSelf;

	static inline int Sign(T val)
	{
		return (val < 0) ? -1 : 1;
	}

	public:
		static TCPolygon createByWideningSegment(const TCSegment2D<T>& segment, T width)
		{
			TCPolygon result;
			T length = segment.length();
			Float32 cosinus = segment.horizontalLength() / length;
			Float32 sinus = segment.verticalLength() / length;
			result.addPoint(TPoint(segment.b().x() + width * sinus, segment.b().y() - width * cosinus));
			result.addPoint(TPoint(segment.b().x() - width * sinus, segment.b().y() + width * cosinus));
			result.addPoint(TPoint(segment.a().x() - width * sinus, segment.a().y() + width * cosinus));
			result.addPoint(TPoint(segment.a().x() + width * sinus, segment.a().y() - width * cosinus));
			return result;
		}

		static TCPolygon createWithRect(const TCRectangle<T>& rect)
		{
			TCPolygon result;
			result.addPoint(rect.topLeft());
			result.addPoint(rect.topRight());
			result.addPoint(rect.bottomRight());
			result.addPoint(rect.bottomLeft());
			return result;
		}

		void addPoint(const TPoint& point)
		{
			mPoints.push_back(point);
		}

		Bool containsPoint(const TPoint& point) const
		{
			Bool result = false;
			int i, j;
			size_t nvert = mPoints.size();
			for (i = 0, j = nvert - 1; i < nvert; j = i++)
			{
				if (((mPoints[i].y() > point.y()) != (mPoints[j].y() > point.y())) &&
					(point.x() < (mPoints[j].x() - mPoints[i].x()) * (point.y()-mPoints[i].y()) / (mPoints[j].y()-mPoints[i].y()) + mPoints[i].x()) )
						result = !result;
			}
			return result;
		}

		Bool isConvex() const
		{
			size_t length = mPoints.size();
			if (length < 3) return false;
			--length;

			int xCh = 0, yCh = 0;

			TPoint a = mPoints[0] - mPoints[1];
			size_t i = 1;
			for (; i < length; ++i)
			{
				TPoint b = mPoints[i] - mPoints[i + 1];
				if (Sign(a.x()) != Sign(b.x())) ++xCh;
				if (Sign(a.y()) != Sign(b.y())) ++yCh;
				if (xCh > 2 || yCh > 2) return false;
				a = b;
			}

			TPoint b = mPoints[i] - mPoints[0];
			if (Sign(a.x()) != Sign(b.x())) ++xCh;
			if (Sign(a.y()) != Sign(b.y())) ++yCh;

			return (xCh <= 2 && yCh <= 2);
		}

		typedef SInt32 int32;
//		int32 DecomposeConvex(b2Polygon* results, int32 maxPolys)
//		{
//				int nVertices = mPoints.size();
//
//				if (nVertices < 3) return 0;
//
//				std::vector<TSelf> triangles = 
//				b2Triangle* triangulated = new b2Triangle[nVertices - 2];
//				int32 nTri;
//				if (isCounterClockWise())
//				{
//					TCPolygon tempP = *this;
//					tempP.reverse();
//					nTri = TriangulatePolygon(tempP.x, tempP.y, tempP.nVertices, triangulated);
//				}
//				else
//				{
//					//printf("It is not ccw \n");
//					nTri = TriangulatePolygon(p->x, p->y, nVertices, triangulated);
//				}
//
//				if (nTri < 1) {
//					printf("Failed triangulation.  Dumping polygon: \n");
//					p->print();
//					//Still no luck?  Oh well...
//					return -1;
//				}
//				int32 nPolys = PolygonizeTriangles(triangulated, nTri, results, maxPolys);
//				delete[] triangulated;
//				return nPolys;
//		}

		std::vector<TSelf> decomposeToTriangles() const
		{
			if (isCounterClockWise())
			{
				TSelf cwSelf = *this;
				cwSelf.reverse();
				return cwSelf.decomposeCWToTriangles();
			}

			return decomposeCWToTriangles();
		}

		std::vector<TSelf> decomposeCWToTriangles() const
		{
			size_t vNum = mPoints.size();
			std::vector<TSelf> result;
			if (vNum < 3)
				return result;

//		b2Triangle* buffer = new b2Triangle[vNum-2];
//	int32 bufferSize = 0;
		TPoints rem = mPoints;
//        float32* xrem = new float[vNum];
//        float32* yrem = new float[vNum];
//        for (int32 i = 0; i < vNum; ++i) {
//            xrem[i] = xv[i];
//            yrem[i] = yv[i];
//        }
//		
//		int xremLength = vNum;
		
        while (vNum > 3) {
            // Find an ear
            int32 earIndex = -1;
            for (int32 i = 0; i < vNum; ++i) {
                if (isEarAtIndex(rem, i)) {
                    earIndex = i;
                    break;
                }
            }
			
            // If we still haven't found an ear, we're screwed.
            // The user did Something Bad, so return -1.
            // This will probably crash their program, since
            // they won't bother to check the return value.
            // At this we shall laugh, heartily and with great gusto.
            LE_ASSERT(earIndex != -1);
			
            // Clip off the ear:
            // - remove the ear tip from the list
			
            // Opt note: actually creates a new list, maybe
            // this should be done in-place instead. A linked
            // list would be even better to avoid array-fu.
            --vNum;

            // - add the clipped triangle to the triangle list
            size_t under = (earIndex == 0) ? (vNum) : (earIndex - 1);
            size_t over = (earIndex == vNum) ? 0 : (earIndex + 1);

			TSelf toAdd;
			toAdd.addPoint(rem[earIndex]);
			toAdd.addPoint(rem[over]);
			toAdd.addPoint(rem[under]);
			result.push_back(toAdd);

			rem.erase(rem.begin() + earIndex);
//
//            b2Triangle toAdd = b2Triangle(xrem[earIndex], yrem[earIndex], xrem[over], yrem[over], xrem[under], yrem[under]);
//            buffer[bufferSize].Set(toAdd);
//            ++bufferSize;
//
//            float32* newx = new float[vNum];
//            float32* newy = new float[vNum];
//            int32 currDest = 0;
//            for (int32 i = 0; i < vNum; ++i) {
//                if (currDest == earIndex) ++currDest;
//                newx[i] = xrem[currDest];
//                newy[i] = yrem[currDest];
//                ++currDest;
//            }
//			
//			
//            // - replace the old list with the new one
//            delete[] xrem;
//            delete[] yrem;
//            xrem = newx;
//            yrem = newy;
        }

			TSelf toAdd;
			toAdd.addPoint(rem[1]);
			toAdd.addPoint(rem[2]);
			toAdd.addPoint(rem[0]);
			result.push_back(toAdd);
//
//
//        b2Triangle toAdd = b2Triangle(xrem[1], yrem[1], xrem[2], yrem[2],
//								  xrem[0], yrem[0]);
//        buffer[bufferSize].Set(toAdd);
//        ++bufferSize;
//		
//        delete[] xrem;
//        delete[] yrem;
		
        LE_ASSERT(result.size() == mPoints.size() - 2);
//
//        for (int32 i = 0; i < bufferSize; i++) {
//            results[i].Set(buffer[i]);
//        }
//		
//        delete[] buffer;
		
        return result;

		}

		std::vector<TSelf> decomposeToConvex() const
		{
			std::vector<TSelf> result;
			result.push_back(*this);
			return result;
		}

//
//		std::vector<TSelf> intersectionWithPolygon(const TSelf& poly) const
//		{
//			size_t selfCount = mPoints.size();
//			size_t otherCount = poly.mPoints.size();
//
//			size_t selfPassed = 0;
//			size_t otherPassed = 0;
//
//			const TSelf* curPoly = this;
//			size_t curPassed = selfPassed;
//
//			std::vector<TSelf> result;
//
//			while (selfPassed < selfCount || otherPassed < otherCount)
//			{
//				TSelf intersection;
//				TPoint nextPoint curPoly->mPoints[curPassed];
//				if (poly.containsPoint(nextPoint))
//				{
//					intersection.addPoint(nextPoint);
//				}
//			}
//
//			return result;
//		}

		void reverse()
		{
			mPoints = TPoints(mPoints.rbegin(), mPoints.rend());
		}

		Float32 area() const
		{
			// First do wraparound
			size_t nVertices = mPoints.size();
			Float32 area = mPoints[nVertices - 1].x() * mPoints[0].y() - mPoints[0].x() * mPoints[nVertices - 1].y();
			for (size_t i = 0; i < nVertices - 1; ++i)
			{
				area += mPoints[i].x() * mPoints[i + 1].y() - mPoints[i + 1].x() * mPoints[i].y();
			}

			return area * 0.5f;
		}

		void dump(std::ostream& stream) const
		{
			stream << '{';
			Bool start = true;
			for (typename TPoints::const_iterator it = mPoints.begin(); it != mPoints.end(); ++it)
			{
				if (!start)
				{
					stream << ", ";
				}
				else
				{
					start = false;
				}

				stream << *it;
			}
			stream << '}';
		}

		const TPoints& points() const
		{
			return mPoints;
		}

		Bool isCounterClockWise() const
		{
			return area() > 0.0f;
		}

	private:

		static Bool isEarAtIndex(const TPoints& points, size_t i)
		{
			if (i >= points.size() || i < 0 || points.size() < 3)
			{
				return false;
			}

			Float32 dx0, dy0, dx1, dy1;

			size_t upper = i + 1;
			size_t lower = i - 1;
			if (i == 0)
			{
				dx0 = points[0].x() - points[points.size() - 1].x();
				dy0 = points[0].y() - points[points.size() - 1].y();
				dx1 = points[1].x() - points[0].x();
				dy1 = points[1].y() - points[0].y();
				lower = points.size() - 1;
			}
			else if (i == points.size() - 1)
			{
				dx0 = points[i].x() - points[i - 1].x();
				dy0 = points[i].y() - points[i - 1].y();
				dx1 = points[0].x() - points[i].x();
				dy1 = points[0].y() - points[i].y();
				upper = 0;
			}
			else
			{
				dx0 = points[i].x() - points[i - 1].x();
				dy0 = points[i].y() - points[i - 1].y();
				dx1 = points[i + 1].x() - points[i].x();
				dy1 = points[i + 1].y() - points[i].y();
			}

			Float32 cross = dx0 * dy1 - dx1 * dy0;

			if (cross > 0)
				return false;

			TSelf myTri;
			myTri.addPoint(points[i]);
			myTri.addPoint(points[upper]);
			myTri.addPoint(points[lower]);

			for (size_t j = 0; j < points.size(); ++j)
			{
				if (j == i || j == lower || j == upper)
					continue;
				if (myTri.containsPoint(points[j]))
					return false;
			}

			return true;
		}

		TPoints mPoints;
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const TCPolygon<T>& poly)
{
	poly.dump(stream);
	return stream;
}

typedef TCPolygon<Float32> CPolygon;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCPolygon_h
