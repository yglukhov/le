#include "slTypes.h"

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
//#pragma mark -- CPoint --
////////////////////////////////////////////////////////////////////////////////

/*CPoint::CPoint(float x, float y, float z) :
	mX(x), mY(y), mZ(z)
{

}

CPoint::CPoint(const CPoint& copy) :
	mX(copy.mX), mY(copy.mY), mZ(copy.mZ)
{

}

//#pragma mark -

float CPoint::x() const
{
	return mX;
}

void CPoint::x(float X)
{
	mX = X;
}

float CPoint::y() const
{
	return mY;
}

void CPoint::y(float Y)
{
	mY = Y;
}

float CPoint::z() const
{
	return mZ;
}

void CPoint::z(float Z)
{
	mZ = Z;
}

//#pragma mark -

// Operators
CPoint& CPoint::operator=(const CPoint& copy)
{
	mX = copy.mX;
	mY = copy.mY;
	mZ = copy.mZ;

	return *this;
}

bool CPoint::operator==(const CPoint& point) const
{
	return ((mX == point.mX) && (mY == point.mY) && (mZ == point.mZ));
}

bool CPoint::operator!=(const CPoint& point) const
{
	return !(operator==(point));
}*/

////////////////////////////////////////////////////////////////////////////////
// CSize
////////////////////////////////////////////////////////////////////////////////


CSize::CSize(float width, float height, float depth) :
	mWidth(width), mHeight(height), mDepth(depth)
{

}

CSize::CSize(const CSize& copy) :
	mWidth(copy.mWidth), mHeight(copy.mHeight), mDepth(copy.mDepth)
{
	
}

//#pragma mark -

// Attributes
float CSize::width() const
{
	return mWidth;
}

void CSize::width(float Width)
{
	mWidth = Width;
}

float CSize::height() const
{
	return mHeight;
}

void CSize::height(float Height)
{
	mHeight = Height;
}

float CSize::depth() const
{
	return mDepth;
}

void CSize::depth(float depth)
{
	mDepth = depth;
}

//#pragma mark -

// Operators
CSize& CSize::operator=(const CSize& copy)
{
	mWidth = copy.mWidth;
	mHeight = copy.mHeight;
	mDepth = copy.mDepth;

	return *this;
}

bool CSize::operator==(const CSize& size) const
{
	return ((mWidth == size.mWidth) && (mHeight == size.mHeight));
}

bool CSize::operator!=(const CSize& size) const
{
	return !(operator==(size));
}

//#pragma mark
////////////////////////////////////////////////////////////////////////////////
//#pragma mark -- CRectangle --
////////////////////////////////////////////////////////////////////////////////

CRectangle::CRectangle(float x, float y, float width, float height) :
	CPoint2D(x, y), CSize2D(width, height)
{

}

CRectangle::CRectangle(const CPoint2D& position, float width, float height) :
	CPoint2D(position), CSize2D(width, height)
{

}

CRectangle::CRectangle(const CRectangle& copy) :
	CPoint2D(copy.position()), CSize2D(copy.size())
{

}

CRectangle::CRectangle(const CPoint2D& position, const CSize2D& size) :
	CPoint2D(position), CSize2D(size)
{

}

CRectangle::CRectangle(float x, float y, const CSize2D& size) :
	CPoint2D(x, y), CSize2D(size)
{

}

//#pragma mark -

CPoint2D CRectangle::topLeft() const
{
	return CPoint(*this);
}

CPoint2D CRectangle::topRight() const
{
	return CPoint2D(x() + width(), y()); 
}

CPoint2D CRectangle::bottomLeft() const
{
	return CPoint2D(x(), y() + height());
}

CPoint2D CRectangle::bottomRight() const
{
	return CPoint2D(x() + width(), y() + height());
}

bool CRectangle::pointInRect(const CPoint2D& point) const
{
	return ((point.x() >= x()) && (point.x() <= x() + width()) &&
			 (point.y() >= y()) && (point.y() <= y() + height()));
}

//#pragma mark -

CSize2D CRectangle::size() const
{
	return CSize2D(*this);
}

void CRectangle::size(const CSize2D& Size)
{
	CSize2D::operator=(Size);
}

CPoint2D CRectangle::position() const
{
	return CPoint2D(*this);
}

void CRectangle::position(const CPoint2D& point)
{
	CPoint2D::operator=(point);
}

void CRectangle::position(float X, float Y)
{
	x(X);
	y(Y);
}

//#pragma mark -

CRectangle& CRectangle::operator=(const CRectangle& copy)
{
	CPoint2D::operator=(copy);
	CSize2D::operator=(copy);
	return *this;
}

bool CRectangle::operator==(const CRectangle& rect) const
{
	return (CPoint2D::operator==(rect) && CSize2D::operator==(rect));
}

bool CRectangle::operator!=(const CRectangle& rect) const
{
	return !(operator==(rect));
}


////////////////////////////////////////////////////////////////////////////////
//CBox
////////////////////////////////////////////////////////////////////////////////

CBox::CBox(float x, float y, float z, float width, float height, float depth) :
	CPoint3D(x, y, z), CSize3D(width, height, depth)
{

}

CBox::CBox(const CPoint3D& position, float width, float height, float depth) :
	CPoint3D(position), CSize3D(width, height, depth)
{

}

CBox::CBox(const CBox& copy) :
	CPoint3D(copy.position()), CSize3D(copy.size())
{

}

CBox::CBox(const CPoint3D& position, const CSize3D& size) :
	CPoint3D(position), CSize3D(size)
{

}

CBox::CBox(float x, float y, float z, const CSize3D& size) :
	CPoint3D(x, y), CSize3D(size)
{

}

bool CBox::pointInBox(const CPoint3D& point) const
{
	return ((point.x() >= x()) && (point.x() <= x() + width()) &&
			 (point.y() >= y()) && (point.y() <= y() + height()) &&
 			 (point.z() >= z()) && (point.z() <= z() + depth()));
}

//#pragma mark -

CSize3D CBox::size() const
{
	return CSize3D(*this);
}

void CBox::size(const CSize3D& Size)
{
	CSize3D::operator=(Size);
}

CPoint3D CBox::position() const
{
	return CPoint3D(*this);
}

void CBox::position(const CPoint3D& point)
{
	CPoint2D::operator=(point);
}

void CBox::position(float X, float Y, float Z)
{
	x(X);
	y(Y);
	z(Z);
}

//#pragma mark -

CBox& CBox::operator=(const CBox& copy)
{
	CPoint3D::operator=(copy);
	CSize3D::operator=(copy);
	return *this;
}

bool CBox::operator==(const CBox& rect) const
{
	return (CPoint3D::operator==(rect) && CSize3D::operator==(rect));
}

bool CBox::operator!=(const CBox& rect) const
{
	return !(operator==(rect));
}

	} // namespace le
} // namespace sokira
