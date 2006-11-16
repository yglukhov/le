#pragma once

#include <common/types/slBasic.h>

LE_NAMESPACE_START

class CNumberBase
{
	protected:
		union UNumberData
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
		};
};

LE_NAMESPACE_END
