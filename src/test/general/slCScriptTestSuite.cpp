#include <iostream>

#include <le/core/slCString.h>
#include <le/core/slCNumber.h>
#include <le/core/slCDictionary.h>
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

//LE_IMPLEMENT_RUNTIME_CLASS(CScriptTestSuite);

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
	CInputDataStream stream(string.UTF8String(), string.length());
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

		struct TestObject : public CDictionary
		{
			LE_RTTI_BEGIN
				LE_RTTI_SELF(TestObject)
				LE_RTTI_SINGLE_PUBLIC_PARENT
				LE_RTTI_SELECTOR(setValue)
				LE_RTTI_SELECTOR_WITH_NAME(value, getValue)
			LE_RTTI_END
			
			void setValue(CObject::Ptr newValue)
			{
				setValueForKey("value", newValue);
			}

			CObject::Ptr value() const
			{
				return valueAsObjectForKey("value");
			}
		};
		
		LE_IMPLEMENT_RUNTIME_CLASS(TestObject);

void CScriptTestSuite::testParser()
{
//	CString string = LESTR("function a(obj, times) { for (i = 0; i < times; i = i + 1) { print('obj ' + i + ': ' + obj); } } a(2, 5);");
	CString string = LESTR("a.value = 10; a.setValue(a.getValue() + 5); print(a.value); b = dict(); b.a = 123; b.a += 2; print(b); return b;");
	CSokript sokript;


	sokript.addExternalFunction("print", printObject);
	sokript.addExternalObject("a", new TestObject());

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
