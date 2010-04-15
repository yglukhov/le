#if !defined SL_LE_gui_slTypes_h
#define SL_LE_gui_slTypes_h

#include <le/core/geometry/slTCPoint3D.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// CSize
////////////////////////////////////////////////////////////////////////////////
class CSize3D
{
	// Construction
	public:
		CSize3D(float width = 0.0, float height = 0.0, float depth = 0.0);
		CSize3D(const CSize3D& copy);

	// Attributes
		float width() const;
		void width(float Width);

		float height() const;
		void height(float Height);

		float depth() const;
		void depth(float depth);

	// Operators
		CSize3D& operator=(const CSize3D& copy);
		bool operator==(const CSize3D& size) const;
		bool operator!=(const CSize3D& size) const;

	// Members
	private:
		float mWidth, mHeight, mDepth;
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
		void size(const CSize3D& Size);

		CPoint3D position() const;
		void position(const CPoint3D& point);
		void position(float x, float y, float z);

	// Operators
		CBox& operator=(const CBox& copy);
		bool operator==(const CBox& box) const;
		bool operator!=(const CBox& box) const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slTypes_h
