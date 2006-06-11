#include "slCCastPolicyRegistry.h"
#include <common/types/slCNumber.h>
#include <common/types/slCString.h>
#include <math.h>

template <typename From, typename To>
class CCastPolicy : public ICastPolicy
{
	protected:
		virtual void* _performCast(const void* from) const
		{
			return static_cast<void*>(new To(performCast(*static_cast<const From*>(from))));
		}

		virtual To performCast(const From& from) const = 0;
};

template <typename From, typename To>
class CTtrivialCastPolicy : public CCastPolicy<From, To>
{
	protected:
		virtual To performCast(const From& from) const
		{
			return To(static_cast<To>(from));
		}
};

template <typename From, typename To>
class COnConstructorCastPolicy : public CCastPolicy<From, To>
{
	protected:
		virtual To performCast(const From& from) const
		{
			return To(from);
		}
};

template <typename To>
class CNumberCastPolicy : public CCastPolicy<CNumber, To>
{
	protected:
		virtual To performCast(const CNumber& from) const
		{
			return from.valueAs<To>();
		}
};

template <typename To>
class CStringToNumberCastPolicy : public CCastPolicy<CString, To>
{
	protected:
		virtual To performCast(const CString& from) const
		{
			return CNumber(from).valueAs<To>();
		}
};

template <typename From>
class CNumericToStringCastPolicy : public CCastPolicy<From, CString>
{
	protected:
		virtual CString performCast(const From& from) const
		{
			return CNumber(from).valueAsString();
		}
};

CCastPolicyRegistry::CCastPolicyRegistry()
{
	////////////////////////////////////////////////////////////////////////////////
	// Cast Policies
	////////////////////////////////////////////////////////////////////////////////
	#define DECLARE_TRIVIAL_CONVERTER(fromType, toType)									\
	mPolicyMap[CString(typeid(fromType).name())][CString(typeid(toType).name())] =\
		new CTtrivialCastPolicy<fromType, toType>();

	#define DECLARE_ON_CONSTRUCTOR_CONVERTER(fromType, toType)							\
	mPolicyMap[CString(typeid(fromType).name())][CString(typeid(toType).name())] =\
		new COnConstructorCastPolicy<fromType, toType>();

	#define DECLARE_NUMERIC_TO_STRING_CONVERTER(fromType)									\
	mPolicyMap[CString(typeid(fromType).name())][CString(typeid(CString).name())] =\
		new CNumericToStringCastPolicy<fromType>();

	DECLARE_TRIVIAL_CONVERTER(SInt1, SInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt1, SInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt1, SInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt1, UInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt1, UInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt1, UInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt1, UInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt1, Float4);
	DECLARE_TRIVIAL_CONVERTER(SInt1, Float8);

	DECLARE_TRIVIAL_CONVERTER(SInt1, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt1, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt1);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt2, SInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt2, SInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt2, SInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt2, UInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt2, UInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt2, UInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt2, UInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt2, Float4);
	DECLARE_TRIVIAL_CONVERTER(SInt2, Float8);

	DECLARE_TRIVIAL_CONVERTER(SInt2, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt2, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt2);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt4, SInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt4, SInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt4, SInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt4, UInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt4, UInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt4, UInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt4, UInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt4, Float4);
	DECLARE_TRIVIAL_CONVERTER(SInt4, Float8);

	DECLARE_TRIVIAL_CONVERTER(SInt4, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt4, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt4);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt4);

	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt1);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt2);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt4);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt8);

	DECLARE_TRIVIAL_CONVERTER(SInt8, Float4);
	DECLARE_TRIVIAL_CONVERTER(SInt8, Float8);

	DECLARE_TRIVIAL_CONVERTER(SInt8, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt8, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt8);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt1, SInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt1, SInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt1, SInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt1, SInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt1, UInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt1, UInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt1, UInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt1, Float4);
	DECLARE_TRIVIAL_CONVERTER(UInt1, Float8);

	DECLARE_TRIVIAL_CONVERTER(UInt1, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt1, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt1);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt2, SInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt2, SInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt2, SInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt2, SInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt2, UInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt2, UInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt2, UInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt2, Float4);
	DECLARE_TRIVIAL_CONVERTER(UInt2, Float8);

	DECLARE_TRIVIAL_CONVERTER(UInt2, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt2, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt2);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt4, SInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt4, SInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt4, SInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt4, SInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt4, UInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt4, UInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt4, UInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt4, Float4);
	DECLARE_TRIVIAL_CONVERTER(UInt4, Float8);

	DECLARE_TRIVIAL_CONVERTER(UInt4, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt4, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt4);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt4);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt8);

	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt1);
	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt2);
	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt4);

	DECLARE_TRIVIAL_CONVERTER(UInt8, Float4);
	DECLARE_TRIVIAL_CONVERTER(UInt8, Float8);

	DECLARE_TRIVIAL_CONVERTER(UInt8, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt8, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt8);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(Bool, SInt1);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt2);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt4);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt8);

	DECLARE_TRIVIAL_CONVERTER(Bool, UInt1);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt2);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt4);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt8);

	DECLARE_TRIVIAL_CONVERTER(Bool, Float4);
	DECLARE_TRIVIAL_CONVERTER(Bool, Float8);

	DECLARE_TRIVIAL_CONVERTER(Bool, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Bool, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Bool);

	/////////////////////////////////////////////////////////////////////////////
	//	Floats are rounded, when casted to ints.
	/////////////////////////////////////////////////////////////////////////////
	#define DECLARE_ROUND_FLOATS_CONVERTER(fromType, toType, roundFunc)			\
	class CRound##fromType##To##toType##CastingPolicy :										\
		public CCastPolicy<fromType, toType>														\
	{																											\
		protected:																							\
			virtual toType performCast(const fromType& from) const							\
			{																									\
				return toType(static_cast<toType>(roundFunc(from)));							\
			}																									\
	};																											\
	mPolicyMap[CString(typeid(fromType).name())][CString(typeid(toType).name())] =\
		new CRound##fromType##To##toType##CastingPolicy();

	DECLARE_ROUND_FLOATS_CONVERTER(Float4, SInt1, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, SInt2, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, SInt4, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, SInt8, llroundf);

	DECLARE_ROUND_FLOATS_CONVERTER(Float4, UInt1, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, UInt2, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, UInt4, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float4, UInt8, llroundf);

	DECLARE_TRIVIAL_CONVERTER(Float4, Float8);

	DECLARE_TRIVIAL_CONVERTER(Float4, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Float4, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Float4);
	/////////////////////////////////////////////////////////////////////////////

	DECLARE_ROUND_FLOATS_CONVERTER(Float8, SInt1, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, SInt2, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, SInt4, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, SInt8, llround);

	DECLARE_ROUND_FLOATS_CONVERTER(Float8, UInt1, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, UInt2, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, UInt4, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float8, UInt8, llround);

	DECLARE_TRIVIAL_CONVERTER(Float8, Float4);

	DECLARE_TRIVIAL_CONVERTER(Float8, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Float8, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Float8);

	/////////////////////////////////////////////////////////////////////////////
	// CNumbers are casted in their own way
	/////////////////////////////////////////////////////////////////////////////

	#define DECLARE_CNUMBER_CONVERTER(toType)												\
	mPolicyMap[CString(typeid(CNumber).name())][CString(typeid(toType).name())] =\
		new CNumberCastPolicy<toType>();

	DECLARE_CNUMBER_CONVERTER(SInt1);
	DECLARE_CNUMBER_CONVERTER(SInt2);
	DECLARE_CNUMBER_CONVERTER(SInt4);
	DECLARE_CNUMBER_CONVERTER(SInt8);

	DECLARE_CNUMBER_CONVERTER(UInt1);
	DECLARE_CNUMBER_CONVERTER(UInt2);
	DECLARE_CNUMBER_CONVERTER(UInt4);
	DECLARE_CNUMBER_CONVERTER(UInt8);

	DECLARE_CNUMBER_CONVERTER(Float4);
	DECLARE_CNUMBER_CONVERTER(Float8);

	DECLARE_CNUMBER_CONVERTER(CString);

	DECLARE_CNUMBER_CONVERTER(Bool);

	/////////////////////////////////////////////////////////////////////////////
	// CStrings are casted in their own way
	/////////////////////////////////////////////////////////////////////////////

	#define DECLARE_CSTRING_CONVERTER(toType)												\
	mPolicyMap[CString(typeid(CNumber).name())][CString(typeid(toType).name())] =\
		new CStringToNumberCastPolicy<toType>();

	DECLARE_CSTRING_CONVERTER(SInt1);
	DECLARE_CSTRING_CONVERTER(SInt2);
	DECLARE_CSTRING_CONVERTER(SInt4);
	DECLARE_CSTRING_CONVERTER(SInt8);

	DECLARE_CSTRING_CONVERTER(UInt1);
	DECLARE_CSTRING_CONVERTER(UInt2);
	DECLARE_CSTRING_CONVERTER(UInt4);
	DECLARE_CSTRING_CONVERTER(UInt8);

	DECLARE_CSTRING_CONVERTER(Float4);
	DECLARE_CSTRING_CONVERTER(Float8);

	DECLARE_CSTRING_CONVERTER(Bool);
	DECLARE_ON_CONSTRUCTOR_CONVERTER(CString, CNumber);

	#undef DECLARE_TRIVIAL_CONVERTER
	#undef DECLARE_ROUND_FLOATS_CONVERTER
	#undef DECLARE_ON_CONSTRUCTOR_CONVERTER
	#undef DECLARE_CNUMBER_CONVERTER
	#undef DECLARE_NUMERIC_TO_STRING_CONVERTER
	#undef DECLARE_CSTRING_CONVERTER
}

LE_NAMESPACE_END
