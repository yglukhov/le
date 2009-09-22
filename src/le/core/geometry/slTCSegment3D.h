#if !defined SL_LE_core_geometry_slTCSegment3D_h
#define SL_LE_core_geometry_slTCSegment3D_h

#include "slTCPoint3D.h"


namespace sokira
{
	namespace le
	{

template <typename T>
class TCSegment3D
{
	typedef TCPoint3D<T> TPoint;
	// Construction
	public:
		TCSegment3D(const TPoint& a = TPoint(), const TPoint& b = TPoint()) :
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
			T c = mB.z() - mA.z();
			return sqrtf(a * a + b * b + c * c);
		}

	// Operators
//		CPoint& operator=(const CPoint& copy);
		Bool operator == (const TCSegment3D& segment) const
		{
			return mA == segment.mA && mB == segment.mB;
		}
//		bool operator!=(const CPoint& point) const;

	// Members
	private:
		TPoint mA, mB;
};

typedef TCSegment3D<Float32> CSegment3D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCSegment3D_h
