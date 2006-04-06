#pragma once


////////////////////////////////////////////////////////////////////////////////
// CPoint
////////////////////////////////////////////////////////////////////////////////
class CPoint
{
	// Construction
	public:
		CPoint(float x = 0.0, float y = 0.0);
		CPoint(const CPoint& copy);

	// Attributes
		float x() const;
		void x(float X);

		float y() const;
		void y(float Y);

	// Operators
		CPoint& operator=(const CPoint& copy);
		bool operator==(const CPoint& point) const;
		bool operator!=(const CPoint& point) const;

	// Draw
		void draw() const;

	// Members
	private:
		float mX, mY;
};


////////////////////////////////////////////////////////////////////////////////
// CSize
////////////////////////////////////////////////////////////////////////////////
class CSize
{
	// Construction
	public:
		CSize(float width = 0.0, float height = 0.0);
		CSize(const CSize& copy);

	// Attributes
		float width() const;
		void width(float Width);

		float height() const;
		void height(float Height);

	// Operators
		CSize& operator=(const CSize& copy);
		bool operator==(const CSize& size) const;
		bool operator!=(const CSize& size) const;

	// Members
	private:
		float mWidth, mHeight;
};


////////////////////////////////////////////////////////////////////////////////
// CRectangle
////////////////////////////////////////////////////////////////////////////////
class CRectangle : public CPoint, public CSize
{
	// Construction
	public:
		CRectangle(float x = 0.0, float y = 0.0, float width = 0.0, float height = 0.0);
		CRectangle(const CPoint& position, float width = 0.0, float height = 0.0);
		CRectangle(const CPoint& position, const CSize& size);
		CRectangle(float x, float y, const CSize& size);
		CRectangle(const CRectangle& copy);

	// Attributes

		CPoint topLeft() const;
		CPoint topRight() const;
		CPoint bottomLeft() const;
		CPoint bottomRight() const;

		bool pointInRect(const CPoint& point) const;

		CSize size() const;
		void size(const CSize& Size);

		CPoint position() const;
		void position(const CPoint& point);
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