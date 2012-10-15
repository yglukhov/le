#include <iostream>

#include <le/core/slCString.h>
#include <le/core/slCNumber.h>
#include <le/core/io/slCDataStream.h>
#include <le/core/script/slCLexer.h>
#include <le/core/template/function/slTCBind.h>
#include <le/core/debug/slCLogControl.h>
#include <le/core/script/slCSokript.h>
#include <le/core/auxiliary/slCStopWatch.h>

#include "slCScriptTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScriptTestSuite);

static void addMatchersToTokenizer(CLexer& tokenizer)
{
	tokenizer.addMatcher(new CCharacterSetTokenMatcher("0123456789"), "LITERAL_INT");
	tokenizer.addMatcher(new CConstStringTokenMatcher(";"), ";");
	tokenizer.addMatcher(new CConstStringTokenMatcher("="), "=");
	tokenizer.addMatcher(new CConstStringTokenMatcher("+="), "+=");
	tokenizer.addMatcher(new CConstStringTokenMatcher("+"), "+");
	tokenizer.addMatcher(new CConstStringTokenMatcher("-"), "-");
	tokenizer.addMatcher(new CConstStringTokenMatcher("/"), "/");
	tokenizer.addMatcher(new CConstStringTokenMatcher("*"), "*");
	tokenizer.addMatcher(new CConstStringTokenMatcher("true"), "LITERAL_TRUE");
	tokenizer.addMatcher(new CConstStringTokenMatcher("false"), "LITERAL_FALSE");
	tokenizer.addMatcher(new CCharacterSetTokenMatcher(" \n\t\r"), "WHITESPACE");
	tokenizer.addMatcher(new CIdentifierTokenMatcher(), "identifier");
	tokenizer.addMatcher(new CStringLiteralTokenMatcher(), "LITERAL_STRING");
	tokenizer.addMatcher(new CConstStringTokenMatcher("function"), "FUNCTION");
}

void CScriptTestSuite::testTokenizer()
{
	CLexer tokenizer;
	CString string = LESTR("sdfg; 1234+1234  ; function   a+=b + 'string literal' z");
	CInputDataStream stream(string.cString(), string.length());
	tokenizer.setInputStream(&stream);
	addMatchersToTokenizer(tokenizer);

	std::vector<CString> tokenIds;
	tokenIds.push_back("identifier");
	tokenIds.push_back(";");
	tokenIds.push_back("LITERAL_INT");
	tokenIds.push_back("+");
	tokenIds.push_back("LITERAL_INT");
	tokenIds.push_back(";");
	tokenIds.push_back("FUNCTION");
	tokenIds.push_back("identifier");
	tokenIds.push_back("+=");
	tokenIds.push_back("identifier");
	tokenIds.push_back("+");
	tokenIds.push_back("LITERAL_STRING");
	tokenIds.push_back("identifier");

	tokenizer.addIgnoredIdentifier("WHITESPACE");

	int i = 0;
	while (!tokenizer.eof())
	{
		CToken token = tokenizer.nextToken();
		if (token.mMatcher)
		{
			LE_ASSERT(token.identifier() == tokenIds[i]);
			++i;
		}
	}

	LE_ASSERT(i == tokenIds.size());
}

CObject::Ptr printObject(CObject::Ptr obj)
{
	LE_ASSERT(obj);
	std::cout << "Print object: " << obj->description() << std::endl;
	return NULL;
}

void CScriptTestSuite::testParser()
{
//	CString string = LESTR("function a(obj, times) { for (i = 0; i < times; i = i + 1) { print('obj ' + i + ': ' + obj); } } a(2, 5);");
	CString string = LESTR("i = 5;");
	CSokript sokript;
	sokript.addExternalFunction("print", printObject);
//	sokript.addExternalObject("a", new CNumber(2));
//	sokript.addExternalObject("b", new CNumber(3));

	CStopWatch watch;
	watch.start();
	CObject::Ptr result = sokript.runScript(string);
	watch.pause();
	LE_ASSERT(result);
	std::cout << "PARSE RESULT: \n";
	std::cout << result->description();
	std::cout << "\ntime: " << watch.milliseconds() << std::endl;
}

	} // namespace le
} // namespace sokira
