#include "slCDictionary.h"

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CDictionary);

typedef std::map<CString, CObject::Ptr> CDictMap;
typedef CDictMap::iterator CDictIterator;
typedef CDictMap::const_iterator CDictConstIterator;

////////////////////////////////////////////////////////////////////////////////
// Auxiliary functions
////////////////////////////////////////////////////////////////////////////////
bool CDictionary::valueExists(const CString& key) const
{
	return (mData.find(key) != mData.end());
}

void CDictionary::deleteValue(const CString& key)
{
	CDictIterator it = mData.find(key);
	if(it != mData.end())
		mData.erase(it);
}

void CDictionary::clear()
{
	mData.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Value accessors
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T CDictionary::dynamic_make(const CString& key) const
{
	CDictConstIterator it = mData.find(key);
	if(it != mData.end())
	{
		const T* result = dynamic_cast<const T*>(((const CObject*)it->second));
		if (result) return *result;
	}
	return T();
}

CObject::Ptr CDictionary::_valueForKey(const CString& key, TSTypeToType<CObject::Ptr>) const
{
	CDictConstIterator it = mData.find(key);
	return (it != mData.end())?(it->second):(CObject::Ptr());
}

CString CDictionary::_valueForKey(const CString& key, TSTypeToType<CString>) const
{
	CDictConstIterator it = mData.find(key);
	if(it != mData.end())
	{
		const CString* string = dynamic_cast<const CString*>(((const CObject*)it->second));
		if (string) return *string;

		const CNumber* number = dynamic_cast<const CNumber*>(((const CObject*)it->second));
		if (number) return number->valueAsString();

		// TODO: convert other objects to CString with their description
	}
	return CString();
}

CNumber CDictionary::_valueForKey(const CString& key, TSTypeToType<CNumber>) const
{
	CDictConstIterator it = mData.find(key);
	if(it != mData.end())
	{
		const CNumber* number = dynamic_cast<const CNumber*>(((const CObject*)it->second));
		if (number) return *number;

		const CString* string = dynamic_cast<const CString*>(((const CObject*)it->second));
		if (string) return CNumber(*string);

		// TODO: convert other objects to CNumber with their description
	}
	return CNumber();
}

CTime CDictionary::_valueForKey(const CString& key, TSTypeToType<CTime>) const
{
	return dynamic_make<CTime>(key);
}

CData CDictionary::_valueForKey(const CString& key, TSTypeToType<CData>) const
{
	return dynamic_make<CData>(key);
}

UInt8 CDictionary::_valueForKey(const CString& key, TSTypeToType<UInt8>) const
{
	return valueAsNumberForKey(key).valueAs<UInt8>();
}

UInt16 CDictionary::_valueForKey(const CString& key, TSTypeToType<UInt16>) const
{
	return valueAsNumberForKey(key).valueAs<UInt16>();
}

UInt32 CDictionary::_valueForKey(const CString& key, TSTypeToType<UInt32>) const
{
	return valueAsNumberForKey(key).valueAs<UInt32>();
}

UInt64 CDictionary::_valueForKey(const CString& key, TSTypeToType<UInt64>) const
{
	return valueAsNumberForKey(key).valueAs<UInt64>();
}

SInt8 CDictionary::_valueForKey(const CString& key, TSTypeToType<SInt8>) const
{
	return valueAsNumberForKey(key).valueAs<SInt8>();
}

SInt16 CDictionary::_valueForKey(const CString& key, TSTypeToType<SInt16>) const
{
	return valueAsNumberForKey(key).valueAs<SInt16>();
}

SInt32 CDictionary::_valueForKey(const CString& key, TSTypeToType<SInt32>) const
{
	return valueAsNumberForKey(key).valueAs<SInt32>();
}

SInt64 CDictionary::_valueForKey(const CString& key, TSTypeToType<SInt64>) const
{
	return valueAsNumberForKey(key).valueAs<SInt64>();
}

Float32 CDictionary::_valueForKey(const CString& key, TSTypeToType<Float32>) const
{
	return valueAsNumberForKey(key).valueAs<Float32>();
}

Float64 CDictionary::_valueForKey(const CString& key, TSTypeToType<Float64>) const
{
	return valueAsNumberForKey(key).valueAs<Float64>();
}

bool CDictionary::_valueForKey(const CString& key, TSTypeToType<bool>) const
{
	return valueAsNumberForKey(key).valueAs<bool>();
}

////////////////////////////////////////////////////////////////////////////////
// Value setters
////////////////////////////////////////////////////////////////////////////////
void CDictionary::valueForKey(const CString& key, const CString& value)
{
	mData[key] = new CString(value);
}

void CDictionary::valueForKey(const CString& key, const CObject::Ptr value)
{
	mData[key] = value;
}

void CDictionary::valueForKey(const CString& key, const CTime& value)
{
	mData[key] = new CTime(value);
}
void CDictionary::valueForKey(const CString& key, const CNumber& value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, const CData& value)
{
	mData[key] = new CData(value);
}

void CDictionary::valueForKey(const CString& key, UInt8 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, UInt16 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, UInt32 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, UInt64 value)
{
	mData[key] = new CNumber(value);
}

void CDictionary::valueForKey(const CString& key, SInt8 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, SInt16 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, SInt32 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, SInt64 value)
{
	mData[key] = new CNumber(value);
}

void CDictionary::valueForKey(const CString& key, Float32 value)
{
	mData[key] = new CNumber(value);
}
void CDictionary::valueForKey(const CString& key, Float64 value)
{
	mData[key] = new CNumber(value);
}

void CDictionary::valueForKey(const CString& key, bool value)
{
	mData[key] = new CNumber(value);
}

LE_NAMESPACE_END
