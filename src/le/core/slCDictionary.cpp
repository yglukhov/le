#include <fstream>
#include "slCDictionary.h"
#include "slCURL.h"
#include "slCClassFactory.h"
#include "base/slCXMLDictionaryParser.hp"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CDictionary);

////////////////////////////////////////////////////////////////////////////////
// Typedefs
typedef std::map<CString, CDictionary> CDictMap;
typedef CDictMap::iterator CDictIterator;
typedef CDictMap::const_iterator CDictConstIterator;

////////////////////////////////////////////////////////////////////////////////
// Constants

#define cTypeAttributeKey LESTR("type")

CDictionary::CDictionary(const CString& rootKey) :
	mRootKey(rootKey)
{

}

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
	mRootValue.clear();
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
	if (dictionary.mData.empty() && !dictionary.mRootValue.isEmpty())
	{
		setRootValue(dictionary.mRootValue);
	}
	else
	{
		for (CDictConstIterator it = dictionary.mData.begin(); it != dictionary.mData.end(); ++it)
		{
			if (overwriteExistingValues || !valueExists(it->first))
			{
				mData[it->first] = it->second;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Root modifiers
////////////////////////////////////////////////////////////////////////
void CDictionary::setRootKey(const CString& key)
{
	mRootKey = key;
}

CString CDictionary::rootKey() const
{
	return mRootKey;
}

void CDictionary::setRootValue(const CString& value)
{
	mData.clear();
	// Try to parse value and split it to key-value structure.
	mRootValue = value;
}

CString CDictionary::rootValue() const
{
	if (!mRootValue.isEmpty())
	{
		return mRootValue;
	}

	for (CDictConstIterator it = mData.begin(); it != mData.end(); ++it)
	{
		mRootValue += it->second.toString();
	}

	return mRootValue;
}

////////////////////////////////////////////////////////////////////////////////
// Value accessors
////////////////////////////////////////////////////////////////////////////////
CObject::Ptr CDictionary::_valueForKey(const CString& key, CObject::Ptr defaultValue) const
{
	CDictConstIterator it = mData.find(key);
	if (it != mData.end())
	{
		CObject::Ptr newObj = CClassFactory::defaultInstance()->create<CObject>(it->second.attributeForKey(cTypeAttributeKey));
		if (newObj)
		{
			newObj->deserialize(it->second);
		}
		return newObj;
	}
	return defaultValue;
}

CString CDictionary::_valueForKey(const CString& key, const CString& defaultValue) const
{
	CDictConstIterator it = mData.find(key);
	return (it == mData.end())? defaultValue : CString(it->second);
}

CNumber CDictionary::_valueForKey(const CString& key, const CNumber& defaultValue) const
{
	CDictConstIterator it = mData.find(key);
	return (it == mData.end())? defaultValue : CNumber(it->second);
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
void CDictionary::setValueForKey(const CString& key, const CObject& value)
{
	mRootValue.clear();
	CDictionary newDict(key);
	newDict.setAttributeForKey(cTypeAttributeKey, value.objectClass().name());
	value.serialize(newDict);
	mData[key] = newDict;
}

void CDictionary::setValueForKey(const CString& key, const CObject::Ptr value)
{
	// TODO: Complete linkage
	CDictionary::setValueForKey(key, *value);
}

void CDictionary::setValueForKey(const CString& key, UInt8 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt16 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt32 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, UInt64 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt8 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt16 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt32 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, SInt64 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, Float32 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, Float64 value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

void CDictionary::setValueForKey(const CString& key, bool value)
{
	CDictionary::setValueForKey(key, CNumber(value));
}

////////////////////////////////////////////////////////////////////////////////
// Attribute management
////////////////////////////////////////////////////////////////////////////////
CString CDictionary::attributeForKey(const CString& key) const
{
	std::map<CString, CString>::const_iterator it = mAttributes.find(key);
	return (it == mAttributes.end())?(CString()):(it->second);
}

void CDictionary::setAttributeForKey(const CString& key, const CString& attribute)
{
	mAttributes[key] = attribute;
}

bool CDictionary::attributeExists(const CString& key) const
{
	std::map<CString, CString>::const_iterator it = mAttributes.find(key);
	return (it != mAttributes.end());
}

UInt32 CDictionary::attributeCount() const
{
	return mAttributes.size();
}

void CDictionary::deleteAttribute(const CString& key)
{
	mAttributes.erase(key);
}

void CDictionary::deleteAllAttributes()
{
	mAttributes.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////////////////////////////////
CString CDictionary::toString() const
{
	CString result = "<" + mRootKey;

	std::map<CString, CString>::const_iterator it = mAttributes.begin();
	for(; it != mAttributes.end(); ++it)
	{
		result += " " + it->first + "=\"" + it->second + "\"";
	}

	result += ">" + rootValue() + "</" + mRootKey + ">";
	return result;
}

void CDictionary::dump(std::ostream& stream) const
{
	stream << '<' << mRootKey;

	std::map<CString, CString>::const_iterator it = mAttributes.begin();
	for(; it != mAttributes.end(); ++it)
	{
		stream << ' ' << it->first << "=\"" << it->second << '\"';
	}

	stream << '>' << rootValue() << "</" << mRootKey << '>';
}


////////////////////////////////////////////////////////////////////////////////
// Serialization
////////////////////////////////////////////////////////////////////////////////
void CDictionary::serialize(CDictionary& toDictionary) const
{
	// Saving attributes
	for (std::map<CString, CString>::const_iterator it = mAttributes.begin(); it != mAttributes.end(); ++it)
		toDictionary.setAttributeForKey(it->first, it->second);

	toDictionary.append(*this);
}

void CDictionary::deserialize(const CDictionary& fromDictionary)
{
	*this = fromDictionary;
	deleteAttribute(cTypeAttributeKey);
}

	} // namespace le
} // namespace sokira
