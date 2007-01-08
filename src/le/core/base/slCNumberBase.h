#pragma once

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

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

	} // namespace le
} // namespace sokira
