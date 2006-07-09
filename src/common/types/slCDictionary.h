#pragma once

#include <map>

#include "slCNumber.h"
#include "slCTime.h"
#include "slCData.h"

LE_NAMESPACE_START

class CDictionary : public CObject
{
	DECLARE_RUNTIME_CLASS(CDictionary);

	public:
		////////////////////////////////////////////////////////////////////////
		// Value accessors
		////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline T valueForKey(const CString& key) const
		{
			return _valueForKey(key, TSTypeToType<T>());
		}

		inline CObject::Ptr valueAsObjectForKey(const CString& key) const // Gets the mutable reference
			{ return valueForKey<CObject::Ptr>(key); }
		inline CString valueAsStringForKey(const CString& key) const
			{ return valueForKey<CString>(key); }
		inline CNumber valueAsNumberForKey(const CString& key) const
			{ return valueForKey<CNumber>(key); }
		inline CTime valueAsTimeForKey(const CString& key) const
			{ return valueForKey<CTime>(key); }
		inline CData valueAsDataForKey(const CString& key) const
			{ return valueForKey<CData>(key); }

		inline UInt8 valueAsUInt8ForKey(const CString& key) const
			{ return valueForKey<UInt8>(key); }
		inline UInt16 valueAsUInt16ForKey(const CString& key) const
			{ return valueForKey<UInt16>(key); }
		inline UInt32 valueAsUInt32ForKey(const CString& key) const
			{ return valueForKey<UInt32>(key); }
		inline UInt64 valueAsUInt64ForKey(const CString& key) const
			{ return valueForKey<UInt64>(key); }

		inline SInt8 valueAsSInt8ForKey(const CString& key) const
			{ return valueForKey<SInt8>(key); }
		inline SInt16 valueAsSInt16ForKey(const CString& key) const
			{ return valueForKey<SInt16>(key); }
		inline SInt32 valueAsSInt32ForKey(const CString& key) const
			{ return valueForKey<SInt32>(key); }
		inline SInt64 valueAsSInt64ForKey(const CString& key) const
			{ return valueForKey<SInt64>(key); }

		inline Float32 valueAsFloat32ForKey(const CString& key) const
			{ return valueForKey<Float32>(key); }
		inline Float64 valueAsFloat64ForKey(const CString& key) const
			{ return valueForKey<Float64>(key); }

		inline bool valueAsBoolForKey(const CString& key) const
			{ return valueForKey<Bool>(key); }

		////////////////////////////////////////////////////////////////////////
		// Value setters
		////////////////////////////////////////////////////////////////////////
		void valueForKey(const CString& key, const CString& value);
		void valueForKey(const CString& key, const CObject::Ptr value);	// Stores the mutable reference
		void valueForKey(const CString& key, const CTime& value);
		void valueForKey(const CString& key, const CNumber& value);
		void valueForKey(const CString& key, const CData& value);

		void valueForKey(const CString& key, UInt8 value);
		void valueForKey(const CString& key, UInt16 value);
		void valueForKey(const CString& key, UInt32 value);
		void valueForKey(const CString& key, UInt64 value);

		void valueForKey(const CString& key, SInt8 value);
		void valueForKey(const CString& key, SInt16 value);
		void valueForKey(const CString& key, SInt32 value);
		void valueForKey(const CString& key, SInt64 value);

		void valueForKey(const CString& key, Float32 value);
		void valueForKey(const CString& key, Float64 value);

		void valueForKey(const CString& key, bool value);

		////////////////////////////////////////////////////////////////////////
		// Auxiliary functions
		////////////////////////////////////////////////////////////////////////
		bool valueExists(const CString& key) const;
		void deleteValue(const CString& key);
		void clear();

	private:
		CObject::Ptr _valueForKey(const CString& key, TSTypeToType<CObject::Ptr>) const;
		CString _valueForKey(const CString& key, TSTypeToType<CString>) const;
		CNumber _valueForKey(const CString& key, TSTypeToType<CNumber>) const;
		CTime _valueForKey(const CString& key, TSTypeToType<CTime>) const;
		CData _valueForKey(const CString& key, TSTypeToType<CData>) const;
		UInt8 _valueForKey(const CString& key, TSTypeToType<UInt8>) const;
		UInt16 _valueForKey(const CString& key, TSTypeToType<UInt16>) const;
		UInt32 _valueForKey(const CString& key, TSTypeToType<UInt32>) const;
		UInt64 _valueForKey(const CString& key, TSTypeToType<UInt64>) const;
		SInt8 _valueForKey(const CString& key, TSTypeToType<SInt8>) const;
		SInt16 _valueForKey(const CString& key, TSTypeToType<SInt16>) const;
		SInt32 _valueForKey(const CString& key, TSTypeToType<SInt32>) const;
		SInt64 _valueForKey(const CString& key, TSTypeToType<SInt64>) const;
		Float32 _valueForKey(const CString& key, TSTypeToType<Float32>) const;
		Float64 _valueForKey(const CString& key, TSTypeToType<Float64>) const;
		bool _valueForKey(const CString& key, TSTypeToType<bool>) const;

		template <typename T>
		inline T dynamic_make(const CString& key) const;

		std::map<CString, CObject::Ptr> mData;
};


LE_NAMESPACE_END
