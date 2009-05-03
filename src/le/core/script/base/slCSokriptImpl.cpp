#include <fstream>

#include <le/core/io/slCDataStream.h>
#include "slCSokriptImpl.hp"
#include "slCSokriptInstruction.hp"

#include "slCSokriptFlexLexer.hp"
#include "slCSokriptVM.hp"


namespace sokira
{
	namespace le
	{

typedef ::_sokira_le::CSokriptBisonParser CSokriptBisonParser;


CSokriptImpl::CSokriptImpl() :
	mLexer(NULL),
	mInstruction(NULL)
{

}

CSokriptImpl::~CSokriptImpl()
{
	delete mLexer;
}

void CSokriptImpl::addFunction(const CString& name, CObject* (*function)(CObject*))
{

}

void CSokriptImpl::runBytecode(const CData& bytecode)
{
	CSokriptVM vm;
	vm.performByteCode(bytecode);
}

void CSokriptImpl::compileFromStream(std::istream& input, std::ostream& output)
{
	mLexer = new CSokriptFlexLexer(&input);
	CSokriptBisonParser parser(this);
//	parser.set_debug_level(1);
	parser.parse(); // Parser should call our setInstruction upon successful parsing.
					// setInstruction will fill our mInstruction.

	delete mLexer;
	mLexer = NULL;

	LE_ASSERT(mInstruction);

	Bool optimize = true;

	if (optimize)
	{
		mInstruction = CSokriptInstruction::optimizeByteCode(mInstruction);
	}

	CSokriptInstruction::dumpBytecodeToStream(mInstruction, output);
	delete mInstruction;
	mInstruction = NULL;
}

int CSokriptImpl::lex(void* yylval, void* yylloc)
{
	return mLexer->lex(
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

void CSokriptImpl::lex_error(const char* str, const void* l)
{
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

CSokriptInstruction* CSokriptImpl::pushConstantInstruction(CObject* theConstant)
{
	CString* str = dynamic_cast<CString*> (theConstant);
	if (str) return new CSokriptInstruction(eInstructionPushStr, str);

	CNumber* number = dynamic_cast<CNumber*> (theConstant);
	if (number) return new CSokriptInstruction(eInstructionPushFloat, number);

	LE_ASSERT(false);

	return NULL;
}

	} // namespace le
} // namespace sokira
