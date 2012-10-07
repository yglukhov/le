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
	CString string = LESTR("sdfg; 1234+1234  ; function   a+=b + 'string literal'");
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

	tokenizer.addIgnoredIdentifier("WHITESPACE");

	int i = 0;
	while (!tokenizer.eof())
	{
		CToken token = tokenizer.nextToken();
		if (token.mMatcher)
		{
			LE_ASSERT(token.identifier() == tokenIds[i]);
		}
		++i;
	}
	
	LE_ASSERT(i == tokenIds.size() + 1);
}

void CScriptTestSuite::testParser()
{
//	CLexer tokenizer;
	CString string = LESTR("function a(x, y) { return x + y; }; print(a(3, 4));");
	CInputDataStream stream(string.cString(), string.length());
//	tokenizer.setInputStream(&stream);
//	addMatchersToTokenizer(tokenizer);

//	tokenizer.retain();

//	CParserGrammar grammar;
	CStopWatch watch;
	watch.start();
	CSokriptParser parser;
	CObject::Ptr result = parser.parse(stream);
	watch.pause();
	std::cout << "PARSE RESULT: \n";
	std::cout << result->description();
	std::cout << "time: " << watch.milliseconds() << std::endl;

	watch.reset();
	watch.start();
	CSokript sokript;
	CDataStream dataStream;
	CInputDataStream bisonStream(string.cString(), string.length());
	sokript.compileFromStream(bisonStream, dataStream);
	watch.pause();
	std::cout << "time: " << watch.milliseconds() << std::endl;

	CData data(dataStream.c_data(), dataStream.size());
//	std::cout << "DATA length: " << data.length() << std::endl;
	sokript.runBytecode(data);
//	CSokriptParser parser;
//	parser.setLexer(&tokenizer);


//	CParser::TRuleHandler handler = bind(matchFunc, bindTo(0));

//	CLogControl::instance()->attachToStandardOutput(0);

//	std::cout << "PARSED: " << parser.parse()->description() << std::endl;
}

	} // namespace le
} // namespace sokira
