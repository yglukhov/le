#if !defined SL_LE_core_slCNumber_h
#define SL_LE_core_slCNumber_h

#include <le/core/slCObject.h>
#include <le/core/template/util/slTSConstToType.h>
#include <le/core/slCString.h>
#include "base/slCNumberBase.h"

namespace sokira
{
	namespace le
	{

class CNumber : public CObject, CNumberBase
{
	LE_DECLARE_RUNTIME_CLASS(CNumber);

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
		CNumber(const CDictionary& fromDict);

		CNumber(const CNumber& copy);

		const CNumber& operator++();		// prefix
		const CNumber operator++(int);		// postfix

		const CNumber& operator--();		// prefix
		const CNumber operator--(int);		// postfix

		const CNumber& operator=(SInt8 value);
		const CNumber& operator=(SInt16 value);
		const CNumber& operator=(SInt32 value);
		const CNumber& operator=(SInt64 value);
		const CNumber& operator=(UInt8 value);
		const CNumber& operator=(UInt16 value);
		const CNumber& operator=(UInt32 value);
		const CNumber& operator=(UInt64 value);
		const CNumber& operator=(Float32 value);
		const CNumber& operator=(Float64 value);
		const CNumber& operator=(Bool value);
		const CNumber& operator=(const CString& value);

		const CNumber& operator+=(const CNumber& value);
		const CNumber& operator-=(const CNumber& value);
		const CNumber& operator*=(const CNumber& value);
		const CNumber& operator/=(const CNumber& value);

		void setBigEndianValue(UInt32);
		void setBigEndianValue(UInt64);
		void setBigEndianValue(UInt16);
		void setBigEndianValue(SInt64);
		void setBigEndianValue(SInt32);
		void setBigEndianValue(SInt16);

		void setLittleEndianValue(UInt64);
		void setLittleEndianValue(UInt32);
		void setLittleEndianValue(UInt16);
		void setLittleEndianValue(SInt64);
		void setLittleEndianValue(SInt32);
		void setLittleEndianValue(SInt16);

		template <typename T>
		inline T valueAs() const { return valueAs(TSTypeToType<T>()); }

		inline SInt8 valueAsSInt8() const	{ return valueAs<SInt8>(); }
		inline SInt16 valueAsSInt16() const	{ return valueAs<SInt16>(); }
		inline SInt32 valueAsSInt32() const	{ return valueAs<SInt32>(); }
		inline SInt64 valueAsSInt64() const	{ return valueAs<SInt64>(); }
		inline UInt8 valueAsUInt8() const	{ return valueAs<UInt8>(); }
		inline UInt16 valueAsUInt16() const	{ return valueAs<UInt16>(); }
		inline UInt32 valueAsUInt32() const	{ return valueAs<UInt32>(); }
		inline UInt64 valueAsUInt64() const	{ return valueAs<UInt64>(); }
		inline Float32 valueAsFloat32() const	{ return valueAs<Float32>(); }
		inline Float64 valueAsFloat64() const	{ return valueAs<Float64>(); }
		inline Bool valueAsBool() const		{ return valueAs<Bool>(); }

		inline SInt valueAsSInt() const		{ return valueAs<SInt>(); }
		inline SIntS valueAsSIntS() const		{ return valueAs<SIntS>(); }
//		inline SIntL valueAsSIntL() const		{ return valueAs<SIntL>(); }
		inline SIntLL valueAsSIntLL() const		{ return valueAs<SIntLL>(); }

		inline UInt valueAsUInt() const		{ return valueAs<UInt>(); }
		inline UIntS valueAsUIntS() const		{ return valueAs<UIntS>(); }
//		inline UIntL valueAsUIntL() const		{ return valueAs<UIntL>(); }
		inline UIntLL valueAsUIntLL() const		{ return valueAs<UIntLL>(); }

		inline CString valueAsString() const{ return valueAs<CString>(); }

		template <typename T>
		inline Bool valueIs() const { return mFormat == (EFormat)TSTypeToFormat<T>::dataType; }

		inline Bool valueIsSInt8() const { return valueIs<SInt8>(); }
		inline Bool valueIsSInt16() const { return valueIs<SInt16>(); }
		inline Bool valueIsSInt32() const { return valueIs<SInt32>(); }
		inline Bool valueIsSInt64() const { return valueIs<SInt64>(); }

		inline Bool valueIsUInt8() const { return valueIs<UInt8>(); }
		inline Bool valueIsUInt16() const { return valueIs<UInt16>(); }
		inline Bool valueIsUInt32() const { return valueIs<UInt32>(); }
		inline Bool valueIsUInt64() const { return valueIs<UInt64>(); }

		inline Bool valueIsSInt() const { return valueIs<SInt>(); }
		inline Bool valueIsSIntS() const { return valueIs<SIntS>(); }
//		inline Bool valueIsSIntL() const { return valueIs<SIntL>(); }
		inline Bool valueIsSIntLL() const { return valueIs<SIntLL>(); }

		inline Bool valueIsUInt() const { return valueIs<UInt>(); }
		inline Bool valueIsUIntS() const { return valueIs<UIntS>(); }
//		inline Bool valueIsUIntL() const { return valueIs<UIntL>(); }
		inline Bool valueIsUIntLL() const { return valueIs<UIntLL>(); }

		inline Bool valueIsFloat32() const { return valueIs<Float32>(); }
		inline Bool valueIsFloat64() const { return valueIs<Float64>(); }

		inline Bool valueIsBool() const { return valueIs<Bool>(); }

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

		// Endian conversion
		static UInt64 hostToBigEndian(UInt64 value);
		static UInt32 hostToBigEndian(UInt32 value);
		static UInt16 hostToBigEndian(UInt16 value);
		static SInt64 hostToBigEndian(SInt64 value);
		static SInt32 hostToBigEndian(SInt32 value);
		static SInt16 hostToBigEndian(SInt16 value);

		static UInt64 hostToLittleEndian(UInt64 value);
		static UInt32 hostToLittleEndian(UInt32 value);
		static UInt16 hostToLittleEndian(UInt16 value);
		static SInt64 hostToLittleEndian(SInt64 value);
		static SInt32 hostToLittleEndian(SInt32 value);
		static SInt16 hostToLittleEndian(SInt16 value);

		static UInt64 bigEndianToHost(UInt64 value);
		static UInt32 bigEndianToHost(UInt32 value);
		static UInt16 bigEndianToHost(UInt16 value);
		static SInt64 bigEndianToHost(SInt64 value);
		static SInt32 bigEndianToHost(SInt32 value);
		static SInt16 bigEndianToHost(SInt16 value);

		static UInt64 littleEndianToHost(UInt64 value);
		static UInt32 littleEndianToHost(UInt32 value);
		static UInt16 littleEndianToHost(UInt16 value);
		static SInt64 littleEndianToHost(SInt64 value);
		static SInt32 littleEndianToHost(SInt32 value);
		static SInt16 littleEndianToHost(SInt16 value);

		static UInt64 littleEndianToBigEndian(UInt64 value);
		static UInt32 littleEndianToBigEndian(UInt32 value);
		static UInt16 littleEndianToBigEndian(UInt16 value);
		static SInt64 littleEndianToBigEndian(SInt64 value);
		static SInt32 littleEndianToBigEndian(SInt32 value);
		static SInt16 littleEndianToBigEndian(SInt16 value);

		static UInt64 bigEndianToLittleEndian(UInt64 value);
		static UInt32 bigEndianToLittleEndian(UInt32 value);
		static UInt16 bigEndianToLittleEndian(UInt16 value);
		static SInt64 bigEndianToLittleEndian(SInt64 value);
		static SInt32 bigEndianToLittleEndian(SInt32 value);
		static SInt16 bigEndianToLittleEndian(SInt16 value);

		template <typename T>
		static Bool isPowerOf2(T val)
		{
			return (val & (val - 1)) == 0;
		}

		template <typename T>
		static T nearestHigherPowerOf2(T val)
		{
			--val;
			val |= val >> 1;
			val |= val >> 2;
			val |= val >> 4;
			val |= val >> 8;
			val |= val >> 16;
			return ++val;
		}

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
		UNumberData mData;
		EFormat mFormat;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCNumber_h
