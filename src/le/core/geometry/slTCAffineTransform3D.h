#if !defined SL_LE_core_geometry_slTCAffinetransform3D_h
#define SL_LE_core_geometry_slTCAffinetransform3D_h

#ifdef __SSE__
#include <xmmintrin.h>
#define LE_USE_SSE
#endif

#include <string.h>
#include "slTCPoint3D.h"

namespace sokira
{
	namespace le
	{

class CAffineTransform3D
{
	public:
		void setIdentity()
		{
#ifdef LE_USE_SSE
			Float32 v[] = { 0, 0, 0, 1, 0, 0, 0 };
			m0 = _mm_loadu_ps(v + 3);
			m1 = _mm_loadu_ps(v + 2);
			m2 = _mm_loadu_ps(v + 1);
			m3 = _mm_loadu_ps(v);
#else
			m[0] = 1; m[4] = 0; m[ 8] = 0; m[12] = 0;
			m[1] = 0; m[5] = 1; m[ 9] = 0; m[13] = 0;
			m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
			m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
#endif
		}

		void translate(Float32 x, Float32 y, Float32 z)
		{
#ifdef LE_USE_SSE
			m3 = _mm_add_ps(m3, _mm_add_ps(_mm_mul_ps(m2, _mm_set_ps1(z)), _mm_add_ps(_mm_mul_ps(m1, _mm_set_ps1(y)), _mm_mul_ps(m0, _mm_set_ps1(x)))));
#else
			m[12] += x * m[ 0] + y * m[ 4] + z * m[ 8];
			m[13] += x * m[ 1] + y * m[ 5] + z * m[ 9];
			m[14] += x * m[ 2] + y * m[ 6] + z * m[10];
			m[15] += x * m[ 3] + y * m[ 7] + z * m[11];
#endif
		}

		void rotate(Float32 x, Float32 y, Float32 z)
		{
			const Float32 A = cosf(x), B = sinf(x), C = cosf(y),
			D = sinf(y), E = cosf(z), F = sinf(z);
			const Float32 AD = A * D, BD = B * D;

			const Float32 A00 = C * E;
			const Float32 A01 = BD * E + A * F;
			const Float32 A02 = -AD * E + B * F;

			const Float32 A04 = -C * F;
			const float A05 = -BD * F + A * E;
			const float A06 = AD * F + B * E;

			const float A09 = -B * C;
			const float A10 = A * C;

#ifdef LE_USE_SSE
			__m128 b0003 = m0;
			__m128 b0407 = m1;
			__m128 b0811 = m2;

			m0 = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(A00), b0003), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(A01), b0407), _mm_mul_ps(_mm_set_ps1(A02), b0811)));
			m1 = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(A04), b0003), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(A05), b0407), _mm_mul_ps(_mm_set_ps1(A06), b0811)));
			m2 = _mm_add_ps(_mm_mul_ps(_mm_set_ps1(  D), b0003), _mm_add_ps(_mm_mul_ps(_mm_set_ps1(A09), b0407), _mm_mul_ps(_mm_set_ps1(A10), b0811)));
#else
			const Float32 b00 = m[0];
			const Float32 b01 = m[1];
			const Float32 b02 = m[2];
			const Float32 b03 = m[3];
			const Float32 b04 = m[4];
			const Float32 b05 = m[5];
			const Float32 b06 = m[6];
			const Float32 b07 = m[7];
			const Float32 b08 = m[8];
			const Float32 b09 = m[9];
			const Float32 b10 = m[10];
			const Float32 b11 = m[11];

			m[ 0] = A00 * b00 + A01 * b04 + A02 * b08;
			m[ 1] = A00 * b01 + A01 * b05 + A02 * b09;
			m[ 2] = A00 * b02 + A01 * b06 + A02 * b10;
			m[ 3] = A00 * b03 + A01 * b07 + A02 * b11;
			m[ 4] = A04 * b00 + A05 * b04 + A06 * b08;
			m[ 5] = A04 * b01 + A05 * b05 + A06 * b09;
			m[ 6] = A04 * b02 + A05 * b06 + A06 * b10;
			m[ 7] = A04 * b03 + A05 * b07 + A06 * b11;
			m[ 8] = D * b00 + A09 * b04 + A10 * b08;
			m[ 9] = D * b01 + A09 * b05 + A10 * b09;
			m[10] = D * b02 + A09 * b06 + A10 * b10;
			m[11] = D * b03 + A09 * b07 + A10 * b11;
#endif
		}

		void scale(Float32 x, Float32 y, Float32 z)
		{
#ifdef LE_USE_SSE
			__m128 v = _mm_set_ps(1, z, y, x);
			m0 = _mm_mul_ps(m0, v);
			m1 = _mm_mul_ps(m1, v);
			m2 = _mm_mul_ps(m2, v);
			m3 = _mm_mul_ps(m3, v);
#else
			m[ 0] *= x; m[ 4] *= x; m[ 8] *= x; m[12] *= x;
			m[ 1] *= y; m[ 5] *= y; m[ 9] *= y; m[13] *= y;
			m[ 2] *= z; m[ 6] *= z; m[10] *= z; m[14] *= z;
#endif
		}

		void ortho(Float32 left, Float32 right,
				  Float32 bottom, Float32 top,
				  Float32 zNear, Float32 zFar)
		{
			CAffineTransform3D o;
			o.setOrtho(left, right, bottom, top, zNear, zFar);
			*this *= o;
		}

		void transpose()
		{
#ifdef LE_USE_SSE
			_MM_TRANSPOSE4_PS(m0, m1, m2, m3);
#else
			std::swap(m[4], m[1]);
			std::swap(m[8], m[2]);
			std::swap(m[12], m[3]);
			std::swap(m[9], m[6]);
			std::swap(m[13], m[7]);
			std::swap(m[14], m[11]);
#endif
		}

		void setTranslation(Float32 x, Float32 y, Float32 z)
		{
#ifdef LE_USE_SSE
			m0 = _mm_set_ps(0, 0, 0, 1);
			m1 = _mm_set_ps(0, 0, 1, 0);
			m2 = _mm_set_ps(0, 1, 0, 0);
			m3 = _mm_set_ps(1, z, y, x);
#else
			m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = x;
			m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = y;
			m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = z;
			m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
#endif
		}

		void setRotation(Float32 x, Float32 y, Float32 z)
		{
			const Float32 A = cosf(x), B = sinf(x), C = cosf(y),
			D = sinf(y), E = cosf(z), F = sinf(z);
			const Float32 AD = A * D, BD = B * D;

#ifdef LE_USE_SSE
			m0 = _mm_set_ps(0,	-AD * E + B * F,	BD * E + A * F,		C * E);
			m1 = _mm_set_ps(0,	AD * F + B * E,		-BD * F + A * E,	-C * F);
			m2 = _mm_set_ps(0,	A * C,				-B * C,				D);
			m3 = _mm_set_ps(1,	0,					0,					0);
#else
			m[ 0] = C * E;				m[ 4] = -C * F;				m[ 8] = D;		m[12] = 0;
			m[ 1] = BD * E + A * F;		m[ 5] = -BD * F + A * E;	m[ 9] = -B * C;	m[13] = 0;
			m[ 2] = -AD * E + B * F;	m[ 6] = AD * F + B * E;		m[10] = A * C;	m[14] = 0;
			m[ 3] = 0;					m[ 7] = 0;					m[11] = 0;		m[15] = 1;
#endif
		}

		void setScale(Float32 x, Float32 y, Float32 z)
		{
#ifdef LE_USE_SSE
			m0 = _mm_set_ps(0, 0, 0, x);
			m1 = _mm_set_ps(0, 0, y, 0);
			m2 = _mm_set_ps(0, z, 0, 0);
			m3 = _mm_set_ps(1, 0, 0, 0);
#else
			m[ 0] = x; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
			m[ 1] = 0; m[ 5] = y; m[ 9] = 0; m[13] = 0;
			m[ 2] = 0; m[ 6] = 0; m[10] = z; m[14] = 0;
			m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
#endif
		}

		void setOrtho(Float32 left, Float32 right,
					  Float32 bottom, Float32 top,
					  Float32 zNear, Float32 zFar)
		{
			const Float32 width = right - left;
			const Float32 height = top - bottom;
			const Float32 depth = zFar - zNear;

			m[ 0] = 2.0f / width;	m[ 4] = 0;				m[ 8] = 0;				m[12] = - (right + left) / width;
			m[ 1] = 0;				m[ 5] = 2.0f / height;	m[ 9] = 0;				m[13] = - (top + bottom) / height;
			m[ 2] = 0;				m[ 6] = 0;				m[10] = -2.0f / depth;	m[14] = - (zFar + zNear) / depth;
			m[ 3] = 0;				m[ 7] = 0;				m[11] = 0;				m[15] = 1;
		}

		void dump(std::ostream& stream) const
		{
			stream << m[ 0] << ", " << m[ 4] << ", " << m[ 8] << ", " << m[12] << std::endl;
			stream << m[ 1] << ", " << m[ 5] << ", " << m[ 9] << ", " << m[13] << std::endl;
			stream << m[ 2] << ", " << m[ 6] << ", " << m[10] << ", " << m[14] << std::endl;
			stream << m[ 3] << ", " << m[ 7] << ", " << m[11] << ", " << m[15] << std::endl;
		}

		void operator *= (const CAffineTransform3D& rhs)
		{
			CAffineTransform3D copy = *this;
			multiply(copy, rhs, *this);
		}

		static void multiply(const CAffineTransform3D& a, const CAffineTransform3D& b, CAffineTransform3D& r)
		{
#ifdef LE_USE_SSE
			r.m0 = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 0]), b.m0), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 1]), b.m1), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 2]), b.m2), _mm_mul_ps(_mm_set1_ps(a.m[ 3]), b.m3))));
			r.m1 = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 4]), b.m0), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 5]), b.m1), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 6]), b.m2), _mm_mul_ps(_mm_set1_ps(a.m[ 7]), b.m3))));
			r.m2 = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 8]), b.m0), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[ 9]), b.m1), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[10]), b.m2), _mm_mul_ps(_mm_set1_ps(a.m[11]), b.m3))));
			r.m3 = _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[12]), b.m0), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[13]), b.m1), _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m[14]), b.m2), _mm_mul_ps(_mm_set1_ps(a.m[15]), b.m3))));
#else
			r.m[ 0] = a.m[ 0] * b.m[ 0] + a.m[ 1] * b.m[ 4] + a.m[ 2] * b.m[ 8] + a.m[ 3] * b.m[12];
			r.m[ 1] = a.m[ 0] * b.m[ 1] + a.m[ 1] * b.m[ 5] + a.m[ 2] * b.m[ 9] + a.m[ 3] * b.m[13];
			r.m[ 2] = a.m[ 0] * b.m[ 2] + a.m[ 1] * b.m[ 6] + a.m[ 2] * b.m[10] + a.m[ 3] * b.m[14];
			r.m[ 3] = a.m[ 0] * b.m[ 3] + a.m[ 1] * b.m[ 7] + a.m[ 2] * b.m[11] + a.m[ 3] * b.m[15];
			r.m[ 4] = a.m[ 4] * b.m[ 0] + a.m[ 5] * b.m[ 4] + a.m[ 6] * b.m[ 8] + a.m[ 7] * b.m[12];
			r.m[ 5] = a.m[ 4] * b.m[ 1] + a.m[ 5] * b.m[ 5] + a.m[ 6] * b.m[ 9] + a.m[ 7] * b.m[13];
			r.m[ 6] = a.m[ 4] * b.m[ 2] + a.m[ 5] * b.m[ 6] + a.m[ 6] * b.m[10] + a.m[ 7] * b.m[14];
			r.m[ 7] = a.m[ 4] * b.m[ 3] + a.m[ 5] * b.m[ 7] + a.m[ 6] * b.m[11] + a.m[ 7] * b.m[15];
			r.m[ 8] = a.m[ 8] * b.m[ 0] + a.m[ 9] * b.m[ 4] + a.m[10] * b.m[ 8] + a.m[11] * b.m[12];
			r.m[ 9] = a.m[ 8] * b.m[ 1] + a.m[ 9] * b.m[ 5] + a.m[10] * b.m[ 9] + a.m[11] * b.m[13];
			r.m[10] = a.m[ 8] * b.m[ 2] + a.m[ 9] * b.m[ 6] + a.m[10] * b.m[10] + a.m[11] * b.m[14];
			r.m[11] = a.m[ 8] * b.m[ 3] + a.m[ 9] * b.m[ 7] + a.m[10] * b.m[11] + a.m[11] * b.m[15];
			r.m[12] = a.m[12] * b.m[ 0] + a.m[13] * b.m[ 4] + a.m[14] * b.m[ 8] + a.m[15] * b.m[12];
			r.m[13] = a.m[12] * b.m[ 1] + a.m[13] * b.m[ 5] + a.m[14] * b.m[ 9] + a.m[15] * b.m[13];
			r.m[14] = a.m[12] * b.m[ 2] + a.m[13] * b.m[ 6] + a.m[14] * b.m[10] + a.m[15] * b.m[14];
			r.m[15] = a.m[12] * b.m[ 3] + a.m[13] * b.m[ 7] + a.m[14] * b.m[11] + a.m[15] * b.m[15];
#endif
		}

	private:
		union
		{
#ifdef LE_USE_SSE
			struct
			{
				__m128 m0;
				__m128 m1;
				__m128 m2;
				__m128 m3;
			};
#endif
			Float32 m[16];
		};
};

static inline std::ostream& operator << (std::ostream& stream, const CAffineTransform3D& transform)
{
	transform.dump(stream);
	return stream;
}

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_geometry_slTCAffinetransform3D_h
