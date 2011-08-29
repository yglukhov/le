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

		TCSegment2D(T ax, T ay, T bx, T by) :
			mA(ax, ay),
			mB(bx, by)
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

		void scale(Float32 k)
		{
			mB.setX(horizontalLength() * k + mA.x());
			mB.setY(verticalLength() * k + mA.y());
		}

		T horizontalLength() const
		{
			return mB.x() - mA.x();
		}

		T verticalLength() const
		{
			return mB.y() - mA.y();
		}

		T length() const
		{
			T a = horizontalLength();
			T b = verticalLength();
			return std::sqrt(a * a + b * b);
		}

		void setLength(T newLength)
		{
			scale(newLength / length());
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

		Float32 tangent() const
		{
			return verticalLength() / horizontalLength();
		}

		Float32 angleInRadians() const
		{
			Float32 result = std::atan(tangent());
			if (mB.x() < mA.x()) result += M_PI;
			return result;
		}

		Float32 angleInDegrees() const
		{
			return radiansToDegrees(angleInRadians());
		}

		void invert()
		{
			TPoint tmp = mA;
			mA = mB;
			mB = tmp;
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


template <typename T>
std::ostream& operator << (std::ostream& stream, const TCSegment2D<T>& segment)
{
	return stream << '{' << segment.a() << ", " << segment.b() << '}';
}


typedef TCSegment2D<Float32> CSegment2D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCSegment2D_h
