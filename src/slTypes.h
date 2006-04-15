#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

////////////////////////////////////////////////////////////////////////////////
// CPoint
////////////////////////////////////////////////////////////////////////////////
class CPoint
{
	// Construction
	public:
		CPoint(float x = 0.0, float y = 0.0, float z = 0.0);
		CPoint(const CPoint& copy);

	// Attributes
		float x() const;
		void x(float X);

		float y() const;
		void y(float Y);

		float z() const;
		void z(float Z);
		
	// Operators
		CPoint& operator=(const CPoint& copy);
		bool operator==(const CPoint& point) const;
		bool operator!=(const CPoint& point) const;

	// Draw
		void draw() const;

	// Members
	private:
		float mX, mY, mZ;
};

typedef CPoint CPoint2D;
typedef CPoint CPoint3D;

////////////////////////////////////////////////////////////////////////////////
// CSize
////////////////////////////////////////////////////////////////////////////////
class CSize
{
	// Construction
	public:
		CSize(float width = 0.0, float height = 0.0, float depth = 0.0);
		CSize(const CSize& copy);

	// Attributes
		float width() const;
		void width(float Width);

		float height() const;
		void height(float Height);

		float depth() const;
		void depth(float depth);

	// Operators
		CSize& operator=(const CSize& copy);
		bool operator==(const CSize& size) const;
		bool operator!=(const CSize& size) const;

	// Members
	private:
		float mWidth, mHeight, mDepth;
};

typedef CSize CSize2D;
typedef CSize CSize3D;

////////////////////////////////////////////////////////////////////////////////
// CRectangle
////////////////////////////////////////////////////////////////////////////////
class CRectangle : public CPoint2D, public CSize2D
{
	// Construction
	public:
		CRectangle(float x = 0.0, float y = 0.0, float width = 0.0, float height = 0.0);
		CRectangle(const CPoint2D& position, float width = 0.0, float height = 0.0);
		CRectangle(const CPoint2D& position, const CSize2D& size);
		CRectangle(float x, float y, const CSize2D& size);
		CRectangle(const CRectangle& copy);

	// Attributes

		CPoint2D topLeft() const;
		CPoint2D topRight() const;
		CPoint2D bottomLeft() const;
		CPoint2D bottomRight() const;

		bool pointInRect(const CPoint2D& point) const;

		CSize2D size() const;
		void size(const CSize2D& Size);

		CPoint2D position() const;
		void position(const CPoint2D& point);
		void position(float x, float y);

	// Operators
		CRectangle& operator=(const CRectangle& copy);
		bool operator==(const CRectangle& rect) const;
		bool operator!=(const CRectangle& rect) const;

	// Draw
		void draw() const;
		void drawWire() const;
};

////////////////////////////////////////////////////////////////////////////////
// CBox
////////////////////////////////////////////////////////////////////////////////
class CBox : public CPoint3D, public CSize3D
{
	// Construction
	public:
		CBox(float x = 0.0, float y = 0.0, float z = 0.0, float width = 0.0, float height = 0.0, float depth = 0.0);
		CBox(const CPoint3D& position, float width = 0.0, float height = 0.0, float depth = 0.0);
		CBox(const CPoint3D& position, const CSize3D& size);
		CBox(float x, float y, float z, const CSize3D& size);
		CBox(const CBox& copy);

		bool pointInBox(const CPoint3D& point) const;

		CSize3D size() const;
		void size(const CSize2D& Size);

		CPoint3D position() const;
		void position(const CPoint3D& point);
		void position(float x, float y, float z);

	// Operators
		CBox& operator=(const CBox& copy);
		bool operator==(const CBox& rect) const;
		bool operator!=(const CBox& rect) const;

	// Draw
		void draw() const;
		void drawWire() const;
};


////////////////////////////////////////////////////////////////////////////////
// CColor
////////////////////////////////////////////////////////////////////////////////
class CColor
{
	// Construction:
	public:
		CColor(float red = 1.0, float green = 1.0, float blue = 1.0);
		CColor(const CColor& copy);

	// Attributes
		float red() const;
		void red(float Red);

		float green() const;
		void green(float Green);

		float blue() const;
		void blue(float Blue);

	// Operators
		CColor& operator=(const CColor& copy);
		bool operator==(const CColor& color) const;
		bool operator!=(const CColor& color) const;

	// Set
		void set() const;

	// Members
	public:
		float mRed, mGreen, mBlue;
};


LE_NAMESPACE_END
