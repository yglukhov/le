#if !defined SL_LE_core_slCDictionary_h
#define SL_LE_core_slCDictionary_h

#include <map>

#include "slCNumber.h"
#include "slCTime.h"
#include "slCData.h"

namespace sokira
{
	namespace le
	{

class CURL;

class CDictionary : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CDictionary)
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELECTOR_WITH_NAME(valueAsObjectForKey, valueForKey)
		LE_RTTI_SELECTOR_WITH_TYPE(setValueForKey, void, (const CString&, const CObject::Ptr))
	LE_RTTI_END

	public:
		//CDictionary(const CString& rootKey = LESTR("dict"));
		static CDictionary createFromStream(std::istream& stream);
		static CDictionary createWithContentsOfURL(const CURL& url);

		CDictionary() {}

#ifdef LE_CPP11
		template <typename ... T>
		CDictionary(const CString& key, T...args)
		{
			initWithKeysAndValues(key, args...);
		}
#endif

		////////////////////////////////////////////////////////////////////////
		// Value accessors
		////////////////////////////////////////////////////////////////////////
		template <typename T>
		inline T valueForKey(const CString& key, T defaultValue) const
		{
			return _valueForKey(key, defaultValue);
		}

		inline CObject::Ptr valueAsObjectForKey(const CString& key, CObject::Ptr defaultValue = CObject::Ptr()) const // Gets the mutable reference
			{ return valueForKey<CObject::Ptr>(key, defaultValue); }
		inline CString valueAsStringForKey(const CString& key, const CString& defaultValue = CString()) const
			{ return valueForKey<CString>(key, defaultValue); }
		inline CNumber valueAsNumberForKey(const CString& key, const CNumber& defaultValue = CNumber()) const
			{ return valueForKey<CNumber>(key, defaultValue); }
		inline CTime valueAsTimeForKey(const CString& key, const CTime& defaultValue = CTime()) const
			{ return valueForKey<CTime>(key, defaultValue); }
		inline CData valueAsDataForKey(const CString& key, const CData& defaultValue = CData()) const
			{ return valueForKey<CData>(key, defaultValue); }

		inline UInt8 valueAsUInt8ForKey(const CString& key, UInt8 defaultValue = 0) const
			{ return valueForKey<UInt8>(key, defaultValue); }
		inline UInt16 valueAsUInt16ForKey(const CString& key, UInt16 defaultValue = 0) const
			{ return valueForKey<UInt16>(key, defaultValue); }
		inline UInt32 valueAsUInt32ForKey(const CString& key, UInt32 defaultValue = 0) const
			{ return valueForKey<UInt32>(key, defaultValue); }
		inline UInt64 valueAsUInt64ForKey(const CString& key, UInt64 defaultValue = 0) const
			{ return valueForKey<UInt64>(key, defaultValue); }

		inline SInt8 valueAsSInt8ForKey(const CString& key, SInt8 defaultValue = 0) const
			{ return valueForKey<SInt8>(key, defaultValue); }
		inline SInt16 valueAsSInt16ForKey(const CString& key, SInt16 defaultValue = 0) const
			{ return valueForKey<SInt16>(key, defaultValue); }
		inline SInt32 valueAsSInt32ForKey(const CString& key, SInt32 defaultValue = 0) const
			{ return valueForKey<SInt32>(key, defaultValue); }
		inline SInt64 valueAsSInt64ForKey(const CString& key, SInt64 defaultValue = 0) const
			{ return valueForKey<SInt64>(key, defaultValue); }

		inline Float32 valueAsFloat32ForKey(const CString& key, Float32 defaultValue = 0) const
			{ return valueForKey<Float32>(key, defaultValue); }
		inline Float64 valueAsFloat64ForKey(const CString& key, Float64 defaultValue = 0) const
			{ return valueForKey<Float64>(key, defaultValue); }

		inline Bool valueAsBoolForKey(const CString& key, Bool defaultValue = 0) const
			{ return valueForKey<Bool>(key, defaultValue); }

		////////////////////////////////////////////////////////////////////////
		// Value setters
		////////////////////////////////////////////////////////////////////////
		void setValueForKey(const CString& key, const CObject::Ptr value);	// Stores the mutable reference
		inline void setValueForKey(const CString& key, const CObject* value)
		{
			value->retain();
			setValueForKey(key, CObject::Ptr(const_cast<CObject*>(value)));
		}

		inline void setValueForKey(const CString& key, const CString& value)
			{ setValueForKey(key, new CString(value)); }

		void setValueForKey(const CString& key, UInt8 value);
		void setValueForKey(const CString& key, UInt16 value);
		void setValueForKey(const CString& key, UInt32 value);
		void setValueForKey(const CString& key, UInt64 value);

		void setValueForKey(const CString& key, SInt8 value);
		void setValueForKey(const CString& key, SInt16 value);
		void setValueForKey(const CString& key, SInt32 value);
		void setValueForKey(const CString& key, SInt64 value);

		void setValueForKey(const CString& key, Float32 value);
		void setValueForKey(const CString& key, Float64 value);

		void setValueForKey(const CString& key, bool value);

		////////////////////////////////////////////////////////////////////////
		// Auxiliary functions
		////////////////////////////////////////////////////////////////////////
		bool valueExists(const CString& key) const;
		void deleteValue(const CString& key);
		void clear();
		bool isEmpty() const;
		UInt32 valueCount() const;
		void append(const CDictionary& dictionary, bool overwriteExistingValues = true);

	public:

		///////////////////////////////////////////////////////////////////////
		// Operators
		///////////////////////////////////////////////////////////////////////
		bool operator == (const CDictionary& rhs) const;
	//	const CDictionary

		CString toString() const;
		void dump(std::ostream& stream) const;

		///////////////////////////////////////////////////////////////////////
		// Serialization
		///////////////////////////////////////////////////////////////////////
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

		virtual CString description() const
		{
			return toString();
		}

	private:
	
#ifdef LE_CPP11
		template <typename TObj, typename ... T>
		void initWithKeysAndValues(const CString& key, TObj obj, T...args)
		{
			setValueForKey(key, obj);
			initWithKeysAndValues(args...);
		}

		void initWithKeysAndValues()
		{
			
		}
#endif

		void dumpContents(std::ostream& stream) const;

		CObject::Ptr _valueForKey(const CString& key, CObject::Ptr defaultValue) const;
		CString _valueForKey(const CString& key, const CString& defaultValue) const;
		CNumber _valueForKey(const CString& key, const CNumber& defaultValue) const;
		CTime _valueForKey(const CString& key, const CTime& defaultValue) const;
		CData _valueForKey(const CString& key, const CData& defaultValue) const;
		UInt8 _valueForKey(const CString& key, UInt8 defaultValue) const;
		UInt16 _valueForKey(const CString& key, UInt16 defaultValue) const;
		UInt32 _valueForKey(const CString& key, UInt32 defaultValue) const;
		UInt64 _valueForKey(const CString& key, UInt64 defaultValue) const;
		SInt8 _valueForKey(const CString& key, SInt8 defaultValue) const;
		SInt16 _valueForKey(const CString& key, SInt16 defaultValue) const;
		SInt32 _valueForKey(const CString& key, SInt32 defaultValue) const;
		SInt64 _valueForKey(const CString& key, SInt64 defaultValue) const;
		Float32 _valueForKey(const CString& key, Float32 defaultValue) const;
		Float64 _valueForKey(const CString& key, Float64 defaultValue) const;
		Bool _valueForKey(const CString& key, Bool defaultValue) const;

		std::map<CString, CObject::Ptr> mData;
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCDictionary_h
