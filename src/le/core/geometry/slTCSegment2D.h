#if !defined SL_LE_core_geometry_slTCSegment2D_h
#define SL_LE_core_geometry_slTCSegment2D_h

#include <algorithm>
#include <cmath>
#include "slTCPoint2D.h"


namespace sokira
{
	namespace le
	{

template <typename T>
class TCSegment2D
{
	typedef TCPoint2D<T> TPoint;
	// Construction
	public:
		TCSegment2D(const TPoint& a = TPoint(), const TPoint& b = TPoint()) :
			mA(a),
			mB(b)
		{
		
		}


	// Attributes
		TPoint a() const
		{
			return mA;
		}

		void setA(const TPoint& a)
		{
			mA = a;
		}

		TPoint b() const
		{
			return mB;
		}

		void setB(const TPoint& b)
		{
			mB = b;
		}

		T length() const
		{
			T a = mB.x() - mA.x();
			T b = mB.y() - mA.y();
			return std::sqrt(a * a + b * b);
		}

		Bool intersectsWith(const TCSegment2D& segment) const
		{
			// Store the values for fast access and easy
			// equations-to-code conversion
			T x1 = mA.x(), x2 = mB.x(), x3 = segment.mA.x(), x4 = segment.mB.x();
			T y1 = mA.y(), y2 = mB.y(), y3 = segment.mA.y(), y4 = segment.mB.y();

			T d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
			// If d is zero, there is no intersection
			if (d == 0) return false;

			// Get the x and y
			T pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
			T x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
			T y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

			return x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
				x >= std::min(x3, x4) && x <= std::max(x3, x4) &&
				y >= std::min(y1, y2) && y <= std::max(y1, y2) &&
				y >= std::min(y3, y4) && y <= std::max(y3, y4);
		}

	// Operators
//		CPoint& operator=(const CPoint& copy);
		Bool operator == (const TCSegment2D& segment) const
		{
			return mA == segment.mA && mB == segment.mB;
		}
//		bool operator!=(const CPoint& point) const;

	// Members
	private:
		TPoint mA, mB;
};

typedef TCSegment2D<Float32> CSegment2D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCSegment2D_h
