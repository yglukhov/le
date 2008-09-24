#include <iostream>
#include <strstream>
#include <fstream>

#include <le/core/slCDictionary.h>
#include <le/core/xml/slCXMLParser.h>
#include <le/core/template/function/slTCBind.h>
#include "slCXMLTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CXMLTestSuite);

void CXMLTestSuite::onStartTag(CXMLParser*, CString tagName, CXMLParser::TArrtibutes attrs)
{
	mActualResult += CString::createWithFormat("<%s", tagName.cString());
	for (CXMLParser::TArrtibutes::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
	{
		mActualResult += CString::createWithFormat(" %s='%s'", it->first.cString(), it->second.cString());
	}
	mActualResult += ">\n";
}

void CXMLTestSuite::onStartTagDump(CXMLParser*, CString tagName, CXMLParser::TArrtibutes attrs)
{
	std::cout << '<' << tagName;
	for (CXMLParser::TArrtibutes::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
	{
		std::cout << ' ' << it->first << "='" << it->second << '\'';
	}
	std::cout << '>' << std::endl;
}

void CXMLTestSuite::onEndTag(CXMLParser*, CString tagName)
{
	mActualResult += CString::createWithFormat("</%s>\n", tagName.cString());
}

void CXMLTestSuite::onEndTagDump(CXMLParser*, CString tagName)
{
	std::cout << "</" << tagName << '>' << std::endl;
}

void CXMLTestSuite::onData(CXMLParser* parser, CString data)
{
	mActualResult += CString::createWithFormat("DATA[%s]\n", data.cString());
}

void CXMLTestSuite::onDataDump(CXMLParser* parser, CString data)
{
	std::cout << "DATA[" << data << ']' << std::endl;
}

void CXMLTestSuite::onError(CXMLParser* parser, CString error)
{
	mActualResult += CString::createWithFormat("ERROR[%s] LINE: %d COLUMN: %d\n", error.cString(), parser->line(), parser->column());
}

void CXMLTestSuite::onErrorDump(CXMLParser* parser, CString error)
{
	std::cout << "ERROR[" << error << "] LINE: " << parser->line() << " COLUMN: " << parser->column() << std::endl;
}

void CXMLTestSuite::testXMLParser()
{
	std::istrstream stream(
		"<  \t  tag1  \n"
		"   attr1=\"val1\" attr2=val2>\n"
		"	<subtag1 at=\"va\" qwer/>\n"
		"	<   subtag2  >some data<   /  subtag2  >\n"
		"</ tag1>\n"
		"<tag2/>");

	CString expectedResult = LESTR(
		"<tag1 attr1='val1' attr2='val2'>\n"
			"<subtag1 at='va' qwer=''>\n"
			"</subtag1>\n"
			"<subtag2>\n"
			"DATA[some data]\n"
			"</subtag2>\n"
		"</tag1>\n"
		"<tag2>\n"
		"</tag2>\n");

	CXMLParser parser;
	parser.setTrimsWhitespace();
	CXMLParser::TOnStartTag onStart = bind(&CXMLTestSuite::onStartTag, this, bindTo(0), bindTo(1), bindTo(2));
	parser.setOnStartTag(onStart);
	CXMLParser::TOnEndTag onEnd = bind(&CXMLTestSuite::onEndTag, this, bindTo(0), bindTo(1));
	parser.setOnEndTag(onEnd);
	CXMLParser::TOnEndTag onError = bind(&CXMLTestSuite::onError, this, bindTo(0), bindTo(1));
	parser.setOnError(onError);
	CXMLParser::TOnData onData = bind(&CXMLTestSuite::onData, this, bindTo(0), bindTo(1));
	parser.setOnData(onData);

	parser.parseStream(stream);

	if (expectedResult != mActualResult)
	{
		std::cout << "Expected result:\n" << expectedResult << "\n\nActual result:\n" << mActualResult << std::endl;
		LE_ASSERT(expectedResult == mActualResult);
	}
}


void CXMLTestSuite::testXMLParser2()
{
	mActualResult.clear();
	CXMLParser parser;
	parser.setTrimsWhitespace();
	CXMLParser::TOnStartTag onStart = bind(&CXMLTestSuite::onStartTagDump, this, bindTo(0), bindTo(1), bindTo(2));
	parser.setOnStartTag(onStart);
	CXMLParser::TOnEndTag onEnd = bind(&CXMLTestSuite::onEndTagDump, this, bindTo(0), bindTo(1));
	parser.setOnEndTag(onEnd);
	CXMLParser::TOnEndTag onError = bind(&CXMLTestSuite::onErrorDump, this, bindTo(0), bindTo(1));
	parser.setOnError(onError);
	CXMLParser::TOnData onData = bind(&CXMLTestSuite::onDataDump, this, bindTo(0), bindTo(1));
	parser.setOnData(onData);

	std::ifstream stream("g:\\ui.xml");
	parser.parseStream(stream);

//	char buf[1024];
//	stream.read(buf, 1024);
//	buf[1023] = 0;
//	std::cout << buf;
}

	} // namespace le
} // namespace sokira
