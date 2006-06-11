#pragma once

#include <common/slCObject.h>
#include <template/util/slTSConstToType.h>
#include "base/slCNumberBase.h"

LE_NAMESPACE_START

class CNumber : public CObject, CNumberBase
{
	DECLARE_RUNTIME_CLASS(CNumber);

	public:
		CNumber();

		CNumber(SInt1 value);
		CNumber(SInt2 value);
		CNumber(SInt4 value);
		CNumber(SInt8 value);

		CNumber(UInt1 value);
		CNumber(UInt2 value);
		CNumber(UInt4 value);
		CNumber(UInt8 value);

		CNumber(Float4 value);
		CNumber(Float8 value);

		CNumber(Bool value);

		CNumber(const CString& value);

		CNumber(const CNumber& copy);

		template <typename T>
		inline T valueAs() const
		{
			return valueAs(TSTypeToType<T>());
		}

		inline SInt1 valueAsSInt1() const	{ return valueAs(TSTypeToType<SInt1>()); }
		inline SInt2 valueAsSInt2() const	{ return valueAs(TSTypeToType<SInt2>()); }
		inline SInt4 valueAsSInt4() const	{ return valueAs(TSTypeToType<SInt4>()); }
		inline SInt8 valueAsSInt8() const	{ return valueAs(TSTypeToType<SInt8>()); }
		inline UInt1 valueAsUInt1() const	{ return valueAs(TSTypeToType<UInt1>()); }
		inline UInt2 valueAsUInt2() const	{ return valueAs(TSTypeToType<UInt2>()); }
		inline UInt4 valueAsUInt4() const	{ return valueAs(TSTypeToType<UInt4>()); }
		inline UInt8 valueAsUInt8() const	{ return valueAs(TSTypeToType<UInt8>()); }
		inline Float4 valueAsFloat4() const	{ return valueAs(TSTypeToType<Float4>()); }
		inline Float8 valueAsFloat8() const	{ return valueAs(TSTypeToType<Float8>()); }
		inline Bool valueAsBool() const		{ return valueAs(TSTypeToType<Bool>()); }
		inline CString valueAsString() const{ return valueAs(TSTypeToType<CString>()); }

	private:
		SInt1 valueAs(TSTypeToType<SInt1>) const;
		SInt2 valueAs(TSTypeToType<SInt2>) const;
		SInt4 valueAs(TSTypeToType<SInt4>) const;
		SInt8 valueAs(TSTypeToType<SInt8>) const;
		UInt1 valueAs(TSTypeToType<UInt1>) const;
		UInt2 valueAs(TSTypeToType<UInt2>) const;
		UInt4 valueAs(TSTypeToType<UInt4>) const;
		UInt8 valueAs(TSTypeToType<UInt8>) const;
		Float4 valueAs(TSTypeToType<Float4>) const;
		Float8 valueAs(TSTypeToType<Float8>) const;
		Bool valueAs(TSTypeToType<Bool>) const;
		CString valueAs(TSTypeToType<CString>) const;

	private:
		ENumberFormat mFormat;
		UNumberData mData;
};

LE_NAMESPACE_END
