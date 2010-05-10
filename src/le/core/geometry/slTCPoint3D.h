#if !defined SL_LE_core_geometry_slTCPoint3D_h
#define SL_LE_core_geometry_slTCPoint3D_h

#include "slTCPoint2D.h"

namespace sokira
{
	namespace le
	{

template <typename T>
class TCPoint3D : public TCPoint2D<T>
{
	// Construction
	public:
		TCPoint3D(T x = T(), T y = T(), T z = T()) :
			TCPoint2D<T>(x, y),
			mZ(z)
		{

		}

//		TCPoint2D(const TCPoint2D& copy);

	// Attributes
		T z() const
		{
			return mZ;
		}

		void z(T Z)
		{
			mZ = Z;
		}

	// Operators
//		CPoint& operator=(const CPoint& copy);
//		bool operator==(const CPoint& point) const;
//		bool operator!=(const CPoint& point) const;

	// Members
	private:
		T mZ;
};

typedef TCPoint3D<Float32> CPoint3D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCPoint3D_h
