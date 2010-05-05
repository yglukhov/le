/*
 *  CXMLDictionaryParser.cpp
 *  le
 *
 *  Created by Yuriy Glukhov on 5/5/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <le/core/template/function/slTCBind.h>
#include <le/core/slCDictionary.h>
#include "slCXMLDictionaryParser.hp"

namespace sokira
{
	namespace le
	{

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
	return CDictionary(*mDictStack.front());
}

void CXMLDictionaryParser::onStartTag(CXMLParser*, CString name, CXMLParser::TArrtibutes attributes)
{
	CDictionary* newDict = new CDictionary(name);
	for (CXMLParser::TArrtibutes::iterator it = attributes.begin(); it != attributes.end(); ++it)
		newDict->attributeForKey(it->first, it->second);

	mDictStack.push_back(newDict);
}

void CXMLDictionaryParser::onEndTag(CXMLParser*, CString tagName)
{
	CDictionary* dict = mDictStack.back();
	mDictStack.pop_back();

	if (mDictStack.empty())
	{
		mDictStack.push_back(dict);
	}
	else
	{
		mDictStack.back()->valueForKey(dict->rootKey(), *dict);
		delete dict;
	}
}

void CXMLDictionaryParser::onData(CXMLParser* parser, CString data)
{
	mDictStack.back()->setRootValue(data);
}

void CXMLDictionaryParser::onError(CXMLParser* parser, CString error)
{

}

	} // namespace le
} // namespace sokira
