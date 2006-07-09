#pragma once

#include <common/slCObject.h>
#include <template/util/slTSConstToType.h>
#include <common/types/slCString.h>
#include "base/slCNumberBase.h"

LE_NAMESPACE_START

class CNumber : public CObject, CNumberBase
{
	DECLARE_RUNTIME_CLASS(CNumber);

	public:
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

		template <typename T>
		inline bool valueIs() const
		{
			return _valueIs(TSTypeToType<T>());
		}

		inline bool valueIs(EFormat format) const
		{
			return (mFormat == format);
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

		template <typename T>
		inline bool _valueIs(TSTypeToType<T>) const
			{ return false;}
		inline bool _valueIs(TSTypeToType<SInt8>) const
			{ return valueIs(eFormatSInt8); }
		inline bool _valueIs(TSTypeToType<SInt16>) const
			{ return valueIs(eFormatSInt16); }
		inline bool _valueIs(TSTypeToType<SInt32>) const
			{ return valueIs(eFormatSInt32); }
		inline bool _valueIs(TSTypeToType<SInt64>) const
			{ return valueIs(eFormatSInt64); }
		inline bool _valueIs(TSTypeToType<UInt8>) const
			{ return valueIs(eFormatUInt8); }
		inline bool _valueIs(TSTypeToType<UInt16>) const
			{ return valueIs(eFormatUInt16); }
		inline bool _valueIs(TSTypeToType<UInt32>) const
			{ return valueIs(eFormatUInt32); }
		inline bool _valueIs(TSTypeToType<UInt64>) const
			{ return valueIs(eFormatUInt64); }
		inline bool _valueIs(TSTypeToType<Float32>) const
			{ return valueIs(eFormatFloat32); }
		inline bool _valueIs(TSTypeToType<Float64>) const
			{ return valueIs(eFormatFloat64); }
		inline bool _valueIs(TSTypeToType<bool>) const
			{ return valueIs(eFormatBool); }

	private:
		EFormat mFormat;
		UNumberData mData;
};

LE_NAMESPACE_END
