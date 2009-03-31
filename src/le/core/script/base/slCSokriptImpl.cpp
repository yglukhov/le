#include <fstream>

#include <le/core/io/slCDataStream.h>
#include "slCSokriptImpl.hp"
#include "slCSokriptInstruction.hp"

#include "slCSokriptFlexLexer.hp"
#include "slCSokriptVM.hp"

#if 0

print(2);
			// INT 
			// CALL_SOKRIPT_FUNCTION print
			// PUSH 2
			// CALL 0

#endif



namespace sokira
{
	namespace le
	{

CSokriptImpl::CSokriptImpl() :
	mLexer(NULL),
	mParser(NULL),
	mInstruction(NULL)
{

}

CSokriptImpl::~CSokriptImpl()
{
	delete mLexer;
	delete mParser;
}

void CSokriptImpl::runFromStream(std::istream& stream)
{
	mLexer = new CSokriptFlexLexer(&stream);
	mParser = new CSokriptBisonParser(this);
//	mParser->set_debug_level(1);
	mParser->parse();

	// the parser should call our setInstruction and thus fill the mInstruction
	LE_ASSERT(mInstruction);
//	std::cout << "Instructions before processing:" << std::endl;
//	mInstruction->showAll();

	mInstruction = CSokriptInstruction::postProcessBytecode(mInstruction);

	std::cout << "Instructions after processing:" << std::endl;
	mInstruction->showAll();

	Bool optimize = true;

	if (optimize)
	{
		CSokriptInstruction::optimizeByteCode(mInstruction);
	}

//	std::ostream
	std::ofstream f("/tmp/sokript.vm.test");
	CDataStream data;
	CSokriptInstruction::dumpBytecodeToStream(mInstruction, data);
	f.write(data.c_data(), data.size());
	f.close();

	CSokriptVM vm;
	
	vm.performByteCode(CData(data.c_data(), data.size()));
	delete mInstruction;
	mInstruction = NULL;
}

int CSokriptImpl::lex(void* yylval, void* yylloc)
{
	return static_cast<CSokriptFlexLexer*> (mLexer)->lex(
		static_cast<CSokriptBisonParser::semantic_type*>(yylval),
		static_cast<CSokriptBisonParser::location_type*>(yylloc),
		this);
}

void CSokriptImpl::parse_error(const void* l, const void* s)
{
	const CSokriptBisonParser::location_type* location = static_cast<const CSokriptBisonParser::location_type*>(l);
	const std::string* str = static_cast<const std::string*>(s);

	std::cerr << *location << ": PARSE ERROR: " << *str << std::endl;
}

void CSokriptImpl::lex_error(const void* s, const void* l)
{
	const char* str = static_cast<const char*> (s);
	const CSokriptBisonParser::location_type* location = static_cast<const CSokriptBisonParser::location_type*>(l);
	std::cerr << *location << ": LEXER ERROR: " << str << std::endl;
}

void CSokriptImpl::setInstruction(CSokriptInstruction* instruction)
{
	mInstruction = instruction;
}

// Arithmetic actions
CObject* CSokriptImpl::addObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		*leftNumber += *rightNumber;
		delete rightNumber;
		return leftNumber;
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		*leftString += *rightString;
		delete rightString;
		return leftString;
	}

	delete left;
	delete right;
	return new CNumber(1);
}

//CObject* CSokriptImpl::substractObjects(CObject* left, CObject* right)
//{
//	// If both values are numbers, resulting value is number
//	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
//	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
//	if (leftNumber && rightNumber)
//	{
//		*leftNumber -= *rightNumber;
//		delete rightNumber;
//		return leftNumber;
//	}
//
//	delete left;
//	delete right;
//	return new CNumber(2);
//}
//
//CObject* CSokriptImpl::multiplyObjects(CObject* left, CObject* right)
//{
//	// If both values are numbers, resulting value is number
//	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
//	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
//	if (leftNumber && rightNumber)
//	{
//		*leftNumber *= *rightNumber;
//		delete rightNumber;
//		return leftNumber;
//	}
//
//	delete left;
//	delete right;
//	return new CNumber(3);
//}
//
//CObject* CSokriptImpl::divideObjects(CObject* left, CObject* right)
//{
//	// If both values are numbers, resulting value is number
//	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
//	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
//	if (leftNumber && rightNumber)
//	{
//		*leftNumber /= *rightNumber;
//		delete rightNumber;
//		return leftNumber;
//	}
//
//	delete left;
//	delete right;
//	return new CNumber(4);
//}
//
//CObject* CSokriptImpl::negateObject(CObject* obj)
//{
//	// If obj is a number, negate it
//	CNumber* number = dynamic_cast<CNumber*>(obj);
//	if (number)
//	{
//		*number = - number->valueAsFloat32();
//		return number;
//	}
//	
//	delete obj;
//	return new CNumber(5);
//}

//CObject* CSokriptImpl::assignableObjectByName(char* name)
//{
//	CString nameStr(CString::__CStringNoCopyDeallocWithFree(name));
//	std::map<CString, CObject*>::iterator it = mVars.find(nameStr);
//	if (it != mVars.end())
//	{
//		return it->second;
//	}
//
////	mVars.insert(std::make_pair(
//
////	free(name);
//	return NULL;
//}

CSokriptInstruction* CSokriptImpl::pushConstantInstruction(CObject* theConstant)
{
	CString* str = dynamic_cast<CString*> (theConstant);
	if (str) return new CSokriptInstruction(eInstructionPushStr, str);

	CNumber* number = dynamic_cast<CNumber*> (theConstant);
	if (number) return new CSokriptInstruction(eInstructionPushFloat, number);

	LE_ASSERT(false);

	return NULL;
}

//CObject* CSokriptImpl::assign(CObject* assignableObject, CObject* expression)
//{
//	std::cout << "Assignable object is:";
//	if (assignableObject) std::cout << assignableObject->description();
//	else std::cout << "NULL";
//	std::cout << std::endl;
//	return NULL;
//}

	} // namespace le
} // namespace sokira
