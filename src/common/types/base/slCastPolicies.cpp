#include "slCCastPolicyRegistry.h"
#include <common/types/slCNumber.h>
#include <common/types/slCString.h>
//#include <cmath>

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

	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt8, SInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt8, UInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt8, Float32);
	DECLARE_TRIVIAL_CONVERTER(SInt8, Float64);

	DECLARE_TRIVIAL_CONVERTER(SInt8, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt8, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt8);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt16, SInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt16, SInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt16, SInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt16, UInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt16, UInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt16, UInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt16, UInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt16, Float32);
	DECLARE_TRIVIAL_CONVERTER(SInt16, Float64);

	DECLARE_TRIVIAL_CONVERTER(SInt16, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt16, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt16);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt32, SInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt32, SInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt32, SInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt32, UInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt32, UInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt32, UInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt32, UInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt32, Float32);
	DECLARE_TRIVIAL_CONVERTER(SInt32, Float64);

	DECLARE_TRIVIAL_CONVERTER(SInt32, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt32, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt32);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(SInt64, SInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt64, SInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt64, SInt32);

	DECLARE_TRIVIAL_CONVERTER(SInt64, UInt8);
	DECLARE_TRIVIAL_CONVERTER(SInt64, UInt16);
	DECLARE_TRIVIAL_CONVERTER(SInt64, UInt32);
	DECLARE_TRIVIAL_CONVERTER(SInt64, UInt64);

	DECLARE_TRIVIAL_CONVERTER(SInt64, Float32);
	DECLARE_TRIVIAL_CONVERTER(SInt64, Float64);

	DECLARE_TRIVIAL_CONVERTER(SInt64, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(SInt64, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(SInt64);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt8, SInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt8, UInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt8, Float32);
	DECLARE_TRIVIAL_CONVERTER(UInt8, Float64);

	DECLARE_TRIVIAL_CONVERTER(UInt8, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt8, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt8);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt16, SInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt16, SInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt16, SInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt16, SInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt16, UInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt16, UInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt16, UInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt16, Float32);
	DECLARE_TRIVIAL_CONVERTER(UInt16, Float64);

	DECLARE_TRIVIAL_CONVERTER(UInt16, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt16, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt16);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt32, SInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt32, SInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt32, SInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt32, SInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt32, UInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt32, UInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt32, UInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt32, Float32);
	DECLARE_TRIVIAL_CONVERTER(UInt32, Float64);

	DECLARE_TRIVIAL_CONVERTER(UInt32, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt32, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt32);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(UInt64, SInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt64, SInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt64, SInt32);
	DECLARE_TRIVIAL_CONVERTER(UInt64, SInt64);

	DECLARE_TRIVIAL_CONVERTER(UInt64, UInt8);
	DECLARE_TRIVIAL_CONVERTER(UInt64, UInt16);
	DECLARE_TRIVIAL_CONVERTER(UInt64, UInt32);

	DECLARE_TRIVIAL_CONVERTER(UInt64, Float32);
	DECLARE_TRIVIAL_CONVERTER(UInt64, Float64);

	DECLARE_TRIVIAL_CONVERTER(UInt64, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(UInt64, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(UInt64);
	////////////////////////////////////////////////////////////////////////////////

	DECLARE_TRIVIAL_CONVERTER(Bool, SInt8);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt16);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt32);
	DECLARE_TRIVIAL_CONVERTER(Bool, SInt64);

	DECLARE_TRIVIAL_CONVERTER(Bool, UInt8);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt16);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt32);
	DECLARE_TRIVIAL_CONVERTER(Bool, UInt64);

	DECLARE_TRIVIAL_CONVERTER(Bool, Float32);
	DECLARE_TRIVIAL_CONVERTER(Bool, Float64);

	DECLARE_TRIVIAL_CONVERTER(Bool, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Bool, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Bool);

	/////////////////////////////////////////////////////////////////////////////
	//	Floats are rounded, when casted to ints.
	/////////////////////////////////////////////////////////////////////////////
	#define DECLARE_ROUND_FLOATS_CONVERTER(fromType, toType, roundFunc)			\
	class CRound##fromType##To##toType##CastingPolicy :							\
		public CCastPolicy<fromType, toType>									\
	{																			\
		protected:																\
			virtual toType performCast(const fromType& from) const				\
			{																	\
				return toType(static_cast<toType>(from));						\
			}																	\
	};																			\
	mPolicyMap[CString(typeid(fromType).name())][CString(typeid(toType).name())] =\
		new CRound##fromType##To##toType##CastingPolicy();

	DECLARE_ROUND_FLOATS_CONVERTER(Float32, SInt8, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, SInt16, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, SInt32, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, SInt64, llroundf);

	DECLARE_ROUND_FLOATS_CONVERTER(Float32, UInt8, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, UInt16, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, UInt32, lroundf);
	DECLARE_ROUND_FLOATS_CONVERTER(Float32, UInt64, llroundf);

	DECLARE_TRIVIAL_CONVERTER(Float32, Float64);

	DECLARE_TRIVIAL_CONVERTER(Float32, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Float32, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Float32);
	/////////////////////////////////////////////////////////////////////////////

	DECLARE_ROUND_FLOATS_CONVERTER(Float64, SInt8, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, SInt16, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, SInt32, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, SInt64, llround);

	DECLARE_ROUND_FLOATS_CONVERTER(Float64, UInt8, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, UInt16, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, UInt32, lround);
	DECLARE_ROUND_FLOATS_CONVERTER(Float64, UInt64, llround);

	DECLARE_TRIVIAL_CONVERTER(Float64, Float32);

	DECLARE_TRIVIAL_CONVERTER(Float64, Bool);

	DECLARE_ON_CONSTRUCTOR_CONVERTER(Float64, CNumber);
	DECLARE_NUMERIC_TO_STRING_CONVERTER(Float64);

	/////////////////////////////////////////////////////////////////////////////
	// CNumbers are casted in their own way
	/////////////////////////////////////////////////////////////////////////////

	#define DECLARE_CNUMBER_CONVERTER(toType)												\
	mPolicyMap[CString(typeid(CNumber).name())][CString(typeid(toType).name())] =\
		new CNumberCastPolicy<toType>();

	DECLARE_CNUMBER_CONVERTER(SInt8);
	DECLARE_CNUMBER_CONVERTER(SInt16);
	DECLARE_CNUMBER_CONVERTER(SInt32);
	DECLARE_CNUMBER_CONVERTER(SInt64);

	DECLARE_CNUMBER_CONVERTER(UInt8);
	DECLARE_CNUMBER_CONVERTER(UInt16);
	DECLARE_CNUMBER_CONVERTER(UInt32);
	DECLARE_CNUMBER_CONVERTER(UInt64);

	DECLARE_CNUMBER_CONVERTER(Float32);
	DECLARE_CNUMBER_CONVERTER(Float64);

	DECLARE_CNUMBER_CONVERTER(CString);

	DECLARE_CNUMBER_CONVERTER(Bool);

	/////////////////////////////////////////////////////////////////////////////
	// CStrings are casted in their own way
	/////////////////////////////////////////////////////////////////////////////

	#define DECLARE_CSTRING_CONVERTER(toType)												\
	mPolicyMap[CString(typeid(CNumber).name())][CString(typeid(toType).name())] =\
		new CStringToNumberCastPolicy<toType>();

	DECLARE_CSTRING_CONVERTER(SInt8);
	DECLARE_CSTRING_CONVERTER(SInt16);
	DECLARE_CSTRING_CONVERTER(SInt32);
	DECLARE_CSTRING_CONVERTER(SInt64);

	DECLARE_CSTRING_CONVERTER(UInt8);
	DECLARE_CSTRING_CONVERTER(UInt16);
	DECLARE_CSTRING_CONVERTER(UInt32);
	DECLARE_CSTRING_CONVERTER(UInt64);

	DECLARE_CSTRING_CONVERTER(Float32);
	DECLARE_CSTRING_CONVERTER(Float64);

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
