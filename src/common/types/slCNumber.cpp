#include "slCNumber.h"
#include <common/types/slCString.h>
#include <math.h>

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CNumber);

CNumber::CNumber() :
	mFormat(numberFormatSInt4)
{
	mData.valSInt8 = 0;
}

CNumber::CNumber(SInt1 value) :
	mFormat(numberFormatSInt1)
{
	mData.valSInt1 = value;
}

CNumber::CNumber(SInt2 value) :
	mFormat(numberFormatSInt2)
{
	mData.valSInt2 = value;
}

CNumber::CNumber(SInt4 value) :
	mFormat(numberFormatSInt4)
{
	mData.valSInt4 = value;
}

CNumber::CNumber(SInt8 value) :
	mFormat(numberFormatSInt8)
{
	mData.valSInt8 = value;
}


CNumber::CNumber(UInt1 value) :
	mFormat(numberFormatUInt1)
{
	mData.valUInt1 = value;
}

CNumber::CNumber(UInt2 value) :
	mFormat(numberFormatUInt2)
{
	mData.valUInt2 = value;
}

CNumber::CNumber(UInt4 value) :
	mFormat(numberFormatUInt4)
{
	mData.valUInt4 = value;
}

CNumber::CNumber(UInt8 value) :
	mFormat(numberFormatUInt8)
{
	mData.valUInt8 = value;
}


CNumber::CNumber(Float4 value) :
	mFormat(numberFormatFloat4)
{
	mData.valFloat4 = value;
}

CNumber::CNumber(Float8 value) :
	mFormat(numberFormatFloat8)
{
	mData.valFloat8 = value;
}


CNumber::CNumber(Bool value) :
	mFormat(numberFormatBool)
{
	mData.valBool = value;
}

CNumber::CNumber(const CString& value) :
	mFormat(numberFormatSInt4)
{
	mData.valUInt8 = 0;
	// TODO: complete this
}

CNumber::CNumber(const CNumber& copy) :
	mFormat(copy.mFormat),
	mData(copy.mData)
{

}

SInt1 CNumber::valueAs(TSTypeToType<SInt1>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<SInt1>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<SInt1>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<SInt1>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<SInt1>(mData.valUInt8);
		case numberFormatSInt1: return mData.valSInt1;
		case numberFormatSInt2: return static_cast<SInt1>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<SInt1>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<SInt1>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<SInt1>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<SInt1>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<SInt1>(mData.valBool);
		default: return 0;
	}
	return 0;
}

SInt2 CNumber::valueAs(TSTypeToType<SInt2>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<SInt2>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<SInt2>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<SInt2>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<SInt2>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<SInt2>(mData.valSInt1);
		case numberFormatSInt2: return mData.valSInt2;
		case numberFormatSInt4: return static_cast<SInt2>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<SInt2>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<SInt2>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<SInt2>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<SInt2>(mData.valBool);
		default: return 0;
	}
	return 0;
}

SInt4 CNumber::valueAs(TSTypeToType<SInt4>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<SInt4>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<SInt4>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<SInt4>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<SInt4>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<SInt4>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<SInt4>(mData.valSInt2);
		case numberFormatSInt4: return mData.valSInt4;
		case numberFormatSInt8: return static_cast<SInt4>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<SInt4>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<SInt4>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<SInt4>(mData.valBool);
		default: return 0;
	}
	return 0;
}

SInt8 CNumber::valueAs(TSTypeToType<SInt8>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<SInt8>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<SInt8>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<SInt8>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<SInt8>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<SInt8>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<SInt8>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<SInt8>(mData.valSInt4);
		case numberFormatSInt8: return mData.valSInt8;
		case numberFormatFloat4: return static_cast<SInt8>(llroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<SInt8>(llround(mData.valFloat8));
		case numberFormatBool: return static_cast<SInt8>(mData.valBool);
		default: return 0;
	}
	return 0;
}

UInt1 CNumber::valueAs(TSTypeToType<UInt1>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return mData.valUInt1;
		case numberFormatUInt2: return static_cast<UInt1>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<UInt1>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<UInt1>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<UInt1>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<UInt1>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<UInt1>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<UInt1>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<UInt1>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<UInt1>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<UInt1>(mData.valBool);
		default: return 0;
	}
	return 0;
}

UInt2 CNumber::valueAs(TSTypeToType<UInt2>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<UInt2>(mData.valUInt1);
		case numberFormatUInt2: return mData.valUInt2;
		case numberFormatUInt4: return static_cast<UInt2>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<UInt2>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<UInt2>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<UInt2>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<UInt2>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<UInt2>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<UInt2>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<UInt2>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<UInt2>(mData.valBool);
		default: return 0;
	}
	return 0;
}

UInt4 CNumber::valueAs(TSTypeToType<UInt4>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<UInt4>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<UInt4>(mData.valUInt2);
		case numberFormatUInt4: return mData.valUInt4;
		case numberFormatUInt8: return static_cast<UInt4>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<UInt4>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<UInt4>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<UInt4>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<UInt4>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<UInt4>(lroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<UInt4>(lround(mData.valFloat8));
		case numberFormatBool: return static_cast<UInt4>(mData.valBool);
		default: return 0;
	}
	return 0;
}

UInt8 CNumber::valueAs(TSTypeToType<UInt8>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<UInt8>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<UInt8>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<UInt8>(mData.valUInt4);
		case numberFormatUInt8: return mData.valUInt8;
		case numberFormatSInt1: return static_cast<UInt8>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<UInt8>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<UInt8>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<UInt8>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<UInt8>(llroundf(mData.valFloat4));
		case numberFormatFloat8: return static_cast<UInt8>(llround(mData.valFloat8));
		case numberFormatBool: return static_cast<UInt8>(mData.valBool);
		default: return 0;
	}
	return 0;
}

Float4 CNumber::valueAs(TSTypeToType<Float4>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<Float4>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<Float4>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<Float4>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<Float4>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<Float4>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<Float4>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<Float4>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<Float4>(mData.valSInt8);
		case numberFormatFloat4: return mData.valFloat4;
		case numberFormatFloat8: return static_cast<Float4>(mData.valFloat8);
		case numberFormatBool: return static_cast<Float4>(mData.valBool);
		default: return 0;
	}
	return 0;
}

Float8 CNumber::valueAs(TSTypeToType<Float8>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<Float8>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<Float8>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<Float8>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<Float8>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<Float8>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<Float8>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<Float8>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<Float8>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<Float8>(mData.valFloat4);
		case numberFormatFloat8: return mData.valFloat8;
		case numberFormatBool: return static_cast<Float8>(mData.valBool);
		default: return 0;
	}
	return 0;
}

Bool CNumber::valueAs(TSTypeToType<Bool>) const
{
	switch (mFormat)
	{
		case numberFormatUInt1: return static_cast<Bool>(mData.valUInt1);
		case numberFormatUInt2: return static_cast<Bool>(mData.valUInt2);
		case numberFormatUInt4: return static_cast<Bool>(mData.valUInt4);
		case numberFormatUInt8: return static_cast<Bool>(mData.valUInt8);
		case numberFormatSInt1: return static_cast<Bool>(mData.valSInt1);
		case numberFormatSInt2: return static_cast<Bool>(mData.valSInt2);
		case numberFormatSInt4: return static_cast<Bool>(mData.valSInt4);
		case numberFormatSInt8: return static_cast<Bool>(mData.valSInt8);
		case numberFormatFloat4: return static_cast<Bool>(mData.valFloat4);
		case numberFormatFloat8: return static_cast<Bool>(mData.valFloat8);
		case numberFormatBool: return static_cast<Float8>(mData.valBool);
		default: return 0;
	}
	return 0;
}

CString CNumber::valueAs(TSTypeToType<CString>) const
{
	// TODO: complete this
	return CString();
}

LE_NAMESPACE_END
