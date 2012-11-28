#include <fstream>
#include <strstream>
#include "slCDictionary.h"
#include "slCURL.h"
#include "slCClassFactory.h"
#include "slCDataStream.h"
#include "base/slCXMLDictionaryParser.hp"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CDictionary);

////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef std::map<CString, CObject::Ptr> CDictMap;
typedef CDictMap::iterator CDictIterator;
typedef CDictMap::const_iterator CDictConstIterator;

////////////////////////////////////////////////////////////////////////////////
// Constants

#define cTypeAttributeKey LESTR("type")

CDictionary CDictionary::createFromStream(std::istream& stream)
{
	if (stream)
	{
		CXMLDictionaryParser parser;
		parser.parseStream(stream);
		return parser.dictionary();
	}
	return CDictionary();
}

CDictionary CDictionary::createWithContentsOfURL(const CURL& url)
{
	std::ifstream stream(url.path().UTF8String());
	return CDictionary::createFromStream(stream);
}

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

bool CDictionary::isEmpty() const
{
	return mData.empty();
}

UInt32 CDictionary::valueCount() const
{
	return mData.size();
}

void CDictionary::append(const CDictionary& dictionary, bool overwriteExistingValues)
{
	for (CDictConstIterator it = dictionary.mData.begin(); it != dictionary.mData.end(); ++it)
	{
		if (overwriteExistingValues)
		{
			mData[it->first] = it->second;
		}
		else
		{
			mData.insert(*it);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// Value accessors
////////////////////////////////////////////////////////////////////////////////
CObject::Ptr CDictionary::_valueForKey(const CString& key, CObject::Ptr defaultValue) const
{
	CDictConstIterator it = mData.find(key);
	return it == mData.end() ? defaultValue : it->second;
}

CString CDictionary::_valueForKey(const CString& key, const CString& defaultValue) const
{
	CObject::Ptr theObj = valueAsObjectForKey(key);
	CString* result = dynamic_cast<CString*>(theObj.get());
	return result ? *result : defaultValue;
}

CNumber CDictionary::_valueForKey(const CString& key, const CNumber& defaultValue) const
{
	CObject::Ptr theObj = valueAsObjectForKey(key);
	CNumber* result = dynamic_cast<CNumber*>(theObj.get());
	if (!result)
	{
		CString* string = dynamic_cast<CString*>(theObj.get());
		if (string)
		{
			return CNumber(*string);
		}
		return defaultValue;
	}
	return *result;
}

CTime CDictionary::_valueForKey(const CString& key, const CTime& defaultValue) const
{
	CObject::Ptr theObj = valueAsObjectForKey(key);
	CTime* result = dynamic_cast<CTime*>(theObj.get());
	return result ? *result : defaultValue;
}

CData CDictionary::_valueForKey(const CString& key, const CData& defaultValue) const
{
	CObject::Ptr theObj = valueAsObjectForKey(key);
	CData* result = dynamic_cast<CData*>(theObj.get());
	return result ? *result : defaultValue;
}

UInt8 CDictionary::_valueForKey(const CString& key, UInt8 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<UInt8>();
}

UInt16 CDictionary::_valueForKey(const CString& key, UInt16 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<UInt16>();
}

UInt32 CDictionary::_valueForKey(const CString& key, UInt32 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<UInt32>();
}

UInt64 CDictionary::_valueForKey(const CString& key, UInt64 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<UInt64>();
}

SInt8 CDictionary::_valueForKey(const CString& key, SInt8 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<SInt8>();
}

SInt16 CDictionary::_valueForKey(const CString& key, SInt16 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<SInt16>();
}

SInt32 CDictionary::_valueForKey(const CString& key, SInt32 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<SInt32>();
}

SInt64 CDictionary::_valueForKey(const CString& key, SInt64 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<SInt64>();
}

Float32 CDictionary::_valueForKey(const CString& key, Float32 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<Float32>();
}

Float64 CDictionary::_valueForKey(const CString& key, Float64 defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<Float64>();
}

Bool CDictionary::_valueForKey(const CString& key, Bool defaultValue) const
{
	return valueAsNumberForKey(key, defaultValue).valueAs<Bool>();
}

////////////////////////////////////////////////////////////////////////////////
// Value setters
////////////////////////////////////////////////////////////////////////////////
void CDictionary::setValueForKey(const CString& key, const CObject::Ptr value)
{
	mData[key] = value;
}

void CDictionary::setValueForKey(const CString& key, UInt8 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt16 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt32 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt64 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt8 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt16 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt32 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt64 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, Float32 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, Float64 value)
{
	setValueForKey(key, new CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, bool value)
{
	setValueForKey(key, new CNumber(value));
}

////////////////////////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////////////////////////
CString CDictionary::toString() const
{
	CDataStream stream;
	dump(stream);
	char* actualRes = new char[stream.size() + 1];
	memcpy(actualRes, stream.c_data(), stream.size());
	actualRes[stream.size()] = 0;
	return CString::__CStringNoCopyDeallocWithDelete(actualRes);
}

void CDictionary::dumpContents(std::ostream& stream) const
{
	for (CDictConstIterator it = mData.begin(); it != mData.end(); ++it)
	{
		stream << "<key>" << it->first << "</key>";
		CClass valClass = it->second->objectClass();
		if (valClass.isKindOfClass(CNumber::staticClass()))
		{
			const CNumber* number = dynamic_cast<const CNumber*>(it->second.get());
			LE_ASSERT(number);
			if (number->valueIsFloat())
			{
				stream << "<real>" << number->valueAsFloat64() << "</real>";
			}
			else if (number->valueIsBool())
			{
				stream << (number->valueAsBool() ? "<true/>" : "<false/>");
			}
			else
			{
				stream << "<integer>";
				if (number->valueIsSigned())
					stream << number->valueAsSInt64();
				else
					stream << number->valueAsUInt64();
				stream << "</integer>";
			}
		}
		else if (valClass.isKindOfClass(CString::staticClass()))
		{
			const CString* string = dynamic_cast<const CString*>(it->second.get());
			LE_ASSERT(string);
			if (string->isEmpty())
			{
				stream << "<string/>";
			}
			else
			{
				stream << "<string>" << *string << "</string>";
			}
		}
		else if (valClass.isKindOfClass(CDictionary::staticClass()))
		{
			const CDictionary* dict = dynamic_cast<const CDictionary*>(it->second.get());
			LE_ASSERT(dict);
			dict->dump(stream);
		}
		else
		{
			CDictionary dict;
			it->second->serialize(dict);
			stream << '<' << valClass.name();
			if (dict.isEmpty())
			{
				stream << "/>";
			}
			else
			{
				stream << '>';
				dict.dumpContents(stream);
				stream << "</" << valClass.name() << '>';
			}
		}
	}
}

void CDictionary::dump(std::ostream& stream) const
{
	if (isEmpty())
	{
		stream << "<dict/>";
	}
	else
	{
		stream << "<dict>";
		dumpContents(stream);
		stream << "</dict>";
	}
}


////////////////////////////////////////////////////////////////////////////////
// Serialization
////////////////////////////////////////////////////////////////////////////////
void CDictionary::serialize(CDictionary& toDictionary) const
{
	toDictionary.append(*this);
}

void CDictionary::deserialize(const CDictionary& fromDictionary)
{
	*this = fromDictionary;
}

	} // namespace le
} // namespace sokira
