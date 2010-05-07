#include <iostream>
#include <fstream>

#include <le/core/slCDictionary.h>
#include <le/core/io/slCDataStream.h>
#include <le/core/xml/slCXMLDocument.h>
#include <le/core/xml/slCXMLNode.h>
#include <le/core/template/function/slTCBind.h>
#include "slCXMLTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CXMLTestSuite);

static void onStartTag(CXMLParser*, CString tagName, CXMLParser::TArrtibutes attrs, CString* result)
{
	*result += CString::createWithFormat("<'%s'", tagName.cString());
	for (CXMLParser::TArrtibutes::const_iterator it = attrs.begin(); it != attrs.end(); ++it)
	{
		*result += CString::createWithFormat(" '%s'='%s'", it->first.cString(), it->second.cString());
	}
	*result += ">\n";
}

static void onEndTag(CXMLParser*, CString tagName, CString* result)
{
	*result += CString::createWithFormat("</%s>\n", tagName.cString());
}

static void onData(CXMLParser* parser, CString data, CString* result)
{
	*result += CString::createWithFormat("DATA[%s]\n", data.cString());
}

static void onError(CXMLParser* parser, CString error, CString* result)
{
	*result += CString::createWithFormat("ERROR[%s] LINE: %d COLUMN: %d\n", error.cString(), parser->line(), parser->column());
}

void CXMLTestSuite::testXMLParser()
{
	CString string = LESTR(
		"<tag1 attr=\"sdfg ljkh\" attr2=\"jhg\">\n"
		"	<subtag1></subtag1>"
		"</tag1><tag2 ghj=\"jhg\"/>\n");

	CInputDataStream stream(string.cString(), string.length());

	CString expectedResult = LESTR(
		"<'tag1' 'attr'='sdfg ljkh' 'attr2'='jhg'>\n"
			"<'subtag1'>\n"
			"</subtag1>\n"
		"</tag1>\n"
		"<'tag2' 'ghj'='jhg'>\n"
		"</tag2>\n");

	CXMLParser parser;
	parser.setTrimsWhitespace();

	CString actualResult;

	CXMLParser::TOnStartTag onStartTagHandler = bind(onStartTag, bindTo(0), bindTo(1), bindTo(2), &actualResult);
	parser.setOnStartTag(onStartTagHandler);
	CXMLParser::TOnEndTag onEndTagHandler = bind(onEndTag, bindTo(0), bindTo(1), &actualResult);
	parser.setOnEndTag(onEndTagHandler);
	CXMLParser::TOnError onErrorHandler = bind(onError, bindTo(0), bindTo(1), &actualResult);
	parser.setOnError(onErrorHandler);
	CXMLParser::TOnData onDataHandler = bind(onData, bindTo(0), bindTo(1), &actualResult);
	parser.setOnData(onDataHandler);

	parser.parseStream(stream);

	if (expectedResult != actualResult)
	{
		std::cout << "Expected result:\n" << expectedResult << "\n\nActual result:\n" << actualResult << std::endl;
		LE_ASSERT(expectedResult == actualResult);
	}
}

void CXMLTestSuite::testXMLDocument()
{
	CString string = LESTR(
		"<someTag someAttr=\"hello\" someOtherAttr=\"hi\">"
		"	<someOtherTag>yo!</someOthertag>\n"
		"	<someOtherEmptyTag emptyAttr1 attr=\"asdf\" emptyAttr2/>\n"
		"</someTag>");

	CInputDataStream inputStream(string.cString(), string.length());
	CXMLDocument document(inputStream);

	CXMLNode* rootNode = document.rootNode();
	LE_ASSERT(rootNode->name() == "someTag");
	LE_ASSERT(rootNode->attribute("someAttr") == "hello");
	LE_ASSERT(rootNode->attribute("someOtherAttr") == "hi");

	CXMLNode* childNode = rootNode->firstChildWithName("someOtherTag");
	LE_ASSERT(childNode->name() == "someOtherTag");
	LE_ASSERT(childNode->parent() == rootNode);

	childNode = rootNode->firstChildWithName("invalidTag");
	LE_ASSERT(childNode == NULL);

	childNode = rootNode->firstChildWithName("someOtherEmptyTag");
	LE_ASSERT(childNode->name() == "someOtherEmptyTag");
	LE_ASSERT(childNode->attribute("attr") == "asdf");
	LE_ASSERT(childNode->attribute("emptyAttr1") == "");
	LE_ASSERT(childNode->attribute("emptyAttr2") == "");
}

void CXMLTestSuite::testDictionaries()
{
	CDictionary dict("test");
	dict.setValueForKey("someTestKey", CString("1234"));
	dict.setValueForKey("someOtherTestKey", CString("4321"));
	dict.setValueForKey("someNumber", CString("123"));

	CDataStream dataStream;
	dict.dump(dataStream);
	CInputDataStream inputStream(dataStream.c_data(), dataStream.size());
	CDictionary newDict = CDictionary::createFromStream(inputStream);

	LE_ASSERT(newDict.valueAsStringForKey("someTestKey") == "1234");
	LE_ASSERT(newDict.valueAsStringForKey("someOtherTestKey") == "4321");
	LE_ASSERT(newDict.valueAsUInt8ForKey("someNumber") == 123);
}

void CXMLTestSuite::testPlistParsing()
{
	CString string = LESTR(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"
		"<plist version=\"1.0\">"
		"<dict>"
		"	<key>CFBundleDevelopmentRegion</key>"
		"	<string>English</string>"
		"	<key>CFBundleExecutable</key>"
		"	<string>yo</string>"
		"	<key>CFBundleIconFile</key>"
		"	<string></string>"
		"	<key>CFBundleIdentifier</key>"
		"	<string>org.7lifes.id</string>"
		"	<key>CFBundleInfoDictionaryVersion</key>"
		"	<string>6.0</string>"
		"	<key>CFBundleName</key>"
		"	<string>yo</string>"
		"	<key>CFBundlePackageType</key>"
		"	<string>APPL</string>"
		"	<key>CFBundleVersion</key>"
		"	<string>1.0</string>"
		"	<key>NSPrincipalClass</key>"
		"	<string>NSApplication</string>"
		"	<key>testBoolTrue</key>"
		"	<true/>"
		"	<key>testBoolFalse</key>"
		"	<false/>"
		"	<key>someDict</key>"
		"	<dict>"
		"		<key>someKey</key>"
		"		<string>someValue</string>"
		"	</dict>"
		"</dict>"
		"</plist>");

	CInputDataStream inputStream(string.cString(), string.length());

	CDictionary newDict = CDictionary::createFromStream(inputStream);
	CString expectedResult = LESTR(
		"<dict>"
			"<CFBundleDevelopmentRegion type=\"CString\">English</CFBundleDevelopmentRegion>"
			"<CFBundleExecutable type=\"CString\">yo</CFBundleExecutable>"
			"<CFBundleIdentifier type=\"CString\">org.7lifes.id</CFBundleIdentifier>"
			"<CFBundleInfoDictionaryVersion type=\"CString\">6.0</CFBundleInfoDictionaryVersion>"
			"<CFBundleName type=\"CString\">yo</CFBundleName>"
			"<CFBundlePackageType type=\"CString\">APPL</CFBundlePackageType>"
			"<CFBundleVersion type=\"CString\">1.0</CFBundleVersion>"
			"<NSPrincipalClass type=\"CString\">NSApplication</NSPrincipalClass>"
			"<someDict type=\"CDictionary\">"
				"<someKey type=\"CString\">someValue</someKey>"
			"</someDict>"
			"<testBoolFalse type=\"CNumber\">0</testBoolFalse>"
			"<testBoolTrue type=\"CNumber\">1</testBoolTrue>"
		"</dict>");

	CDataStream outputStream;
	newDict.dump(outputStream);
	char* actualRes = new char[outputStream.size() + 1];
	memcpy(actualRes, outputStream.c_data(), outputStream.size());
	actualRes[outputStream.size()] = 0;

	CString actualResult = CString::__CStringNoCopyDeallocWithDelete(actualRes);

	if (expectedResult != actualResult)
	{
		std::cout << "Expected result:\n" << expectedResult << "\n\nActual result:\n" << actualResult << std::endl;
		LE_ASSERT(expectedResult == actualResult);
	}
}

	} // namespace le
} // namespace sokira
