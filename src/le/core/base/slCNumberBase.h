#if !defined SL_LE_core_base_slCNumberBase_h
#define SL_LE_core_base_slCNumberBase_h

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

class CNumberBase
{
	protected:
		union
		{
			UInt8 valUInt8;
			UInt16 valUInt16;
			UInt32 valUInt32;
			UInt64 valUInt64;
			SInt8 valSInt8;
			SInt16 valSInt16;
			SInt32 valSInt32;
			SInt64 valSInt64;

			Float32 valFloat32;
			Float64 valFloat64;

			Bool valBool;
		} mData;

		enum EFormat
		{
			eFormatUInt8 = 0,
			eFormatUInt16,
			eFormatUInt32,
			eFormatUInt64,
			eFormatSInt8,
			eFormatSInt16,
			eFormatSInt32,
			eFormatSInt64,
			eFormatFloat32,
			eFormatFloat64,
			eFormatBool
		};

		template <typename T> struct TSTypeToFormat;
};

template <> struct CNumberBase::TSTypeToFormat<UInt8> { enum { dataType = eFormatUInt8 }; };
template <> struct CNumberBase::TSTypeToFormat<UInt16> { enum { dataType = eFormatUInt16 }; };
template <> struct CNumberBase::TSTypeToFormat<UInt32> { enum { dataType = eFormatUInt32 }; };
template <> struct CNumberBase::TSTypeToFormat<UInt64> { enum { dataType = eFormatUInt64 }; };
template <> struct CNumberBase::TSTypeToFormat<SInt8> { enum { dataType = eFormatSInt8 }; };
template <> struct CNumberBase::TSTypeToFormat<SInt16> { enum { dataType = eFormatSInt16 }; };
template <> struct CNumberBase::TSTypeToFormat<SInt32> { enum { dataType = eFormatSInt32 }; };
template <> struct CNumberBase::TSTypeToFormat<SInt64> { enum { dataType = eFormatSInt64 }; };

template <> struct CNumberBase::TSTypeToFormat<Float32> { enum { dataType = eFormatFloat32 }; };
template <> struct CNumberBase::TSTypeToFormat<Float64> { enum { dataType = eFormatFloat64 }; };

template <> struct CNumberBase::TSTypeToFormat<Bool> { enum { dataType = eFormatBool }; };

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_base_slCNumberBase_h
