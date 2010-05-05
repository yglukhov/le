#include "slCDictionary.h"
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
	CXMLDictionaryParser parser;
	if (stream)
	{
		parser.parseStream(stream);
		return parser.dictionary();
	}
	return CDictionary();
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
CObject::Ptr CDictionary::_valueForKey(const CString& key, TSTypeToType<CObject::Ptr>) const
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
	return NULL;
}

CString CDictionary::_valueForKey(const CString& key, TSTypeToType<CString>) const
{
	CDictConstIterator it = mData.find(key);
	return (it == mData.end())?(CString()):(CString(it->second));
}

CNumber CDictionary::_valueForKey(const CString& key, TSTypeToType<CNumber>) const
{
	CDictConstIterator it = mData.find(key);
	return (it == mData.end())?(CNumber()):(CNumber(it->second));
}

CTime CDictionary::_valueForKey(const CString& key, TSTypeToType<CTime>) const
{
	CObject::Ptr theObj = valueForKey<CObject::Ptr>(key);
	CTime* result = dynamic_cast<CTime*>(theObj.get());
	return (result)?(*result):(CTime());
}

CData CDictionary::_valueForKey(const CString& key, TSTypeToType<CData>) const
{
	CObject::Ptr theObj = valueForKey<CObject::Ptr>(key);
	CData* result = dynamic_cast<CData*>(theObj.get());
	return (result)?(*result):(CData());
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
void CDictionary::valueForKey(const CString& key, const CObject& value)
{
	mRootValue.clear();
	CDictionary newDict(key);
	newDict.attributeForKey(cTypeAttributeKey, value.objectClass().name());
	value.serialize(newDict);
	mData[key] = newDict;
}

void CDictionary::valueForKey(const CString& key, const CObject::Ptr value)
{
	// TODO: Complete linkage
	CDictionary::valueForKey(key, *value);
}

void CDictionary::valueForKey(const CString& key, UInt8 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, UInt16 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, UInt32 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, UInt64 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, SInt8 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, SInt16 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, SInt32 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, SInt64 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, Float32 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, Float64 value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

void CDictionary::valueForKey(const CString& key, bool value)
{
	CDictionary::valueForKey(key, CNumber(value));
}

////////////////////////////////////////////////////////////////////////////////
// Attribute management
////////////////////////////////////////////////////////////////////////////////
CString CDictionary::attributeForKey(const CString& key) const
{
	std::map<CString, CString>::const_iterator it = mAttributes.find(key);
	return (it == mAttributes.end())?(CString()):(it->second);
}

void CDictionary::attributeForKey(const CString& key, const CString& attribute)
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
		toDictionary.attributeForKey(it->first, it->second);

	toDictionary.append(*this);
}

void CDictionary::deserialize(const CDictionary& fromDictionary)
{
	*this = fromDictionary;
	deleteAttribute(cTypeAttributeKey);
}

	} // namespace le
} // namespace sokira
