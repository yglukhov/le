#if !defined SL_LE_core_geometry_slTCPoint2D_h
#define SL_LE_core_geometry_slTCPoint2D_h

#include <math.h>
#include <le/core/slTypes.h>


namespace sokira
{
	namespace le
	{

template <typename T>
class TCPoint2D
{
	// Construction
	public:
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

	// Operators
//		CPoint& operator=(const CPoint& copy);
		Bool operator == (const TCPoint2D& point) const
		{
			return !(*this == point);
		}

		Bool operator != (const TCPoint2D& point) const
		{
			return mX != point.mX || mY != point.mY;
		}

	// Members
	private:
		T mX, mY;
};

typedef TCPoint2D<Float32> CPoint2D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCPoint2D_h
