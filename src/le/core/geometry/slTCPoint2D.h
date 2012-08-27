#if !defined SL_LE_core_geometry_slTCPoint2D_h
#define SL_LE_core_geometry_slTCPoint2D_h

#include <cmath>
#include <algorithm>
#include <iostream>
#include <le/core/slTypes.h>


namespace sokira
{
	namespace le
	{

template <typename T>
static inline T degreesToRadians(T degrees)
{
	return degrees * M_PI / 180;
}

template <typename T>
static inline T radiansToDegrees(T radians)
{
	return radians * 180 / M_PI;
}


template <typename T>
class TCPoint2D
{
	// Construction
	public:
		typedef T TComponentType;

		TCPoint2D(T x = T(), T y = T()) :
			mX(x),
			mY(y)
		{

		}

//		TCPoint2D(const TCPoint2D& copy);

	// Attributes
		T x() const
		{
			return mX;
		}

		void setX(T X)
		{
			mX = X;
		}

		T y() const
		{
			return mY;
		}

		void setY(T Y)
		{
			mY = Y;
		}

		void offset(T byX, T byY)
		{
			mX += byX;
			mY += byY;
		}

		T distanceFromPoint(const TCPoint2D& point) const
		{
			T a = mX - point.mX;
			T b = mY - point.mY;
			return sqrtf(a*a + b*b);
		}

		void translateByRadiansAndLength(Float32 angle, T length)
		{
			mX += length * std::cos(angle);
			mY += length * std::sin(angle);
		}

		void translateByDegreesAndLength(Float32 angle, T length)
		{
			translateByRadiansAndLength(degreesToRadians(angle), length);
		}

	// Operators
//		CPoint& operator=(const CPoint& copy);
		Bool operator == (const TCPoint2D& point) const
		{
			return mX == point.mX && mY == point.mY;
		}

		Bool operator != (const TCPoint2D& point) const
		{
			return mX != point.mX || mY != point.mY;
		}

		TCPoint2D operator - (const TCPoint2D& lhs) const
		{
			return TCPoint2D(x() - lhs.x(), y() - lhs.y());
		}

		TCPoint2D operator + (const TCPoint2D& lhs) const
		{
			return TCPoint2D(x() + lhs.x(), y() + lhs.y());
		}

	// Members
	private:
		T mX, mY;
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const TCPoint2D<T>& point)
{
	return stream << '{' << point.x() << ", " << point.y() << '}';
}

typedef TCPoint2D<Float32> CPoint2D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCPoint2D_h
