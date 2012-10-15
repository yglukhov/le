#include <iterator>
#include <le/core/io/slCDataStream.h>

#include "slCSokript.h"
#include "slCParser.h"
#include "base/slCSokriptInstruction.hp"
#include "base/slCSokriptVM.hp"
#include <le/core/slCNumber.h>
#include <le/core/slCAny.h>


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CSokript);

static void dumpArgs(std::vector<CObject::Ptr>& args)
{
	for (std::vector<CObject::Ptr>::iterator it = args.begin(); it != args.end(); ++it)
	{
		std::cout << (*it)->description() << ", ";
	}
	std::cout << std::endl;
}

static CObject::Ptr createNumberLiteral(std::vector<CObject::Ptr>& args)
{
	LE_ASSERT(args.size() == 1);
	CString* val = (CString*)args[0].get();
	return new CNumber(*val);
}

static CObject::Ptr createConstantExpression(std::vector<CObject::Ptr>& args)
{
//	std::cout << "createConstantExpression: ";
//	dumpArgs(args);
	LE_ASSERT(args.size() == 1);
	CClass objClass = args[0]->objectClass();
	if (objClass == CString::staticClass())
	{
		return new CSokriptInstruction(eInstructionPushStr, args[0]);
	}
	else if (objClass == CNumber::staticClass())
	{
		return new CSokriptInstruction(eInstructionPushFloat, args[0]);
	}
	LE_ASSERT(false);
	return NULL;
}

static CObject::Ptr createStatementFromExpression(std::vector<CObject::Ptr>& args)
{
//	std::cout << "createStatement: ";
//	dumpArgs(args);
	LE_ASSERT(args.size() == 2);
	CSokriptInstruction::Ptr instruction = args[0].upcast<CSokriptInstruction>();
	if (instruction)
	{
		instruction->addInstruction(new CSokriptInstruction(eInstructionDiscard));
	}
	return instruction;
}

static CObject::Ptr createStatementList(std::vector<CObject::Ptr>& args)
{
//	std::cout << "createStatementList: ";
//	dumpArgs(args);
	LE_ASSERT(args.size() <= 2);
	CSokriptInstruction::Ptr i1;
	CSokriptInstruction::Ptr i2;
	if (args.size() >= 1 && args[0])
	{
		i1 = args[0].upcast<CSokriptInstruction>();
	}

	if (args.size() >= 2 && args[1])
	{
		i2 = args[1].upcast<CSokriptInstruction>();
	}

	if (i1)
	{
		if (i2)
		{
			i1->addInstruction(i2);
		}
		return i1;
	}
	else if (i2)
	{
		return i2;
	}

	return NULL;
}

static CObject::Ptr createProgram(std::vector<CObject::Ptr>& args)
{
//	std::cout << "createProgram: ";
//	dumpArgs(args);
	LE_ASSERT(args.size() == 1);
	CSokriptInstruction::Ptr i = args[0].upcast<CSokriptInstruction>();
	if (i)
		i->addReturn0Instruction();
	else
		i = CSokriptInstruction::return0Instruction();

	return CSokriptInstruction::postProcessBytecode(i, NULL);
}

static CObject::Ptr createBinaryArithmeticExpression(std::vector<CObject::Ptr>& args)
{
//	std::cout << "createBinaryArithmeticExpression: ";
//	dumpArgs(args);

	LE_ASSERT(args.size() == 3);

	CSokriptInstruction::Ptr first = args[0].upcast<CSokriptInstruction>();
	CSokriptInstruction::Ptr second = args[2].upcast<CSokriptInstruction>();
	CString* operation = dynamic_cast<CString*>(args[1].get());
	LE_ASSERT(first);
	LE_ASSERT(second);
	LE_ASSERT(operation);

	EInstruction instruction = eInstructionNOP;
	if (*operation == "+")
		instruction = eInstructionAdd;
	else if (*operation == "-")
		instruction = eInstructionSubstract;
	else if (*operation == "*")
		instruction = eInstructionMultiply;
	else if (*operation == "/")
		instruction = eInstructionDivide;
	else if (*operation == "<")
		instruction = eInstructionLessThan;
	else if (*operation == ">")
		instruction = eInstructionGreaterThan;
	else if (*operation == "<=")
		instruction = eInstructionLessEqual;
	else if (*operation == ">=")
		instruction = eInstructionGreaterEqual;
	else if (*operation == "==")
		instruction = eInstructionEqual;
	else if (*operation == "!=")
		instruction = eInstructionNotEqual;

	LE_ASSERT(instruction != eInstructionNOP);
	second->addInstruction(new CSokriptInstruction(instruction));
	first->addInstruction(second);
	return first;
}

static CObject::Ptr negateExpression(std::vector<CObject::Ptr>& args)
{
	LE_ASSERT(args.size() == 2);
	CSokriptInstruction::Ptr i = args[1].upcast<CSokriptInstruction>();
	LE_ASSERT(i);
	i->addInstruction(new CSokriptInstruction(eInstructionNegate));
	return i;
}

static CObject::Ptr createReturnStatement(std::vector<CObject::Ptr>& args)
{
	LE_ASSERT(args.size() == 3);
	CSokriptInstruction::Ptr i = args[1].upcast<CSokriptInstruction>();
	if (!i)
		i = new CSokriptInstruction(eInstructionPushFloat, new CNumber());

	i->addInstruction(new CSokriptInstruction(eInstructionReturn));
	return i;
}

static CObject::Ptr createIfThenElse(std::vector<CObject::Ptr>& args)
{
	CSokriptInstruction* expression = dynamic_cast<CSokriptInstruction*>(args[2].get());
	LE_ASSERT(expression);
	expression->retain();
	CSokriptInstruction* ifStatement = dynamic_cast<CSokriptInstruction*>(args[4].get());
	if (ifStatement) ifStatement->retain();

	CSokriptInstruction* elseStatement = NULL;
	if (args.size() == 7)
	{
		elseStatement = dynamic_cast<CSokriptInstruction*>(args[6].get());
		if (elseStatement) elseStatement->retain();
	}
	return CSokriptInstruction::createIfThenElse(expression, ifStatement, elseStatement);
}

static CObject::Ptr createLoop(std::vector<CObject::Ptr>& args)
{
	std::cout << "createLoop:\n";
	dumpArgs(args);
	CSokriptInstruction* expression = dynamic_cast<CSokriptInstruction*>(args[2].get());
	LE_ASSERT(expression);
	expression->retain();
	CSokriptInstruction* statement = dynamic_cast<CSokriptInstruction*>(args[4].get());
	if (statement) statement->retain();
	statement = CSokriptInstruction::createLoop(expression, statement);
	statement->retain();
	return statement;
}

static CObject::Ptr createForLoop(std::vector<CObject::Ptr>& args)
{
	CSokriptInstruction::Ptr afterLoop = args[6].upcast<CSokriptInstruction>();
	CSokriptInstruction::Ptr loopBody = args[8].upcast<CSokriptInstruction>();
	CSokriptInstruction::Ptr condition = args[4].upcast<CSokriptInstruction>();
	CSokriptInstruction::Ptr loopInit = args[2].upcast<CSokriptInstruction>();

	if (afterLoop)
	{
		afterLoop->addInstruction(new CSokriptInstruction(eInstructionDiscard));
		if (loopBody)
		{
			loopBody->addInstruction(afterLoop);
		}
		else
			loopBody = afterLoop;
	}

	CSokriptInstruction::Ptr loopInstruction = CSokriptInstruction::createLoop(condition, loopBody);
	if (loopInit)
	{
		CSokriptInstruction* discard = new CSokriptInstruction(eInstructionDiscard);
		discard->addInstruction(loopInstruction);
		loopInit->addInstruction(discard);
	}
	else
	{
		loopInit = loopInstruction;
		loopInit.retain();
	}

	return loopInit;
}

static CObject::Ptr createAssignmentExpression(std::vector<CObject::Ptr>& args)
{
	CSokriptInstruction::Ptr expression = args[2].upcast<CSokriptInstruction>();
	LE_ASSERT(expression);
	expression->addInstruction(new CSokriptInstruction(eInstructionAssign, args[0]));
	return expression;
}

static CObject::Ptr createExpressionFromIdentifier(std::vector<CObject::Ptr>& args)
{
	return new CSokriptInstruction(eInstructionPushVar, args[0]);
}

static CObject::Ptr createStringLiteral(std::vector<CObject::Ptr>& args)
{
	CString* literal = dynamic_cast<CString*>(args[0].get());
	CString* result = new CString(literal->subString(1, literal->length() - 2));
	std::cout << "STRING LITERAL: " << *result << std::endl;
	return result;
}

static CObject::Ptr concatStringLiteral(std::vector<CObject::Ptr>& args)
{
	CString* literal1 = dynamic_cast<CString*>(args[0].get());
	CString* literal2 = dynamic_cast<CString*>(args[1].get());
	LE_ASSERT(literal1);
	LE_ASSERT(literal2);
	return new CString(*literal1 + *literal2);
}

static CObject::Ptr createFunctionDefinition(std::vector<CObject::Ptr>& args)
{
	int definitionHasIdentifier = args.size() == 8;
	CSokriptInstruction::Ptr instruction = args[5 + definitionHasIdentifier].upcast<CSokriptInstruction>();
	std::list<CString>* funcArgs = &(dynamic_cast<CAny*>(args[2 + definitionHasIdentifier].get())->mutableValue<std::list<CString> >());

	if (instruction)
	{
		instruction->addReturn0Instruction();
	}
	else
		instruction = CSokriptInstruction::return0Instruction();

	instruction = CSokriptInstruction::postProcessBytecode(instruction, funcArgs);

	CSokriptInstruction::Ptr pushFunction = new CSokriptInstruction(eInstructionPushFunction);
	pushFunction->mUInt32Arg1 = instruction->length();
	pushFunction->mUInt16Arg2 = funcArgs->size();

	if (definitionHasIdentifier)
	{
		CObject::Ptr identifier = args[1];
		CSokriptInstruction* tmp = new CSokriptInstruction(eInstructionAssign, identifier);
		tmp->addInstruction(new CSokriptInstruction(eInstructionDiscard));
		instruction->addInstruction(tmp);
	}

	pushFunction->addInstruction(instruction);
	return pushFunction;
}

static CObject::Ptr createFunctionArgListDefinition(std::vector<CObject::Ptr>& args)
{
	CAny::Ptr list;
	CObject::Ptr identifier;
	if (args.size() > 1)
	{
		list = args[0].upcast<CAny>();
		identifier = args[2];
	}
	else
	{
		list = new CAny(std::list<CString>());

		if (args.size())
		{
			identifier = args[0];
		}
	}

	if (identifier)
	{
		CString* idStr = dynamic_cast<CString*>(identifier.get());
		LE_ASSERT(idStr);
		list->mutableValue<std::list<CString> >().push_back(CString(*idStr));
	}

	return list;
}

struct SFunctionCallArguments : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(SFunctionCallArguments)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END
	CSokriptInstruction::Ptr args;
	UInt16 argsCount;
};

LE_IMPLEMENT_RUNTIME_CLASS(SFunctionCallArguments);

static CObject::Ptr createFunctionCall(std::vector<CObject::Ptr>& args)
{
	SFunctionCallArguments::Ptr arguments = args[2].upcast<SFunctionCallArguments>();
	LE_ASSERT(arguments);

	CSokriptInstruction::Ptr call = new CSokriptInstruction(eInstructionCall);
	call->mUInt16Arg1 = arguments->argsCount;

	CSokriptInstruction::Ptr argsInstruction = arguments->args;

	if (argsInstruction)
	{
		argsInstruction->addInstruction(call);
	}
	else
		argsInstruction = call;

	CSokriptInstruction::Ptr funcExpression = args[0].upcast<CSokriptInstruction>();
	LE_ASSERT(funcExpression);
	funcExpression->addInstruction(argsInstruction);

	return funcExpression;
}

static CObject::Ptr createFunctionArgList(std::vector<CObject::Ptr>& args)
{
	SFunctionCallArguments::Ptr callArgs = NULL;
	if (args.size() <= 1)
	{
		callArgs = new SFunctionCallArguments;
		callArgs->argsCount = 0;
		if (args.size() == 1)
		{
			callArgs->args = args[0].upcast<CSokriptInstruction>();
			callArgs->argsCount = 1;
		}
	}
	else
	{
		callArgs = args[0].upcast<SFunctionCallArguments>();
		LE_ASSERT(callArgs);
		LE_ASSERT(callArgs->args);
		callArgs->args->addInstruction(args[2].upcast<CSokriptInstruction>());
		++callArgs->argsCount;
	}
	return callArgs;
}

static inline CParserGrammar::Ptr sokripGrammar()
{
	CParserGrammar* pGrammar = new CParserGrammar();
	CParserGrammar& grammar = *pGrammar;

	grammar["%ignore"]
		>> new CCharacterSetTokenMatcher(" \n\t\r");

	grammar["%right"]
		>> '=';

	grammar["%left"]
		>> "||"
		>> "&&"
		>> "==" << "!="
		>> "<" << "<=" << ">" << ">="
		>> '+' << '-'
		>> '*' << '/';

	grammar["%right"]
		>> '!';

	grammar["%left"]
		>> '(' << ')'
		>> '.';

	grammar["program"]
		>> "statementList" << createProgram;

	grammar["statementList"]
		>> "statementList" << "statement" << createStatementList
		>> "";

	grammar["statement"]
		>> "functionDefinition"
		>> "classDefinition"
		>> "expressionOrNothing" << ';' << createStatementFromExpression
		>> "return" << "expressionOrNothing" << ';' << createReturnStatement
		>> '{' << "statementList" << '}' << 1
		>> "selectionStatement"
		>> "loopStatement";

	grammar["selectionStatement"]
//		>> "if" << '(' << "expression" << ')' << "statement" << createIfThenElse
		>> "if" << '(' << "expression" << ')' << "statement" << "else" << "statement" << createIfThenElse;

	grammar["loopStatement"]
		>> "while" << '(' << "expression" << ')' << "statement" << createLoop
		>> "for" << '(' <<  "expressionOrNothing" << ';' << "expression" << ';' << "expressionOrNothing" << ')' << "statement" << createForLoop;

	grammar["expressionOrNothing"]
		>> "expression"
		>> "";

	grammar["expression"]
		>> "assignmentExpression"
		>> "arithmeticExpression"
		>> "comparisonExpression"
		>> "logicExpression"
		>> "identifier" << createExpressionFromIdentifier
		>> "constantExpression" << createConstantExpression
		>> "functionCall"
		>> "anonymousFunctionDefinition"
		>> "getProperty";

	grammar["getProperty"]
		>> "expression" << '.' << "identifier";

	grammar["arithmeticExpression"]
		>> "expression" << '+' << "expression" << createBinaryArithmeticExpression
		>> "expression" << '-' << "expression" << createBinaryArithmeticExpression
		>> "expression" << '*' << "expression" << createBinaryArithmeticExpression
		>> "expression" << '/' << "expression" << createBinaryArithmeticExpression
		>> '-' << "expression" << negateExpression
		>> '+' << "expression" << 1
		>> '(' << "expression" << ')' << 1;

	grammar["comparisonExpression"]
		>> "expression" << "<=" << "expression" << createBinaryArithmeticExpression
		>> "expression" << ">=" << "expression" << createBinaryArithmeticExpression
		>> "expression" << '<' << "expression" << createBinaryArithmeticExpression
		>> "expression" << '>' << "expression" << createBinaryArithmeticExpression
		>> "expression" << "==" << "expression" << createBinaryArithmeticExpression
		>> "expression" << "!=" << "expression" << createBinaryArithmeticExpression;

	grammar["logicExpression"]
		>> "expression" << "&&" << "expression"
		>> "expression" << "||" << "expression"
		>> '!' << "expression";

	grammar["assignmentExpression"]
		>> "identifier" << "=" << "expression" << createAssignmentExpression;

//	grammar["lvalueExpression"]
//		>> "identifier";

	grammar["functionCall"]
		>> "expression" << '(' << "functionArgList" << ')' << createFunctionCall;

	grammar["functionArgList"]
		>> "not_empty_function_arg_list"
		>> "" << createFunctionArgList;

	grammar["not_empty_function_arg_list"]
		>> "expression" << createFunctionArgList
		>> "not_empty_function_arg_list" << ',' << "expression" << createFunctionArgList;

	grammar["functionDefinition"]
		>> "function" << "identifier" << '(' << "functionArgListDefinition" << ')' << '{' << "statementList" << '}' << createFunctionDefinition;

	grammar["anonymousFunctionDefinition"]
		>> "function" << '(' << "functionArgListDefinition" << ')' << '{' << "statementList" << '}' << createFunctionDefinition;

	grammar["functionArgListDefinition"]
		>> "nonEmptyFunctionArgListDefinition"
		>> "" << createFunctionArgListDefinition;

	grammar["nonEmptyFunctionArgListDefinition"]
		>> "identifier" << createFunctionArgListDefinition
		>> "nonEmptyFunctionArgListDefinition" << ',' << "identifier" << createFunctionArgListDefinition;

	grammar["constantExpression"]
		>> "literal";

	grammar["literal"]
		>> new CCharacterSetTokenMatcher("0123456789") << createNumberLiteral
		>> "stringLiteral"
		>> "booleanLiteral" << createNumberLiteral;

	grammar["stringLiteral"]
		>> "singleStringLiteral"
		>> "stringLiteral" << "singleStringLiteral" << concatStringLiteral;

	grammar["singleStringLiteral"]
		>> new CStringLiteralTokenMatcher() << createStringLiteral;

	grammar["booleanLiteral"]
		>> "true"
		>> "false";

	grammar["identifier"]
		>> new CIdentifierTokenMatcher();

	return pGrammar;
}

CSokript::CSokript()
{

}

void CSokript::addExternalObject(const CString& name, CObject::Ptr object)
{
	mExternalObjects.insert(std::make_pair(name, object));
}

struct CExternalFunction : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CExternalFunction)
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELECTOR_WITH_NAME(operator(), __func__)
	LE_RTTI_END

	CObject::Ptr operator()(CObject::Ptr arg)
	{
		return mFunction(arg);
	}

	TScriptFunction mFunction;
};

LE_IMPLEMENT_RUNTIME_CLASS(CExternalFunction);

void CSokript::addExternalFunction(const CString& name, TScriptFunction function)
{
	CExternalFunction* fn = new CExternalFunction;
	fn->mFunction = function;
	addExternalObject(name, fn);
}

bool CSokript::compileStream(std::istream& stream, std::ostream& ostream)
{
	CParser parser;
	parser.setGrammar(sokripGrammar());

	CSokriptInstruction::Ptr instruction = parser.parse(stream).upcast<CSokriptInstruction>();
	if (instruction)
	{
		instruction->showAll(std::cout);
		CSokriptInstruction::dumpBytecodeToStream(instruction, ostream);
		return true;
	}
	return false;
}

CObject::Ptr CSokript::runBytecode(const CData& bytecode)
{
	CData temp = bytecode;
	temp.retain();
	CSokriptVM vm;
	vm.setBytecode(&temp);
	vm.setExternalObjects(&mExternalObjects);
	return vm.performByteCode();
}

	} // namespace le
} // namespace sokira
