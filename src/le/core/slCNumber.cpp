#include <cmath>
#include "slCNumber.h"
#include <le/core/slCDictionary.h>

// TODO: remove
#define lroundf(x) (x)
#define lround(x) (x)
#define llroundf(x) (x)
#define llround(x) (x)
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

void CNumber::serialize(CDictionary& toDictionary) const
{
	toDictionary.rootValue(valueAsString());
}

void CNumber::deserialize(const CDictionary& fromDictionary)
{
	operator=(fromDictionary.rootValue());
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
