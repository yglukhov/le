#include <iostream>

#include <le/core/slCString.h>
#include <le/core/io/slCDataStream.h>
#include <le/core/script/slCTokenizer.h>
#include "slCScriptTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScriptTestSuite);

void CScriptTestSuite::testTokenizer()
{
	CTokenizer tokenizer;
	CString string = LESTR("sdfg; 1234+1234  ;    a+=b");
	CInputDataStream stream(string.cString(), string.length());
	tokenizer.setInputStream(&stream);
	const char* map[] = {
		"eTokenTypeUnknown",
		"eTokenTypeSpace",
		"eTokenTypePunctuation",
		"eTokenTypeIdentifier",
		"eTokenTypeNumericLiteral",
		"eTokenTypeStringLiteral" };
	while (!tokenizer.eof())
	{
		CToken token = tokenizer.nextToken();
//		std::cout << "token: \"" << token.token << "\" (" << map[token.type] << ")" << std::endl;
	}
}

	} // namespace le
} // namespace sokira
