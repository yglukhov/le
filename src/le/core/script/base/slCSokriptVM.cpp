#include <vector>
#include "slCSokriptInstruction.hp"
#include "slCSokriptVM.hp"

namespace sokira
{
	namespace le
	{


#define REALLOC_COEF 1.5
//#define LOG_INSTRUCTIONS

template<typename T>
struct SokriptVMStack
{
	inline SokriptVMStack() :
		mSize(0),
		mBuffer(NULL),
		mPosition(0)
#ifdef LOG_INSTRUCTIONS
		, mTraceRealloc(false)
#endif
	{

	}

	inline ~SokriptVMStack()
	{
		if (mBuffer) free(mBuffer);
	}

	void push(T obj)
	{
		if (mPosition + 1 >= mSize) reallocate(1);
		mBuffer[mPosition++] = obj;
	}

	T pop()
	{
		LE_ASSERT(mPosition);
		return mBuffer[--mPosition];
	}

	void increase(UInt32 bySize)
	{
		if (mPosition + bySize >= mSize) reallocate(bySize);

#ifdef LOG_INSTRUCTIONS
		UInt32 newPosition = mPosition + bySize;
		for (; mPosition < newPosition; ++mPosition)
		{
			mBuffer[mPosition] = NULL;
		}
#else
		mPosition += bySize;
#endif
	}

	void decrease(UInt32 bySize)
	{
		mPosition -= bySize;
	}

	void reallocate(UInt32 bySize)
	{
		UInt32 newSize = mSize * REALLOC_COEF + 1;
		if (newSize < mSize + bySize) newSize = mSize + bySize;
#ifdef LOG_INSTRUCTIONS
		if (mTraceRealloc) std::cout << "Reallocating stack. Old size: " << mSize << ", new size: " << newSize << std::endl;
#endif
		mSize = newSize;

		mBuffer = (T*)realloc(mBuffer, newSize * sizeof(T));
	}

	T objectAtIndex(UInt32 pos)
	{
		return mBuffer[pos];
	}

	void setObjectAtIndex(UInt32 pos, T obj)
	{
		mBuffer[pos] = obj;
	}

	UInt32 position()
	{
		return mPosition;
	}

	UInt32 mSize;
	T* mBuffer;
	UInt32 mPosition;

#ifdef LOG_INSTRUCTIONS
	Bool mTraceRealloc;
#endif
};


CSokriptVM::CSokriptVM()
{

}

static CObject* printObject(CObject* obj)
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
	return new CNumber();
}

static CObject* print1(CObject* obj)
{
	std::cout << "print1: ";
	return printObject(obj);
}

static CObject* print2(CObject* obj)
{
	std::cout << "print2: ";
	return printObject(obj);
}

static CObject* print3(CObject* obj)
{
	std::cout << "print3: ";
	return printObject(obj);
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


#ifdef LOG_INSTRUCTIONS
#define LOG_INSTRUCTION(x) std::cout << "INSTRUCTION: "; (x);
#else
#define LOG_INSTRUCTION(x)
#endif

void dumpVarStack(SokriptVMStack<CObject*>* stack)
{
	UInt32 pos = stack->position();
	for (UInt32 i = 0; i < pos; ++i)
	{
		CObject* obj = stack->objectAtIndex(i);
		std::cout << i << ": ";
		if (obj)
			std::cout << obj->description();
		else
			std::cout << "NULL";
		std::cout << std::endl;
	}
}

void CSokriptVM::performByteCode(const CData& data)
{
	const UInt8* code = static_cast<const UInt8*>(data.data());
	SokriptVMStack<CObject*> varStack;
	SokriptVMStack<const UInt8*> pcStack;
	SokriptVMStack<UInt32> stackLineStack;

	std::vector<CString> externFunctions;

	mFunctions[LESTR("print")] = &printObject;
	mFunctions[LESTR("print1")] = &print1;
	mFunctions[LESTR("print2")] = &print2;
	mFunctions[LESTR("print3")] = &print3;

	bool run = true;

	pcStack.push(NULL);
	stackLineStack.push(0);

	UInt32 currentStackLine = 0;


#ifdef LOG_INSTRUCTIONS
	varStack.mTraceRealloc = true;
#endif

	do
	{
		switch (*code)
		{
			case eInstructionSetSymbolsCount:
				LOG_INSTRUCTION(std::cout << "eInstructionSetSymbolsCount: " << *(UInt32*)(code + 1));
				varStack.increase(*(UInt32*)(code + 1));
				code += sizeof(UInt32);
				break;

			case eInstructionNOP:
				LOG_INSTRUCTION(std::cout << "eInstructionNOP");
				break;

			case eInstructionPushVar:
				LOG_INSTRUCTION(std::cout << "eInstructionPushVar: " << *(SInt32*)(code + 1) << ", stackLine: " << currentStackLine);
				varStack.push(varStack.objectAtIndex(currentStackLine + *(SInt32*)(code + 1)));
				code += sizeof(SInt32);
				break;

			case eInstructionPushStr:
				LOG_INSTRUCTION(std::cout << "eInstructionPushStr");
				varStack.push(new CString(CString::__CStringWithLiteral((char*)(code + sizeof(UInt32) + 1))));
				code += *((UInt32*)(code + 1)) + sizeof(UInt32);
				break;

			case eInstructionDeclareExternalFunction:
				LOG_INSTRUCTION(std::cout << "eInstructionDeclareExternalFunction: " << (char*)(code + sizeof(UInt32) + 1));
				externFunctions.push_back(CString::__CStringWithLiteral((char*)(code + sizeof(UInt32) + 1)));
				code += *((UInt32*)(code + 1)) + sizeof(UInt32);
				break;

			case eInstructionPushInt:
				LOG_INSTRUCTION(std::cout << "eInstructionPushInt");
				varStack.push(new CNumber(*((UInt32*)(code + 1))));
				code += sizeof(UInt32);
				break;

			case eInstructionPushFloat:
				LOG_INSTRUCTION(std::cout << "eInstructionPushFloat");
				varStack.push(new CNumber(*((Float32*)(code + 1))));
				code += sizeof(Float32);
				break;

			case eInstructionDiscard:
				LOG_INSTRUCTION(std::cout << "eInstructionDiscard");
				varStack.pop();
				break;

			case eInstructionAssign:
				LOG_INSTRUCTION(std::cout << "eInstructionAssign");
				varStack.setObjectAtIndex(currentStackLine + *(SInt32*)(code + 1), varStack.pop());
				varStack.push(varStack.objectAtIndex(currentStackLine + *(SInt32*)(code + 1)));
				code += sizeof(SInt32);
				break;

			case eInstructionAdd:
				LOG_INSTRUCTION(std::cout << "eInstructionAdd");
				varStack.push(addObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionSubstract:
				LOG_INSTRUCTION(std::cout << "eInstructionSubstract");
				varStack.push(substractObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionMultiply:
				LOG_INSTRUCTION(std::cout << "eInstructionMultiply");
				varStack.push(multiplyObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionDivide:
				LOG_INSTRUCTION(std::cout << "eInstructionDivide");
				varStack.push(divideObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionNegate:
				LOG_INSTRUCTION(std::cout << "eInstructionNegate");
				varStack.push(negateObject(varStack.pop()));
				break;

			case eInstructionEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionEqual");
				varStack.push(equalObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionNotEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionNotEqual");
				varStack.push(notEqualObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionGreaterThan:
				LOG_INSTRUCTION(std::cout << "eInstructionGreaterThan");
				varStack.push(greaterThanObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionGreaterEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionGreaterEqual");
				varStack.push(greaterEqualObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionLessThan:
				LOG_INSTRUCTION(std::cout << "eInstructionLessThan");
				varStack.push(lessThanObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionLessEqual:
				LOG_INSTRUCTION(std::cout << "eInstructionLessEqual");
				varStack.push(lessEqualObjects(varStack.pop(), varStack.pop()));
				break;

			case eInstructionNot:
				varStack.push(notObject(varStack.pop()));
				break;

			case eInstructionJumpIfTrue:
				LOG_INSTRUCTION(std::cout << "eInstructionJumpIfTrue : " << (*(SInt32*)(code + 1)));
				if (objIsFalse(varStack.pop())) { code += sizeof(SInt32); break; }// Else continue with next case

			case eInstructionJump:
				LOG_INSTRUCTION(std::cout << "eInstructionJump : " << (*(SInt32*)(code + 1)));
				if ((*(SInt32*)(code + 1)) > 0)
					code += (*(SInt32*)(code + 1)) + sizeof(SInt32);
				else
					code += (*(SInt32*)(code + 1));
				break;

			case eInstructionJumpIfFalse:
				LOG_INSTRUCTION(std::cout << "eInstructionJumpIfFalse");
				code += (objIsFalse(varStack.pop())?(*(UInt32*)(code + 1)):(0)) + sizeof(UInt32);
				break;

			case eInstructionReturn:
				LOG_INSTRUCTION(std::cout << "eInstructionReturn : " << *(UInt16*)(code + 1));
				{
					UInt16 unwindVars = *(UInt16*)(code + 1);
					code = pcStack.pop();
					if (code)
					{
						CObject* returnValue = varStack.pop();
						varStack.decrease(unwindVars);
						currentStackLine = stackLineStack.pop();
						varStack.push(returnValue);
					}
					else
						run = false;
					break;
				}

			case eInstructionCall:
				LOG_INSTRUCTION(std::cout << "eInstructionCall");
				currentStackLine = varStack.position();
				stackLineStack.push(currentStackLine);
				pcStack.push(code + sizeof(UInt32));
				code -= *(UInt32*)(code + 1);
				break;

			case eInstructionCallExternal:
				LOG_INSTRUCTION(std::cout << "eInstructionCallExternal: " << *(UInt32*)(code + 1));
				varStack.push(mFunctions[externFunctions[*(UInt32*)(code + 1)]](varStack.pop()));
				code += sizeof(UInt32);
				break;

			default:
				LOG_INSTRUCTION(std::cout << "Invalid instruction: " << (int) *code);
				LE_ASSERT_MESSAGE(false, "Invalid instruction!");
		}

#ifdef LOG_INSTRUCTIONS
		std::cout << std::endl;
		dumpVarStack(&varStack);
#endif
		++code;
	} while (run);
}

	} // namespace le
} // namespace sokira
