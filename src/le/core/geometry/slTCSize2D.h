#if !defined SL_LE_core_geometry_slTCSize2D_h
#define SL_LE_core_geometry_slTCSize2D_h

#include <iostream>
#include <le/core/slTypes.h>


namespace sokira
{
	namespace le
	{

template <typename T>
class TCSize2D
{
	// Construction
	public:
		TCSize2D(T width = T(), T height = T()) :
			mWidth(width),
			mHeight(height)
		{

		}

//		TCSize2D(const TCSize2D& copy);

	// Attributes
		T width() const
		{
			return mWidth;
		}

		void setWidth(T width)
		{
			mWidth = width;
		}

		T height() const
		{
			return mHeight;
		}

		void setHeight(T height)
		{
			mHeight = height;
		}

		T area() const
		{
			return mWidth * mHeight;
		}

		T aspectRatio() const
		{
			return mWidth / mHeight;
		}

	// Operators
//		CPoint& operator=(const CPoint& copy);
		Bool operator == (const TCSize2D& size) const
		{
			return !(*this == size);
		}

		Bool operator != (const TCSize2D& size) const
		{
			return mWidth != size.mWidth || mHeight != size.mHeight;
		}

	// Members
	private:
		T mWidth, mHeight;
};


		
template <typename T>
std::ostream& operator << (std::ostream& stream, const TCSize2D<T>& size)
{
	return stream << '{' << size.width() << ", " << size.height() << '}';
}

typedef TCSize2D<Float32> CSize2D;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCSize2D_h
