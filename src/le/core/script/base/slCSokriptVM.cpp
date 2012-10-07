#include <vector>
#include "slCSokriptInstruction.hp"
#include "slCSokriptVM.hp"

namespace sokira
{
	namespace le
	{

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


#ifdef LE_LOG_INSTRUCTIONS
#define LOG_INSTRUCTION(x) std::cout << "INSTRUCTION: "; (x); std::cout << std::endl;
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

#define LE_INSTRUCTION_HANDLER(instruction) template <> void CSokriptVM::handleInstruction<instruction>()
#define LE_DUMMY_INSTRUCTION(instruction) LE_INSTRUCTION_HANDLER(instruction) { LE_ASSERT(false); }

LE_DUMMY_INSTRUCTION(eInstructionNOP);
LE_DUMMY_INSTRUCTION(eInstructionStartFunction);

LE_INSTRUCTION_HANDLER(eInstructionSetSymbolsCount)
{
	LOG_INSTRUCTION(std::cout << "eInstructionSetSymbolsCount: " << *(UInt32*)(mCode + 1));
	mVarStack.increase(*(UInt32*)(mCode + 1));
	mCode += sizeof(UInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionPushVar)
{
	LOG_INSTRUCTION(std::cout << "eInstructionPushVar: " << *(SInt32*)(mCode + 1) << ", stackLine: " << mCurrentStackLine);
	mVarStack.push(mVarStack.objectAtIndex(mCurrentStackLine + *(SInt32*)(mCode + 1)));
	mCode += sizeof(SInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionPushStr)
{
	LOG_INSTRUCTION(std::cout << "eInstructionPushStr");
	mVarStack.push(new CString((char*)(mCode + sizeof(UInt32) + 1)));
	mCode += *((UInt32*)(mCode + 1)) + sizeof(UInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionDeclareExternalFunction)
{
	LOG_INSTRUCTION(std::cout << "eInstructionDeclareExternalFunction: " << (char*)(mCode + sizeof(UInt32) + 1));
	mExternFunctions.push_back((char*)(mCode + sizeof(UInt32) + 1));
	mCode += *((UInt32*)(mCode + 1)) + sizeof(UInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionPushInt)
{
	LOG_INSTRUCTION(std::cout << "eInstructionPushInt");
	mVarStack.push(new CNumber(*((UInt32*)(mCode + 1))));
	mCode += sizeof(UInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionPushFloat)
{
	LOG_INSTRUCTION(std::cout << "eInstructionPushFloat");
	mVarStack.push(new CNumber(*((Float32*)(mCode + 1))));
	mCode += sizeof(Float32);
}

LE_INSTRUCTION_HANDLER(eInstructionDiscard)
{
	LOG_INSTRUCTION(std::cout << "eInstructionDiscard");
	mVarStack.pop();
}

LE_INSTRUCTION_HANDLER(eInstructionAssign)
{
	LOG_INSTRUCTION(std::cout << "eInstructionAssign");
	mVarStack.setObjectAtIndex(mCurrentStackLine + *(SInt32*)(mCode + 1), mVarStack.pop());
	mVarStack.push(mVarStack.objectAtIndex(mCurrentStackLine + *(SInt32*)(mCode + 1)));
	mCode += sizeof(SInt32);
}

LE_INSTRUCTION_HANDLER(eInstructionAdd)
{
	LOG_INSTRUCTION(std::cout << "eInstructionAdd");
	mVarStack.push(addObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionSubstract)
{
	LOG_INSTRUCTION(std::cout << "eInstructionSubstract");
	mVarStack.push(substractObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionMultiply)
{
	LOG_INSTRUCTION(std::cout << "eInstructionMultiply");
	mVarStack.push(multiplyObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionDivide)
{
	LOG_INSTRUCTION(std::cout << "eInstructionDivide");
	mVarStack.push(divideObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionNegate)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNegate");
	mVarStack.push(negateObject(mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionEqual");
	mVarStack.push(equalObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionNotEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNotEqual");
	mVarStack.push(notEqualObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionGreaterThan)
{
	LOG_INSTRUCTION(std::cout << "eInstructionGreaterThan");
	mVarStack.push(greaterThanObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionGreaterEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionGreaterEqual");
	mVarStack.push(greaterEqualObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionLessThan)
{
	LOG_INSTRUCTION(std::cout << "eInstructionLessThan");
	mVarStack.push(lessThanObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionLessEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionLessEqual");
	mVarStack.push(lessEqualObjects(mVarStack.pop(), mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionNot)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNot");
	mVarStack.push(notObject(mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionJumpIfTrue)
{
	LOG_INSTRUCTION(std::cout << "eInstructionJumpIfTrue : " << (*(SInt32*)(mCode + 1)));
	if (objIsFalse(mVarStack.pop())) { mCode += sizeof(SInt32) + (*(SInt32*)(mCode + 1)); }
}

LE_INSTRUCTION_HANDLER(eInstructionJump)
{
	LOG_INSTRUCTION(std::cout << "eInstructionJump : " << (*(SInt32*)(mCode + 1)));
	if ((*(SInt32*)(mCode + 1)) > 0)
		mCode += (*(SInt32*)(mCode + 1)) + sizeof(SInt32);
	else
		mCode += (*(SInt32*)(mCode + 1));
}

LE_INSTRUCTION_HANDLER(eInstructionReturn)
{
	LOG_INSTRUCTION(std::cout << "eInstructionReturn");
//	UInt16 unwindVars = *(UInt16*)(mCode + 1);
	mCode = mPcStack.pop();
	if (mCode)
	{
		CObject* returnValue = mVarStack.pop();
		mCurrentStackLine = mStackLineStack.pop();
		UInt32 unwindVars = mVarStack.position() - mCurrentStackLine;
		mVarStack.decrease(unwindVars);
		mVarStack.push(returnValue);
	}
}

LE_INSTRUCTION_HANDLER(eInstructionPushFunction)
{
	LOG_INSTRUCTION(std::cout << "eInstructionPushFunction");
	// TODO.
}

LE_INSTRUCTION_HANDLER(eInstructionCall)
{
	LOG_INSTRUCTION(std::cout << "eInstructionCall");
	mCurrentStackLine = mVarStack.position();
	mStackLineStack.push(mCurrentStackLine);
	mPcStack.push(mCode + sizeof(UInt32));
	mCode -= *(UInt32*)(mCode + 1);
}

LE_INSTRUCTION_HANDLER(eInstructionCallExternal)
{
	LOG_INSTRUCTION(std::cout << "eInstructionCallExternal: " << *(UInt32*)(mCode + 1));
	mVarStack.push(mFunctions[mExternFunctions[*(UInt32*)(mCode + 1)]](mVarStack.pop()));
	mCode += sizeof(UInt32);
}

void CSokriptVM::performByteCode(const CData& data)
{
	mCode = static_cast<const UInt8*>(data.data());
	mVarStack = SokriptVMStack<CObject*>();
	mPcStack = SokriptVMStack<const UInt8*>();
	mStackLineStack = SokriptVMStack<UInt32>();

	mFunctions[LESTR("print")] = &printObject;
	mFunctions[LESTR("print1")] = &print1;
	mFunctions[LESTR("print2")] = &print2;
	mFunctions[LESTR("print3")] = &print3;

	mPcStack.push(NULL);
	mStackLineStack.push(0);

	mCurrentStackLine = 0;

	mExternFunctions.clear();

#ifdef LE_LOG_INSTRUCTIONS
	mVarStack.mTraceRealloc = true;
#endif

	do
	{
		switch (*mCode)
		{

#define LE_HANDLE_INSTRUCTION(code) case code: handleInstruction<code>(); break;
_LE_FOR_INSTRUCTION_LIST(LE_HANDLE_INSTRUCTION)

			default:
				LOG_INSTRUCTION(std::cout << "Invalid instruction: " << (int) *mCode);
				LE_ASSERT_MESSAGE(false, "Invalid instruction!");
		}

#ifdef LE_LOG_INSTRUCTIONS
		std::cout << std::endl;
		dumpVarStack(&mVarStack);
#endif
		++mCode;
	} while (mPcStack.position() > 0);

	if (mVarStack.position() == 1)
	{
		std::cout << "Stack result: " << mVarStack.objectAtIndex(0)->description() << std::endl;
	}
}

	} // namespace le
} // namespace sokira
