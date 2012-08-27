#if !defined SL_LE_core_geometry_slTCAffinetransform2D_h
#define SL_LE_core_geometry_slTCAffinetransform2D_h

#include <string.h>
#include "slTCPoint3D.h"

namespace sokira
{
	namespace le
	{

template <typename T>
class TCAffineTransform3D
{
	public:
		TCAffineTransform3D()
		{
			m[0] = 1; m[4] = 0; m[ 8] = 0; m[12] = 0;
			m[1] = 0; m[5] = 1; m[ 9] = 0; m[13] = 0;
			m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
			m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 0;
		}

		TCAffineTransform3D(const T* elements, Bool rowMajor)
		{
			if (rowMajor)
			{

			}
			else
			{
				memcpy(m, elements, sizeof(m));
			}
		}

		void getMatrix(T* elements, Bool rowMajor) const;
			   
		TCPoint3D<T> transformPoint(const TCPoint3D<T>& point)
		{
		
		}

		void translate(T x, T y, T z)
		{
			m[12] += x;
			m[13] += y;
			m[14] += z;
		}

		void rotate(T x, T y, T z)
		{
		
		}

		void scale(T x, T y, T z)
		{
			m[0] *= x;
			m[5] *= y;
			m[10] *= z;
		}

	private:
		T m[16];
};

typedef TCAffineTransform3D<Float32> CAffineTransform;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCAffinetransform2D_h
