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

		CNumber(SInt8 value);
		CNumber(SInt16 value);
		CNumber(SInt32 value);
		CNumber(SInt64 value);

		CNumber(UInt8 value);
		CNumber(UInt16 value);
		CNumber(UInt32 value);
		CNumber(UInt64 value);

		CNumber(Float32 value);
		CNumber(Float64 value);

		CNumber(Bool value);

		CNumber(const CString& value);

		CNumber(const CNumber& copy);

		template <typename T>
		inline T valueAs() const
		{
			return valueAs(TSTypeToType<T>());
		}

		const CNumber& operator++();		// prefix
		const CNumber operator++(int);		// postfix

		inline SInt8 valueAsSInt8() const	{ return valueAs(TSTypeToType<SInt8>()); }
		inline SInt16 valueAsSInt16() const	{ return valueAs(TSTypeToType<SInt16>()); }
		inline SInt32 valueAsSInt32() const	{ return valueAs(TSTypeToType<SInt32>()); }
		inline SInt64 valueAsSInt64() const	{ return valueAs(TSTypeToType<SInt64>()); }
		inline UInt8 valueAsUInt8() const	{ return valueAs(TSTypeToType<UInt8>()); }
		inline UInt16 valueAsUInt16() const	{ return valueAs(TSTypeToType<UInt16>()); }
		inline UInt32 valueAsUInt32() const	{ return valueAs(TSTypeToType<UInt32>()); }
		inline UInt64 valueAsUInt64() const	{ return valueAs(TSTypeToType<UInt64>()); }
		inline Float32 valueAsFloat32() const	{ return valueAs(TSTypeToType<Float32>()); }
		inline Float64 valueAsFloat64() const	{ return valueAs(TSTypeToType<Float64>()); }
		inline Bool valueAsBool() const		{ return valueAs(TSTypeToType<Bool>()); }
		inline CString valueAsString() const{ return valueAs(TSTypeToType<CString>()); }

	private:
		SInt8 valueAs(TSTypeToType<SInt8>) const;
		SInt16 valueAs(TSTypeToType<SInt16>) const;
		SInt32 valueAs(TSTypeToType<SInt32>) const;
		SInt64 valueAs(TSTypeToType<SInt64>) const;
		UInt8 valueAs(TSTypeToType<UInt8>) const;
		UInt16 valueAs(TSTypeToType<UInt16>) const;
		UInt32 valueAs(TSTypeToType<UInt32>) const;
		UInt64 valueAs(TSTypeToType<UInt64>) const;
		Float32 valueAs(TSTypeToType<Float32>) const;
		Float64 valueAs(TSTypeToType<Float64>) const;
		Bool valueAs(TSTypeToType<Bool>) const;
		CString valueAs(TSTypeToType<CString>) const;

	private:
		ENumberFormat mFormat;
		UNumberData mData;
};

LE_NAMESPACE_END
