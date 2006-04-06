#include "Types.h"

#include "glut/glut.h"



////////////////////////////////////////////////////////////////////////////////
//#pragma mark -- CPoint --
////////////////////////////////////////////////////////////////////////////////

CPoint::CPoint(float x, float y) :
	mX(x), mY(y)
{

}

CPoint::CPoint(const CPoint& copy) :
	mX(copy.mX), mY(copy.mY)
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

//#pragma mark -

// Operators
CPoint& CPoint::operator=(const CPoint& copy)
{
	mX = copy.mX;
	mY = copy.mY;
	return *this;
}

bool CPoint::operator==(const CPoint& point) const
{
	return ((mX == point.mX) && (mY == point.mY));
}

bool CPoint::operator!=(const CPoint& point) const
{
	return !(operator==(point));
}

//#pragma mark -

void CPoint::draw() const
{
	glVertex2f(mX, mY);
}


//#pragma mark
////////////////////////////////////////////////////////////////////////////////
//#pragma mark -- CSize --
////////////////////////////////////////////////////////////////////////////////


CSize::CSize(float width, float height) :
	mWidth(width), mHeight(height)
{

}

CSize::CSize(const CSize& copy) :
	mWidth(copy.mWidth), mHeight(copy.mHeight)
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

//#pragma mark -

// Operators
CSize& CSize::operator=(const CSize& copy)
{
	mWidth = copy.mWidth;
	mHeight = copy.mHeight;
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
	CPoint(x, y), CSize(width, height)
{

}


CRectangle::CRectangle(const CPoint& position, float width, float height) :
	CPoint(position), CSize(width, height)
{

}

CRectangle::CRectangle(const CRectangle& copy) :
	CPoint(copy.position()), CSize(copy.size())
{

}

CRectangle::CRectangle(const CPoint& position, const CSize& size) :
	CPoint(position), CSize(size)
{

}

CRectangle::CRectangle(float x, float y, const CSize& size) :
	CPoint(x, y), CSize(size)
{

}

//#pragma mark -

CPoint CRectangle::topLeft() const
{
	return CPoint(*this);
}

CPoint CRectangle::topRight() const
{
	return CPoint(x() + width(), y()); 
}

CPoint CRectangle::bottomLeft() const
{
	return CPoint(x(), y() + height());
}

CPoint CRectangle::bottomRight() const
{
	return CPoint(x() + width(), y() + height());
}

bool CRectangle::pointInRect(const CPoint& point) const
{
	return ((point.x() >= x()) && (point.x() <= x() + width()) &&
			 (point.y() >= y()) && (point.y() <= y() + height()));
}

//#pragma mark -

CSize CRectangle::size() const
{
	return CSize(*this);
}

void CRectangle::size(const CSize& Size)
{
	CSize::operator=(Size);
}

CPoint CRectangle::position() const
{
	return CPoint(*this);
}

void CRectangle::position(const CPoint& point)
{
	CPoint::operator=(point);
}

void CRectangle::position(float X, float Y)
{
	x(X);
	y(Y);
}

//#pragma mark -

CRectangle& CRectangle::operator=(const CRectangle& copy)
{
	CPoint::operator=(copy);
	CSize::operator=(copy);
	return *this;
}

bool CRectangle::operator==(const CRectangle& rect) const
{
	return (CPoint::operator==(rect) && CSize::operator==(rect));
}

bool CRectangle::operator!=(const CRectangle& rect) const
{
	return !(operator==(rect));
}

//#pragma mark -

// Draw
void CRectangle::draw() const
{
	glRectf(x(), y(), x() + width(), y() + height());
}

void CRectangle::drawWire() const
{
	glBegin(GL_LINE_STRIP);
	 glVertex2f(x(), y());
	 glVertex2f(x() + width(), y());
	 glVertex2f(x() + width(), y() + height());
	 glVertex2f(x(), y() + height());
	 glVertex2f(x(), y());
	glEnd();
}

//#pragma mark
////////////////////////////////////////////////////////////////////////////////
//#pragma mark -- CColor --
////////////////////////////////////////////////////////////////////////////////
CColor::CColor(float red, float green, float blue) :
	mRed(red), mGreen(green), mBlue(blue)
{

}

CColor::CColor(const CColor& copy) :
	mRed(copy.mRed), mGreen(copy.mGreen), mBlue(copy.mBlue)
{

}

//#pragma mark -
// Attributes
float CColor::red() const
{
	return mRed;
}

void CColor::red(float Red)
{
	mRed = Red;
}

float CColor::green() const
{
	return mGreen;
}

void CColor::green(float Green)
{
	mGreen = Green;
}

float CColor::blue() const
{
	return mBlue;
}

void CColor::blue(float Blue)
{
	mBlue = Blue;
}

//#pragma mark -
// Operators
CColor& CColor::operator=(const CColor& copy)
{
	mRed = copy.mRed;
	mGreen = copy.mGreen;
	mBlue = copy.mBlue;
	return *this;
}

bool CColor::operator==(const CColor& color) const
{
	return ((mRed == color.mRed) && (mGreen == color.mGreen) && (mBlue == color.mBlue));
}

bool CColor::operator!=(const CColor& color) const
{
	return !(operator==(color));
}

//#pragma mark -
// Set
void CColor::set() const
{
	glColor3f(mRed, mGreen, mBlue);
}