#pragma once

#include <common/types/slBasic.h>

LE_NAMESPACE_START

class CNumberBase
{
	protected:
		enum ENumberFormat
		{
			numberFormatUInt1 = 0,
			numberFormatUInt2,
			numberFormatUInt4,
			numberFormatUInt8,
			numberFormatSInt1,
			numberFormatSInt2,
			numberFormatSInt4,
			numberFormatSInt8,
			numberFormatFloat4,
			numberFormatFloat8,
			numberFormatBool
		};

		union UNumberData
		{
			UInt1 valUInt1;
			UInt2 valUInt2;
			UInt4 valUInt4;
			UInt8 valUInt8;
			SInt1 valSInt1;
			SInt2 valSInt2;
			SInt4 valSInt4;
			SInt8 valSInt8;

			Float4 valFloat4;
			Float8 valFloat8;

			Bool valBool;
		};
};

LE_NAMESPACE_END
