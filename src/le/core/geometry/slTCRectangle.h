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
		T minX() const
		{
			return TSelf::x();
		}

		T minY() const
		{
			return TSelf::y();
		}

		T midX() const
		{
			return TSelf::x() + TSelf::width() / 2;
		}

		T midY() const
		{
			return TSelf::y() + TSelf::height() / 2;
		}

		T maxX() const
		{
			return TSelf::x() + TSelf::width();
		}

		T maxY() const
		{
			return TSelf::y() + TSelf::height();
		}


		TPoint topLeft() const
		{
			return position();
		}

		TPoint topRight() const
		{
			return TPoint(TSelf::maxX(), TSelf::minY());
		}

		TPoint bottomLeft() const
		{
			return TPoint(TSelf::minX(), TSelf::maxY());
		}

		TPoint bottomRight() const
		{
			return TPoint(TSelf::maxX(), TSelf::maxY());
		}

		TPoint center() const
		{
			return TPoint(TSelf::midX(), TSelf::midY());
		}

		bool containsPoint(const TPoint& point) const
		{
			return (point.x() >= TSelf::minX() && point.x() <= TSelf::maxX() &&
					 point.y() >= TSelf::minY() && point.y() <= TSelf::maxY());
		}

		bool containsRect(const TCRectangle& rect) const
		{
			return rect.x() >= TSelf::x() && rect.y() >= TSelf::y() &&
					rect.maxX() <= TSelf::maxX() &&
					rect.maxY() <= TSelf::maxY();
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

		void extendToPoint(const TPoint& point)
		{
			if (TSelf::x() > point.x()) TSelf::setX(point.x());
			if (TSelf::y() > point.y()) TSelf::setY(point.y());
			if (TSelf::maxX() < point.x()) TSelf::setWidth(point.x() - TSelf::minX());
			if (TSelf::maxY() < point.y()) TSelf::setHeight(point.y() - TSelf::minY());
		}

		void extendToRect(const TCRectangle& rect)
		{
			if (TSelf::x() > rect.x()) TSelf::setX(rect.x());
			if (TSelf::y() > rect.y()) TSelf::setY(rect.y());
			if (TSelf::maxX() < rect.maxX()) TSelf::setWidth(rect.maxX() - TSelf::minX());
			if (TSelf::maxY() < rect.maxY()) TSelf::setHeight(rect.maxY() - TSelf::minY());
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

template <typename T>
std::ostream& operator << (std::ostream& stream, const TCRectangle<T>& rect)
{
	return stream << '{' << rect.position() << ", " << rect.size() << '}';
}

typedef TCRectangle<Float32> CRectangle;

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCRectangle_h
