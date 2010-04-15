#if !defined SL_LE_core_geometry_slTCRectangle_h
#define SL_LE_core_geometry_slTCRectangle_h

#include "slTCPoint2D.h"
#include "slTCSize2D.h"

namespace sokira
{
	namespace le
	{

template <typename T>
class TCRectangle : public TCPoint2D<T>, public TCSize2D<T>
{
	typedef TCPoint2D<T> TPoint;
	typedef TCSize2D<T> TSize;
	typedef TCRectangle TSelf;

	// Construction
	public:
		TCRectangle(T x = T(), T y = T(), T width = T(), T height = T()) :
			TPoint(x, y), TSize(width, height) { }

		TCRectangle(const TPoint& position, T width = T(), T height = T()) :
			TPoint(position), TSize(width, height) { }

		TCRectangle(const TPoint& position, const TSize& size) :
			TPoint(position), TSize(size) { }

		TCRectangle(T x, T y, const TSize& size) :
			TPoint(x, y), TSize(size) { }

	// Attributes

		TPoint topLeft() const
		{
			return position();
		}

		TPoint topRight() const
		{
			return TPoint(TSelf::x() + TSelf::width(), TSelf::y()); 
		}

		TPoint bottomLeft() const
		{
			return TPoint(TSelf::x(), TSelf::y() + TSelf::height());
		}

		TPoint bottomRight() const
		{
			return TPoint(TSelf::x() + TSelf::width(), TSelf::y() + TSelf::height());
		}

		bool containsPoint(const TPoint& point) const
		{
			return (point.x() >= TSelf::x() && (point.x() <= TSelf::x() + TSelf::width()) &&
					 point.y() >= TSelf::y() && (point.y() <= TSelf::y() + TSelf::height()));
		}

		bool containsRect(const TCRectangle& rect) const
		{
			return rect.x() >= TSelf::x() && rect.y() >= TSelf::y() &&
					rect.x() + rect.width() <= TSelf::x() + TSelf::width() &&
					rect.y() + rect.height() <= TSelf::y() + TSelf::height();
		}

		bool intersectsRect(const TCRectangle& rect) const
		{
			T xa1 = TSelf::x();
			T xa2 = xa1 + TSelf::width();
			T xb1 = rect.x();
			T xb2 = xb1 + rect.width();

			T ya1 = TSelf::y();
			T ya2 = ya1 + TSelf::height();
			T yb1 = rect.y();
			T yb2 = yb1 + rect.height();

			return ((xa1 >= xb1 && xa1 <= xb2) || (xa2 >= xb1 && xa2 <= xb2) || // X intersection
					(xb1 >= xa1 && xb1 <= xa2) || (xb2 >= xa1 && xb2 <= xa2)) &&
				   ((ya1 >= yb1 && ya1 <= yb2) || (ya2 >= yb1 && ya2 <= yb2) || // Y intersection
					(yb1 >= ya1 && yb1 <= ya2) || (yb2 >= ya1 && yb2 <= ya2));
		}

		TSize size() const
		{
			return TSize(*this);
		}

		void setSize(const TSize& Size)
		{
			TSize::operator=(Size);
		}

		TPoint position() const
		{
			return TPoint(*this);
		}

		void setPosition(const TPoint& point)
		{
			TPoint::operator=(point);
		}

		void setPosition(T x, T y)
		{
			TSelf::setX(x);
			TSelf::setY(y);
		}

	// Operators
//		CRectangle& operator=(const CRectangle& copy)
//		{
//			position(copy);
//			size(copy);
//			return *this;
//		}

		bool operator==(const TCRectangle& rect) const
		{
			return rect.position() == position() && rect.size() == size();
		}

		bool operator!=(const TCRectangle& rect) const
		{
			return !operator=(rect);
		}
};

typedef TCRectangle<Float32> CRectangle;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCRectangle_h
