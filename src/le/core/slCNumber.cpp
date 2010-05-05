#include <cmath>
#include "slCNumber.h"
#include <le/core/slCDictionary.h>

// TODO: remove
#define lroundf(x) (x)
#define lround(x) (x)
#define llroundf(x) (x)
#define llround(x) (x)

////////////////////////////////////////////////////////////////////////////////
// Endian swapping

#define LE_SwapInt16(type, x) \
	((type)((((type)(x) & 0xff00) >> 8) | \
	(((type)(x) & 0x00ff) << 8)))

#define LE_SwapInt32(type, x) \
    ((type)((((type)(x) & 0xff000000) >> 24) | \
                (((type)(x) & 0x00ff0000) >>  8) | \
                (((type)(x) & 0x0000ff00) <<  8) | \
                (((type)(x) & 0x000000ff) << 24)))

#define LE_SwapInt64(type, x) \
    ((type)((((type)(x) & 0xff00000000000000ULL) >> 56) | \
                (((type)(x) & 0x00ff000000000000ULL) >> 40) | \
                (((type)(x) & 0x0000ff0000000000ULL) >> 24) | \
                (((type)(x) & 0x000000ff00000000ULL) >>  8) | \
                (((type)(x) & 0x00000000ff000000ULL) <<  8) | \
                (((type)(x) & 0x0000000000ff0000ULL) << 24) | \
                (((type)(x) & 0x000000000000ff00ULL) << 40) | \
                (((type)(x) & 0x00000000000000ffULL) << 56)))

////////////////////////////////////////////////////////////////////////////////


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CNumber);

CNumber::CNumber() :
	mFormat(eFormatSInt32)
{
	mData.valSInt32 = 0;
}

CNumber::CNumber(SInt8 value) :
	mFormat(eFormatSInt8)
{
	mData.valSInt8 = value;
}

CNumber::CNumber(SInt16 value) :
	mFormat(eFormatSInt16)
{
	mData.valSInt16 = value;
}

CNumber::CNumber(SInt32 value) :
	mFormat(eFormatSInt32)
{
	mData.valSInt32 = value;
}

CNumber::CNumber(SInt64 value) :
	mFormat(eFormatSInt64)
{
	mData.valSInt64 = value;
}


CNumber::CNumber(UInt8 value) :
	mFormat(eFormatUInt8)
{
	mData.valUInt8 = value;
}

CNumber::CNumber(UInt16 value) :
	mFormat(eFormatUInt16)
{
	mData.valUInt16 = value;
}

CNumber::CNumber(UInt32 value) :
	mFormat(eFormatUInt32)
{
	mData.valUInt32 = value;
}

CNumber::CNumber(UInt64 value) :
	mFormat(eFormatUInt64)
{
	mData.valUInt64 = value;
}


CNumber::CNumber(Float32 value) :
	mFormat(eFormatFloat32)
{
	mData.valFloat32 = value;
}

CNumber::CNumber(Float64 value) :
	mFormat(eFormatFloat64)
{
	mData.valFloat64 = value;
}


CNumber::CNumber(Bool value) :
	mFormat(eFormatBool)
{
	mData.valBool = value;
}

CNumber::CNumber(const CString& value) :
	mFormat(eFormatFloat32)
{
	// TODO: complete this
	sscanf(value.cString(), "%f", &mData.valFloat32);
}

CNumber::CNumber(const CDictionary& fromDict)
{
	operator=(fromDict.rootValue());
}

CNumber::CNumber(const CNumber& copy) :
	mData(copy.mData),
	mFormat(copy.mFormat)
{

}

const CNumber& CNumber::operator++()		// prefix
{
	switch (mFormat)
	{
		case eFormatUInt8:		++mData.valUInt8;	break;
		case eFormatUInt16:		++mData.valUInt16;	break;
		case eFormatUInt32:		++mData.valUInt32;	break;
		case eFormatUInt64:		++mData.valUInt64;	break;
		case eFormatSInt8:		++mData.valSInt8;	break;
		case eFormatSInt16:		++mData.valSInt16;	break;
		case eFormatSInt32:		++mData.valSInt32;	break;
		case eFormatSInt64:		++mData.valSInt64;	break;
		case eFormatFloat32:	++mData.valFloat32; break;
		case eFormatFloat64:	++mData.valFloat64; break;
		case eFormatBool:		mData.valBool = !mData.valBool;
		default:;
	}
	return *this;
}

const CNumber CNumber::operator++(int)		// postfix
{
	CNumber result = *this;
	switch (mFormat)
	{
		case eFormatUInt8:		++mData.valUInt8;	break;
		case eFormatUInt16:		++mData.valUInt16;	break;
		case eFormatUInt32:		++mData.valUInt32;	break;
		case eFormatUInt64:		++mData.valUInt64;	break;
		case eFormatSInt8:		++mData.valSInt8;	break;
		case eFormatSInt16:		++mData.valSInt16;	break;
		case eFormatSInt32:		++mData.valSInt32;	break;
		case eFormatSInt64:		++mData.valSInt64;	break;
		case eFormatFloat32:	++mData.valFloat32; break;
		case eFormatFloat64:	++mData.valFloat64; break;
		case eFormatBool:		mData.valBool = !mData.valBool;
		default:;
	}
	return result;
}

const CNumber& CNumber::operator--()		// prefix
{
	switch (mFormat)
	{
		case eFormatUInt8:		--mData.valUInt8;	break;
		case eFormatUInt16:		--mData.valUInt16;	break;
		case eFormatUInt32:		--mData.valUInt32;	break;
		case eFormatUInt64:		--mData.valUInt64;	break;
		case eFormatSInt8:		--mData.valSInt8;	break;
		case eFormatSInt16:		--mData.valSInt16;	break;
		case eFormatSInt32:		--mData.valSInt32;	break;
		case eFormatSInt64:		--mData.valSInt64;	break;
		case eFormatFloat32:	--mData.valFloat32; break;
		case eFormatFloat64:	--mData.valFloat64; break;
		case eFormatBool:		mData.valBool = !mData.valBool;
		default:;
	}
	return *this;
}

const CNumber CNumber::operator--(int)		// postfix
{
	CNumber result = *this;
	switch (mFormat)
	{
		case eFormatUInt8:		--mData.valUInt8;	break;
		case eFormatUInt16:		--mData.valUInt16;	break;
		case eFormatUInt32:		--mData.valUInt32;	break;
		case eFormatUInt64:		--mData.valUInt64;	break;
		case eFormatSInt8:		--mData.valSInt8;	break;
		case eFormatSInt16:		--mData.valSInt16;	break;
		case eFormatSInt32:		--mData.valSInt32;	break;
		case eFormatSInt64:		--mData.valSInt64;	break;
		case eFormatFloat32:	--mData.valFloat32; break;
		case eFormatFloat64:	--mData.valFloat64; break;
		case eFormatBool:		mData.valBool = !mData.valBool;
		default:;
	}
	return result;
}

const CNumber& CNumber::operator=(SInt8 value)
{
	mFormat = eFormatSInt8;
	mData.valSInt8 = value;
	return *this;
}

const CNumber& CNumber::operator=(SInt16 value)
{
	mFormat = eFormatSInt16;
	mData.valSInt16 = value;
	return *this;
}

const CNumber& CNumber::operator=(SInt32 value)
{
	mFormat = eFormatSInt32;
	mData.valSInt32 = value;
	return *this;
}

const CNumber& CNumber::operator=(SInt64 value)
{
	mFormat = eFormatSInt64;
	mData.valSInt64 = value;
	return *this;
}

const CNumber& CNumber::operator=(UInt8 value)
{
	mFormat = eFormatUInt8;
	mData.valUInt8 = value;
	return *this;
}

const CNumber& CNumber::operator=(UInt16 value)
{
	mFormat = eFormatUInt16;
	mData.valUInt16 = value;
	return *this;
}

const CNumber& CNumber::operator=(UInt32 value)
{
	mFormat = eFormatUInt32;
	mData.valUInt32 = value;
	return *this;
}

const CNumber& CNumber::operator=(UInt64 value)
{
	mFormat = eFormatUInt64;
	mData.valUInt64 = value;
	return *this;
}

const CNumber& CNumber::operator=(Float32 value)
{
	mFormat = eFormatFloat32;
	mData.valFloat32 = value;
	return *this;
}

const CNumber& CNumber::operator=(Float64 value)
{
	mFormat = eFormatFloat64;
	mData.valFloat64 = value;
	return *this;
}

const CNumber& CNumber::operator=(Bool value)
{
	mFormat = eFormatBool;
	mData.valBool = value;
	return *this;
}

const CNumber& CNumber::operator=(const CString& value)
{
	// TODO: complete this
	mFormat = eFormatFloat32;
	sscanf(value.cString(), "%f", &mData.valFloat32);
	return *this;
}

const CNumber& CNumber::operator+=(const CNumber& value)
{
	return *this = this->valueAsFloat32() + value.valueAsFloat32();
}

const CNumber& CNumber::operator-=(const CNumber& value)
{
	return *this = this->valueAsFloat32() - value.valueAsFloat32();
}

const CNumber& CNumber::operator*=(const CNumber& value)
{
	return *this = this->valueAsFloat32() * value.valueAsFloat32();
}

const CNumber& CNumber::operator/=(const CNumber& value)
{
	Float32 rval = value.valueAsFloat32();
//	if (rval == 0.0) rval = 1.0;
	return *this = this->valueAsFloat32() / rval;
}

void CNumber::setBigEndianValue(UInt64 value)
{
	mFormat = eFormatUInt64;
	mData.valUInt64 = bigEndianToHost(value);
}

void CNumber::setBigEndianValue(UInt32 value)
{
	mFormat = eFormatUInt32;
	mData.valUInt32 = bigEndianToHost(value);
}

void CNumber::setBigEndianValue(UInt16 value)
{
	mFormat = eFormatUInt16;
	mData.valUInt16 = bigEndianToHost(value);
}

void CNumber::setBigEndianValue(SInt64 value)
{
	mFormat = eFormatSInt64;
	mData.valSInt64 = bigEndianToHost(value);
}

void CNumber::setBigEndianValue(SInt32 value)
{
	mFormat = eFormatSInt32;
	mData.valSInt32 = bigEndianToHost(value);
}

void CNumber::setBigEndianValue(SInt16 value)
{
	mFormat = eFormatSInt16;
	mData.valSInt16 = bigEndianToHost(value);
}


void CNumber::setLittleEndianValue(UInt64 value)
{
	mFormat = eFormatUInt64;
	mData.valUInt64 = littleEndianToHost(value);
}

void CNumber::setLittleEndianValue(UInt32 value)
{
	mFormat = eFormatUInt32;
	mData.valUInt32 = littleEndianToHost(value);
}

void CNumber::setLittleEndianValue(UInt16 value)
{
	mFormat = eFormatUInt16;
	mData.valUInt16 = littleEndianToHost(value);
}

void CNumber::setLittleEndianValue(SInt64 value)
{
	mFormat = eFormatSInt64;
	mData.valSInt64 = littleEndianToHost(value);
}

void CNumber::setLittleEndianValue(SInt32 value)
{
	mFormat = eFormatSInt32;
	mData.valSInt32 = littleEndianToHost(value);
}

void CNumber::setLittleEndianValue(SInt16 value)
{
	mFormat = eFormatSInt16;
	mData.valSInt16 = littleEndianToHost(value);
}

void CNumber::serialize(CDictionary& toDictionary) const
{
	toDictionary.setRootValue(valueAsString());
}

void CNumber::deserialize(const CDictionary& fromDictionary)
{
	operator=(fromDictionary.rootValue());
}

template <typename T>
inline T __hostToBigEndian(T value)
{
#if LE_ENDIAN == LE_ENDIAN_BIG
	return value;
#else
	return CNumber::littleEndianToBigEndian(value);
#endif
}

template <typename T>
inline T __bigEndianToHost(T value)
{
#if LE_ENDIAN == LE_ENDIAN_BIG
	return value;
#else
	return CNumber::bigEndianToLittleEndian(value);
#endif
}

template <typename T>
inline T __hostToLittleEndian(T value)
{
#if LE_ENDIAN == LE_ENDIAN_BIG
	return CNumber::bigEndianToLittleEndian(value);
#else
	return value;
#endif
}

template <typename T>
inline T __littleEndianToHost(T value)
{
#if LE_ENDIAN == LE_ENDIAN_BIG
	return CNumber::littleEndianToBigEndian(value);
#else
	return value;
#endif
}

UInt64 CNumber::hostToBigEndian(UInt64 value)
{
	return __hostToBigEndian(value);
}

UInt32 CNumber::hostToBigEndian(UInt32 value)
{
	return __hostToBigEndian(value);

}

UInt16 CNumber::hostToBigEndian(UInt16 value)
{
	return __hostToBigEndian(value);

}

SInt64 CNumber::hostToBigEndian(SInt64 value)
{
	return __hostToBigEndian(value);
}

SInt32 CNumber::hostToBigEndian(SInt32 value)
{
	return __hostToBigEndian(value);
}

SInt16 CNumber::hostToBigEndian(SInt16 value)
{
	return __hostToBigEndian(value);
}


UInt64 CNumber::hostToLittleEndian(UInt64 value)
{
	return __hostToLittleEndian(value);
}

UInt32 CNumber::hostToLittleEndian(UInt32 value)
{
	return __hostToLittleEndian(value);
}

UInt16 CNumber::hostToLittleEndian(UInt16 value)
{
	return __hostToLittleEndian(value);
}

SInt64 CNumber::hostToLittleEndian(SInt64 value)
{
	return __hostToLittleEndian(value);
}

SInt32 CNumber::hostToLittleEndian(SInt32 value)
{
	return __hostToLittleEndian(value);
}

SInt16 CNumber::hostToLittleEndian(SInt16 value)
{
	return __hostToLittleEndian(value);
}


UInt64 CNumber::bigEndianToHost(UInt64 value)
{
	return __bigEndianToHost(value);
}

UInt32 CNumber::bigEndianToHost(UInt32 value)
{
	return __bigEndianToHost(value);
}

UInt16 CNumber::bigEndianToHost(UInt16 value)
{
	return __bigEndianToHost(value);
}

SInt64 CNumber::bigEndianToHost(SInt64 value)
{
	return __bigEndianToHost(value);
}

SInt32 CNumber::bigEndianToHost(SInt32 value)
{
	return __bigEndianToHost(value);
}

SInt16 CNumber::bigEndianToHost(SInt16 value)
{
	return __bigEndianToHost(value);
}


UInt64 CNumber::littleEndianToHost(UInt64 value)
{
	return __littleEndianToHost(value);
}

UInt32 CNumber::littleEndianToHost(UInt32 value)
{
	return __littleEndianToHost(value);
}

UInt16 CNumber::littleEndianToHost(UInt16 value)
{
	return __littleEndianToHost(value);
}

SInt32 CNumber::littleEndianToHost(SInt32 value)
{
	return __littleEndianToHost(value);
}

SInt64 CNumber::littleEndianToHost(SInt64 value)
{
	return __littleEndianToHost(value);
}

SInt16 CNumber::littleEndianToHost(SInt16 value)
{
	return __littleEndianToHost(value);
}


UInt64 CNumber::littleEndianToBigEndian(UInt64 value)
{
	return LE_SwapInt64(UInt64, value);
}

UInt32 CNumber::littleEndianToBigEndian(UInt32 value)
{
	return LE_SwapInt32(UInt32, value);
}

UInt16 CNumber::littleEndianToBigEndian(UInt16 value)
{
	return LE_SwapInt16(UInt16, value);
}

SInt64 CNumber::littleEndianToBigEndian(SInt64 value)
{
	return LE_SwapInt64(SInt64, value);
}

SInt32 CNumber::littleEndianToBigEndian(SInt32 value)
{
	return LE_SwapInt32(SInt32, value);
}

SInt16 CNumber::littleEndianToBigEndian(SInt16 value)
{
	return LE_SwapInt16(SInt16, value);
}

UInt64 CNumber::bigEndianToLittleEndian(UInt64 value)
{
	return LE_SwapInt64(UInt64, value);
}

UInt32 CNumber::bigEndianToLittleEndian(UInt32 value)
{
	return LE_SwapInt32(UInt32, value);
}

UInt16 CNumber::bigEndianToLittleEndian(UInt16 value)
{
	return LE_SwapInt16(UInt16, value);
}

SInt64 CNumber::bigEndianToLittleEndian(SInt64 value)
{
	return LE_SwapInt64(SInt64, value);
}

SInt32 CNumber::bigEndianToLittleEndian(SInt32 value)
{
	return LE_SwapInt32(SInt32, value);
}

SInt16 CNumber::bigEndianToLittleEndian(SInt16 value)
{
	return LE_SwapInt16(SInt16, value);
}



SInt8 CNumber::valueAs(TSTypeToType<SInt8>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<SInt8>(mData.valUInt8);
		case eFormatUInt16: return static_cast<SInt8>(mData.valUInt16);
		case eFormatUInt32: return static_cast<SInt8>(mData.valUInt32);
		case eFormatUInt64: return static_cast<SInt8>(mData.valUInt64);
		case eFormatSInt8: return mData.valSInt8;
		case eFormatSInt16: return static_cast<SInt8>(mData.valSInt16);
		case eFormatSInt32: return static_cast<SInt8>(mData.valSInt32);
		case eFormatSInt64: return static_cast<SInt8>(mData.valSInt64);
		case eFormatFloat32: return static_cast<SInt8>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<SInt8>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<SInt8>(mData.valBool);
		default:;
	}
	return 0;
}

SInt16 CNumber::valueAs(TSTypeToType<SInt16>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<SInt16>(mData.valUInt8);
		case eFormatUInt16: return static_cast<SInt16>(mData.valUInt16);
		case eFormatUInt32: return static_cast<SInt16>(mData.valUInt32);
		case eFormatUInt64: return static_cast<SInt16>(mData.valUInt64);
		case eFormatSInt8: return static_cast<SInt16>(mData.valSInt8);
		case eFormatSInt16: return mData.valSInt16;
		case eFormatSInt32: return static_cast<SInt16>(mData.valSInt32);
		case eFormatSInt64: return static_cast<SInt16>(mData.valSInt64);
		case eFormatFloat32: return static_cast<SInt16>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<SInt16>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<SInt16>(mData.valBool);
		default:;
	}
	return 0;
}

SInt32 CNumber::valueAs(TSTypeToType<SInt32>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<SInt32>(mData.valUInt8);
		case eFormatUInt16: return static_cast<SInt32>(mData.valUInt16);
		case eFormatUInt32: return static_cast<SInt32>(mData.valUInt32);
		case eFormatUInt64: return static_cast<SInt32>(mData.valUInt64);
		case eFormatSInt8: return static_cast<SInt32>(mData.valSInt8);
		case eFormatSInt16: return static_cast<SInt32>(mData.valSInt16);
		case eFormatSInt32: return mData.valSInt32;
		case eFormatSInt64: return static_cast<SInt32>(mData.valSInt64);
		case eFormatFloat32: return static_cast<SInt32>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<SInt32>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<SInt32>(mData.valBool);
		default:;
	}
	return 0;
}

SInt64 CNumber::valueAs(TSTypeToType<SInt64>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<SInt64>(mData.valUInt8);
		case eFormatUInt16: return static_cast<SInt64>(mData.valUInt16);
		case eFormatUInt32: return static_cast<SInt64>(mData.valUInt32);
		case eFormatUInt64: return static_cast<SInt64>(mData.valUInt64);
		case eFormatSInt8: return static_cast<SInt64>(mData.valSInt8);
		case eFormatSInt16: return static_cast<SInt64>(mData.valSInt16);
		case eFormatSInt32: return static_cast<SInt64>(mData.valSInt32);
		case eFormatSInt64: return mData.valSInt64;
		case eFormatFloat32: return static_cast<SInt64>(llroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<SInt64>(llround(mData.valFloat64));
		case eFormatBool: return static_cast<SInt64>(mData.valBool);
		default:;
	}
	return 0;
}

UInt8 CNumber::valueAs(TSTypeToType<UInt8>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return mData.valUInt8;
		case eFormatUInt16: return static_cast<UInt8>(mData.valUInt16);
		case eFormatUInt32: return static_cast<UInt8>(mData.valUInt32);
		case eFormatUInt64: return static_cast<UInt8>(mData.valUInt64);
		case eFormatSInt8: return static_cast<UInt8>(mData.valSInt8);
		case eFormatSInt16: return static_cast<UInt8>(mData.valSInt16);
		case eFormatSInt32: return static_cast<UInt8>(mData.valSInt32);
		case eFormatSInt64: return static_cast<UInt8>(mData.valSInt64);
		case eFormatFloat32: return static_cast<UInt8>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<UInt8>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<UInt8>(mData.valBool);
		default:;
	}
	return 0;
}

UInt16 CNumber::valueAs(TSTypeToType<UInt16>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<UInt16>(mData.valUInt8);
		case eFormatUInt16: return mData.valUInt16;
		case eFormatUInt32: return static_cast<UInt16>(mData.valUInt32);
		case eFormatUInt64: return static_cast<UInt16>(mData.valUInt64);
		case eFormatSInt8: return static_cast<UInt16>(mData.valSInt8);
		case eFormatSInt16: return static_cast<UInt16>(mData.valSInt16);
		case eFormatSInt32: return static_cast<UInt16>(mData.valSInt32);
		case eFormatSInt64: return static_cast<UInt16>(mData.valSInt64);
		case eFormatFloat32: return static_cast<UInt16>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<UInt16>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<UInt16>(mData.valBool);
		default:;
	}
	return 0;
}

UInt32 CNumber::valueAs(TSTypeToType<UInt32>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<UInt32>(mData.valUInt8);
		case eFormatUInt16: return static_cast<UInt32>(mData.valUInt16);
		case eFormatUInt32: return mData.valUInt32;
		case eFormatUInt64: return static_cast<UInt32>(mData.valUInt64);
		case eFormatSInt8: return static_cast<UInt32>(mData.valSInt8);
		case eFormatSInt16: return static_cast<UInt32>(mData.valSInt16);
		case eFormatSInt32: return static_cast<UInt32>(mData.valSInt32);
		case eFormatSInt64: return static_cast<UInt32>(mData.valSInt64);
		case eFormatFloat32: return static_cast<UInt32>(lroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<UInt32>(lround(mData.valFloat64));
		case eFormatBool: return static_cast<UInt32>(mData.valBool);
		default:;
	}
	return 0;
}

UInt64 CNumber::valueAs(TSTypeToType<UInt64>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<UInt64>(mData.valUInt8);
		case eFormatUInt16: return static_cast<UInt64>(mData.valUInt16);
		case eFormatUInt32: return static_cast<UInt64>(mData.valUInt32);
		case eFormatUInt64: return mData.valUInt64;
		case eFormatSInt8: return static_cast<UInt64>(mData.valSInt8);
		case eFormatSInt16: return static_cast<UInt64>(mData.valSInt16);
		case eFormatSInt32: return static_cast<UInt64>(mData.valSInt32);
		case eFormatSInt64: return static_cast<UInt64>(mData.valSInt64);
		case eFormatFloat32: return static_cast<UInt64>(llroundf(mData.valFloat32));
		case eFormatFloat64: return static_cast<UInt64>(llround(mData.valFloat64));
		case eFormatBool: return static_cast<UInt64>(mData.valBool);
		default:;
	}
	return 0;
}

Float32 CNumber::valueAs(TSTypeToType<Float32>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<Float32>(mData.valUInt8);
		case eFormatUInt16: return static_cast<Float32>(mData.valUInt16);
		case eFormatUInt32: return static_cast<Float32>(mData.valUInt32);
		case eFormatUInt64: return static_cast<Float32>(mData.valUInt64);
		case eFormatSInt8: return static_cast<Float32>(mData.valSInt8);
		case eFormatSInt16: return static_cast<Float32>(mData.valSInt16);
		case eFormatSInt32: return static_cast<Float32>(mData.valSInt32);
		case eFormatSInt64: return static_cast<Float32>(mData.valSInt64);
		case eFormatFloat32: return mData.valFloat32;
		case eFormatFloat64: return static_cast<Float32>(mData.valFloat64);
		case eFormatBool: return static_cast<Float32>(mData.valBool);
		default:;
	}
	return 0.0f;
}

Float64 CNumber::valueAs(TSTypeToType<Float64>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return static_cast<Float64>(mData.valUInt8);
		case eFormatUInt16: return static_cast<Float64>(mData.valUInt16);
		case eFormatUInt32: return static_cast<Float64>(mData.valUInt32);
		case eFormatUInt64: return static_cast<Float64>(mData.valUInt64);
		case eFormatSInt8: return static_cast<Float64>(mData.valSInt8);
		case eFormatSInt16: return static_cast<Float64>(mData.valSInt16);
		case eFormatSInt32: return static_cast<Float64>(mData.valSInt32);
		case eFormatSInt64: return static_cast<Float64>(mData.valSInt64);
		case eFormatFloat32: return static_cast<Float64>(mData.valFloat32);
		case eFormatFloat64: return mData.valFloat64;
		case eFormatBool: return static_cast<Float64>(mData.valBool);
		default:;
	}
	return 0.0;
}

Bool CNumber::valueAs(TSTypeToType<Bool>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return (mData.valUInt8)?(true):(false);
		case eFormatUInt16: return (mData.valUInt16)?(true):(false);
		case eFormatUInt32: return (mData.valUInt32)?(true):(false);
		case eFormatUInt64: return (mData.valUInt64)?(true):(false);
		case eFormatSInt8: return (mData.valSInt8)?(true):(false);
		case eFormatSInt16: return (mData.valSInt16)?(true):(false);
		case eFormatSInt32: return (mData.valSInt32)?(true):(false);
		case eFormatSInt64: return (mData.valSInt64)?(true):(false);
		case eFormatFloat32: return (mData.valFloat32)?(true):(false);
		case eFormatFloat64: return (mData.valFloat64)?(true):(false);
		case eFormatBool: return mData.valBool;
		default:;
	}
	return false;
}

CString CNumber::valueAs(TSTypeToType<CString>) const
{
	switch (mFormat)
	{
		case eFormatUInt8: return CString::createWithFormat("%d", mData.valUInt8);
		case eFormatUInt16: return CString::createWithFormat("%d", mData.valUInt16);
		case eFormatUInt32: return CString::createWithFormat("%d", mData.valUInt32);
		case eFormatUInt64: return CString::createWithFormat("%d", mData.valUInt64);
		case eFormatSInt8: return CString::createWithFormat("%d", mData.valSInt8);
		case eFormatSInt16: return CString::createWithFormat("%d", mData.valSInt16);
		case eFormatSInt32: return CString::createWithFormat("%d", mData.valSInt32);
		case eFormatSInt64: return CString::createWithFormat("%d", mData.valSInt64);
		case eFormatFloat32: return CString::createWithFormat("%f", mData.valFloat32);
		case eFormatFloat64: return CString::createWithFormat("%f", mData.valFloat64);
		case eFormatBool: return CString::createWithFormat("%d", mData.valBool);
		default: ;
	}
	std::cout << "ERROR!" << std::endl;
	return CString();
}

	} // namespace le
} // namespace sokira
