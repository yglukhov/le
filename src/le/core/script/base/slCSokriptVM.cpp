
#include "slCSokriptInstruction.hp"
#include "slCSokriptVM.hp"

namespace sokira
{
	namespace le
	{


template<typename T>
struct SokriptVMStack
{
	inline SokriptVMStack(T* obj, SokriptVMStack* prev) :
		mObj(obj),
		mPrev(prev)
	{

	}

	T* pop(SokriptVMStack**stack)
	{
		LE_ASSERT(this);
		*stack = mPrev;
		T* result = mObj;
		delete this;
		return result;
	}

	T* mObj;
	SokriptVMStack* mPrev;
};

#define STACK_PUSH(name, type, obj)		((void)(name = new SokriptVMStack<type>(obj, name)))
#define STACK_POP(name)					(name->pop(&name))

#define OBJ_STACK_PUSH(obj) STACK_PUSH(varStack, CObject, obj)
#define OBJ_STACK_POP()		STACK_POP(varStack)

#define PC_STACK_PUSH(obj)	STACK_PUSH(pcStack, const UInt8, obj)
#define PC_STACK_POP()		STACK_POP(pcStack)



CSokriptVM::CSokriptVM() :
	mNext(NULL),
	mCurrentArg(NULL)
{

}

static void printObject(CObject* obj)
{
	CString* string = dynamic_cast<CString*> (obj);
	if (string)
		std::cout << *string << std::endl;
	else
	{
		CNumber* number = dynamic_cast<CNumber*> (obj);
		LE_ASSERT(number);
		std::cout << number->valueAsFloat32() << std::endl;
	}
//	delete obj;
}

CObject* CSokriptVM::assignObject(CString* name, CObject* value)
{
	CObject*& theSymbol = mSymbols[*name];
	LE_ASSERT(value);
	if (theSymbol)
	{
		delete theSymbol;
//		theSymbol = NULL;
	}

	CString *string = dynamic_cast<CString*>(value);
	if (string)
		theSymbol = new CString(*string);
	else
	{
		CNumber* number = dynamic_cast<CNumber*>(value);
		LE_ASSERT(number);
		theSymbol = new CNumber(*number);
	}

//	std::cout << "assignObject(" << *name << ", " << value->description() << "): " << theSymbol->description() << std::endl;

	return theSymbol;
}

CObject* CSokriptVM::findObject(CString* name)
{
	CObject*& theSymbol = mSymbols[*name];
	if (!theSymbol)
		theSymbol = new CString();
//	std::cout << "findObject(" << *name << "): " << theSymbol->description() << std::endl;
	return theSymbol;
}

static inline CObject* addObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() + rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CString(*leftString + *rightString);
	}

	if (leftString && rightNumber)
	{
		return new CString(*leftString + rightNumber->valueAsString());
	}

	if (leftNumber && rightString)
	{
		return new CString(leftNumber->valueAsString() + *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* substractObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() - rightNumber->valueAsFloat32());
	}

	LE_ASSERT(false);
	return new CNumber(2);
}

static inline CObject* multiplyObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() * rightNumber->valueAsFloat32());
	}

	LE_ASSERT(false);
	return new CNumber(3);
}

static inline CObject* divideObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() / rightNumber->valueAsFloat32());
	}

	LE_ASSERT(false);
	return new CNumber(4);
}

static inline CObject* negateObject(CObject* obj)
{
	// If obj is a number, negate it
	CNumber* number = dynamic_cast<CNumber*>(obj);
	if (number)
	{
		return new CNumber(- number->valueAsFloat32());
	}

	LE_ASSERT(false);
	return new CNumber(5);
}

static inline CObject* equalObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() == rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString == *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* notEqualObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() != rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString != *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* lessEqualObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() <= rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString <= *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* lessThanObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() < rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString < *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* greaterEqualObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() >= rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString >= *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static inline CObject* greaterThanObjects(CObject* left, CObject* right)
{
	// If both values are numbers, resulting value is number
	CNumber* leftNumber = dynamic_cast<CNumber*>(left);
	CNumber* rightNumber = dynamic_cast<CNumber*>(right);
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() > rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString* leftString = dynamic_cast<CString*>(left);
	CString* rightString = dynamic_cast<CString*>(right);

	if (leftString && rightString)
	{
		return new CNumber(*leftString > *rightString);
	}

	LE_ASSERT(false);
	return new CNumber(1);
}

static Bool objIsFalse(CObject* obj)
{
	CString* string = dynamic_cast<CString*> (obj);
	if (string)
	{
		return string->isEmpty();
	}

	CNumber* number = dynamic_cast<CNumber*> (obj);
	if (number)
	{
		return !number->valueAsBool();
	}

	LE_ASSERT(false);
	return 0;
}

static inline CObject* notObject(CObject* object)
{
	return new CNumber(!objIsFalse(object));
}

#if 1
#define LOG_INSTRUCTION(x) (x)
#else
#define LOG_INSTRUCTION(x)
#endif

void CSokriptVM::performByteCode(const CData& data)
{
	const UInt8* code = static_cast<const UInt8*>(data.data());
	SokriptVMStack<CObject> *varStack = NULL;
	SokriptVMStack<const UInt8> *pcStack = NULL;

	bool run = true;
	CObject ** symbols = NULL;

	PC_STACK_PUSH(NULL);

	do
	{
		switch (*code)
		{
			case eInstructionSetSymbolsCount:
				LOG_INSTRUCTION(std::cout << "eInstructionSetSymbolsCount");
				LE_ASSERT(symbols == NULL);
				symbols = new CObject*[(*(UInt32*)(code + 1)) + 1];
				code += sizeof(UInt32);
				break;

			case eInstructionNOP:
				LOG_INSTRUCTION(std::cout << "eInstructionNOP");
				break;

			case eInstructionPushVar:
				LOG_INSTRUCTION(std::cout << "eInstructionPushVar");
				LE_ASSERT(symbols);
				LE_ASSERT(symbols[(*(UInt32*)(code + 1))]);
				OBJ_STACK_PUSH(symbols[(*(UInt32*)(code + 1))]);
				code += sizeof(UInt32);
				break;

			case eInstructionPushStr:
				LOG_INSTRUCTION(std::cout << "eInstructionPushStr");
				OBJ_STACK_PUSH(new CString(CString::__CStringWithLiteral((char*)(code + sizeof(UInt32) + 1))));
				code += *((UInt32*)(code + 1)) + sizeof(UInt32);
				break;

			case eInstructionPushInt:
				LOG_INSTRUCTION(std::cout << "eInstructionPushInt");
				OBJ_STACK_PUSH(new CNumber(*((UInt32*)(code + 1))));
				code += sizeof(UInt32);
				break;

			case eInstructionPushFloat:
				LOG_INSTRUCTION(std::cout << "eInstructionPushFloat");
				OBJ_STACK_PUSH(new CNumber(*((Float32*)(code + 1))));
				code += sizeof(Float32);
				break;

			case eInstructionDiscard:
				LOG_INSTRUCTION(std::cout << "eInstructionDiscard");
				OBJ_STACK_POP();
				break;

			case eInstructionPrint:
				LOG_INSTRUCTION(std::cout << "eInstructionPrint" << std::endl);
				printObject(OBJ_STACK_POP());
				OBJ_STACK_PUSH(NULL);
				break;

			case eInstructionAssign:
				LOG_INSTRUCTION(std::cout << "eInstructionAssign");
				OBJ_STACK_PUSH(symbols[(*(UInt32*)(code + 1))] = OBJ_STACK_POP());
				code += sizeof(UInt32);
				break;

			case eInstructionAdd:
				LOG_INSTRUCTION(std::cout << "eInstructionAdd");
				OBJ_STACK_PUSH(addObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionSubstract:
				LOG_INSTRUCTION(std::cout << "eInstructionSubstract");
				OBJ_STACK_PUSH(substractObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionMultiply:
				LOG_INSTRUCTION(std::cout << "eInstructionMultiply");
				OBJ_STACK_PUSH(multiplyObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionDivide:
				LOG_INSTRUCTION(std::cout << "eInstructionDivide");
				OBJ_STACK_PUSH(divideObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionNegate:
				LOG_INSTRUCTION(std::cout << "eInstructionNegate");
				OBJ_STACK_PUSH(negateObject(OBJ_STACK_POP()));
				break;

			case eInstructionEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionEqual");
				OBJ_STACK_PUSH(equalObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionNotEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionNotEqual");
				OBJ_STACK_PUSH(notEqualObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionGreaterThan:
				LOG_INSTRUCTION(std::cout << "eInstructionGreaterThan");
				OBJ_STACK_PUSH(greaterThanObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionGreaterEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionGreaterEqual");
				OBJ_STACK_PUSH(greaterEqualObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionLessThan:
				LOG_INSTRUCTION(std::cout << "eInstructionLessThan");
				OBJ_STACK_PUSH(lessThanObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionLessEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionLessEqual");
				OBJ_STACK_PUSH(lessEqualObjects(OBJ_STACK_POP(), OBJ_STACK_POP()));
				break;

			case eInstructionNot:
				OBJ_STACK_PUSH(notObject(OBJ_STACK_POP()));
				break;

			case eInstructionJumpIfTrue:
				LOG_INSTRUCTION(std::cout << "eInstructionJumpIfTrue : " << (*(SInt32*)(code + 1)));
				if (objIsFalse(OBJ_STACK_POP())) { code += sizeof(SInt32); break; }// Else continue with next case

			case eInstructionJump:
				LOG_INSTRUCTION(std::cout << "eInstructionJump : " << (*(SInt32*)(code + 1)));
				if ((*(SInt32*)(code + 1)) > 0)
					code += (*(SInt32*)(code + 1)) + sizeof(SInt32);
				else
					code += (*(SInt32*)(code + 1));
				break;

			case eInstructionJumpIfFalse:
				LOG_INSTRUCTION(std::cout << "eInstructionJumpIfFalse");
				code += (objIsFalse(OBJ_STACK_POP())?(*(UInt32*)(code + 1)):(0)) + sizeof(UInt32);
				break;

			case eInstructionReturn:
				LOG_INSTRUCTION(std::cout << "eInstructionReturn");
				code = PC_STACK_POP();
				if (code)
					OBJ_STACK_PUSH(NULL);
				else
					run = false;
				break;

			case eInstructionStartFunction:
				LOG_INSTRUCTION(std::cout << "eInstructionStartFunction");
				symbols[*(UInt32*)(code + 1)] = (CObject*)(code + 1 + sizeof(UInt32) + sizeof(SInt32));
				code += sizeof(UInt32);
				break;

			case eInstructionCall:
				LOG_INSTRUCTION(std::cout << "eInstructionCall");
				PC_STACK_PUSH(code + sizeof(UInt32));
				code = (UInt8*) symbols[*(UInt32*)(code + 1)];
				break;

			default:
				LOG_INSTRUCTION(std::cout << "Invalid instruction: " << (int) *code);
				LE_ASSERT_MESSAGE(false, "Invalid instruction!");
		}
		LOG_INSTRUCTION(std::cout << std::endl);
		++code;
	} while (run);
}

	} // namespace le
} // namespace sokira
