#include <le/core/template/function/slTCBind.h>
#include <le/core/slCDictionary.h>
#include "slCXMLDictionaryParser.hp"

namespace sokira
{
	namespace le
	{

static CString cDict = LESTR("dict");

CXMLDictionaryParser::~CXMLDictionaryParser()
{
	while (!mDictStack.empty())
	{
		delete mDictStack.back();
		mDictStack.pop_back();
	}
}

void CXMLDictionaryParser::parseStream(std::istream& stream)
{
	mIsPlist = false;
	mKey = cDict;

	CXMLParser parser;
	parser.setTrimsWhitespace();

	CXMLParser::TOnStartTag onStart = bind(&CXMLDictionaryParser::onStartTag, this, bindTo(0), bindTo(1), bindTo(2));
	parser.setOnStartTag(onStart);
	CXMLParser::TOnEndTag onEnd = bind(&CXMLDictionaryParser::onEndTag, this, bindTo(0), bindTo(1));
	parser.setOnEndTag(onEnd);
	CXMLParser::TOnEndTag onError = bind(&CXMLDictionaryParser::onError, this, bindTo(0), bindTo(1));
	parser.setOnError(onError);
	CXMLParser::TOnData onData = bind(&CXMLDictionaryParser::onData, this, bindTo(0), bindTo(1));
	parser.setOnData(onData);
	parser.parseStream(stream);
}

CDictionary CXMLDictionaryParser::dictionary()
{
	if (!mDictStack.empty())
	{
		return CDictionary(*mDictStack.front());
	}
	return CDictionary();
}

void CXMLDictionaryParser::onStartTag(CXMLParser*, CString name, CXMLParser::TArrtibutes attributes)
{
	if (name == "?xml") return;
	if (name == "!DOCTYPE" && attributes.find("plist") != attributes.end())
	{
		mIsPlist = true;
		return;
	}

	if (mIsPlist)
	{
		mLastTag = name;
		if (name == cDict)
		{
			CDictionary* newDict = new CDictionary(mKey);
			mDictStack.push_back(newDict);
		}
		else if (name == "true")
		{
			mDictStack.back()->setValueForKey(mKey, true);
		}
		else if (name == "false")
		{
			mDictStack.back()->setValueForKey(mKey, false);
		}
	}
	else
	{
		CDictionary* newDict = new CDictionary(name);
		for (CXMLParser::TArrtibutes::iterator it = attributes.begin(); it != attributes.end(); ++it)
			newDict->setAttributeForKey(it->first, it->second);

		mDictStack.push_back(newDict);
	}
}

void CXMLDictionaryParser::onEndTag(CXMLParser*, CString name)
{
	if (!mIsPlist || (mIsPlist && (name == cDict)))
	{
		CDictionary* dict = mDictStack.back();
		mDictStack.pop_back();

		if (mDictStack.empty())
		{
			mDictStack.push_back(dict);
		}
		else
		{
			mDictStack.back()->setValueForKey(dict->rootKey(), *dict);
			delete dict;
		}
	}
}

void CXMLDictionaryParser::onData(CXMLParser* parser, CString data)
{
	if (mIsPlist)
	{
		if (mLastTag == "key")
		{
			mKey = data;
		}
		else if (mLastTag == "string" || mLastTag == "real" || mLastTag == "integer")
		{
			mDictStack.back()->setValueForKey(mKey, data);
		}
	}
	else
	{
		mDictStack.back()->setRootValue(data);
	}
}

void CXMLDictionaryParser::onError(CXMLParser* parser, CString error)
{

}

	} // namespace le
} // namespace sokira
