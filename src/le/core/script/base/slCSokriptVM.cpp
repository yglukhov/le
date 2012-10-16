#include <vector>
#include "slCSokriptInstruction.hp"
#include "slCSokriptVM.hp"

namespace sokira
{
	namespace le
	{

//#define LE_LOG_INSTRUCTIONS

CSokriptVM::CSokriptVM()
{
	reset();
}

static inline CObject::Ptr addObjects(CObject::Ptr left, CObject::Ptr right)
{
	// If both values are numbers, resulting value is number
	CNumber::Ptr leftNumber = left.upcast<CNumber>();
	CNumber::Ptr rightNumber = right.upcast<CNumber>();
	if (leftNumber && rightNumber)
	{
		return new CNumber(leftNumber->valueAsFloat32() + rightNumber->valueAsFloat32());
	}

	// If both values are strings, resulting value is string
	CString::Ptr leftString = left.upcast<CString>();
	CString::Ptr rightString = right.upcast<CString>();

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

template <template <typename> class Operator>
void CSokriptVM::arithmeticOperation()
{
	CNumber::Ptr rightNumber = mVarStack.pop().upcast<CNumber>();
	CNumber::Ptr leftNumber = mVarStack.pop().upcast<CNumber>();
	CObject::Ptr result;
	if (leftNumber && rightNumber)
	{
		result = new CNumber(Operator<CNumber>()(*leftNumber, *rightNumber));
	}
	else
	{
		LE_ASSERT(false);
		result = new CNumber();
	}
	mVarStack.push(result);
}

static inline CObject::Ptr negateObject(CObject::Ptr obj)
{
	// If obj is a number, negate it
	CNumber* number = dynamic_cast<CNumber*>(obj.get());

	if (number)
	{
		return new CNumber(- number->valueAsFloat32());
	}

	LE_ASSERT(false);
	return new CNumber(5);
}

template <template <typename> class Operator>
void CSokriptVM::operateObjects()
{
	CObject::Ptr right = mVarStack.pop();
	CObject::Ptr left = mVarStack.pop();

	CObject::Ptr result;
	
	// If both values are numbers, resulting value is number
	const CNumber* leftNumber = dynamic_cast<const CNumber*>(left.get());
	const CNumber* rightNumber = dynamic_cast<const CNumber*>(right.get());
	if (leftNumber && rightNumber)
	{
		result = new CNumber(Operator<CNumber>()(*leftNumber, *rightNumber));
	}
	else
	{
		// If both values are strings, resulting value is string
		const CString* leftString = dynamic_cast<const CString*>(left.get());
		const CString* rightString = dynamic_cast<const CString*>(right.get());

		if (leftString && rightString)
		{
			result = new CNumber(Operator<CString>()(*leftString, *rightString));
		}
		else
		{
			LE_ASSERT(false);
			result = new CNumber(1);
		}
	}
	mVarStack.push(result);
}

static Bool booleanFromObject(CObject::Ptr obj)
{
	CString* string = dynamic_cast<CString*> (obj.get());
	if (string)
	{
		return CNumber(*string).valueAsBool();
	}

	CNumber* number = dynamic_cast<CNumber*> (obj.get());
	if (number)
	{
		return number->valueAsBool();
	}

	LE_ASSERT(false);
	return false;
}


#ifdef LE_LOG_INSTRUCTIONS
#define LOG_INSTRUCTION(x) std::cout << "INSTRUCTION: "; (x); std::cout << std::endl;
#else
#define LOG_INSTRUCTION(x)
#endif

void dumpVarStack(SokriptVMStack<CObject::Ptr>* stack)
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

LE_INSTRUCTION_HANDLER(eInstructionDeclareExternalSymbols)
{
	CString symbols = CBasicString::__CStringWithLiteral((char*)(mCode + sizeof(UInt32) + 1));
	LOG_INSTRUCTION(std::cout << "eInstructionDeclareExternalSymbols: " << symbols);

	UInt32 startPos = 0;
	SInt32 pos = 0;
	Bool undefined = false;

	while (pos != -1)
	{
		pos = symbols.find('\n', startPos);
		SInt32 endPos = pos;
		if (endPos == -1)
		{
			endPos = symbols.length();
		}

		CString symbol = symbols.subString(startPos, endPos - startPos);

		std::map<CString, CObject::Ptr>::const_iterator it = mAllExternalObjects->find(symbol);
		if (it == mAllExternalObjects->end())
		{
			std::cout << "Undefined external symbol: " << symbol << std::endl;
			undefined = true;
		}

		mExternalObjects.push_back(it->second);
		startPos = endPos + 1;
	}

	LE_ASSERT(!undefined);

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
	LOG_INSTRUCTION(std::cout << "eInstructionPushFloat: " << *((Float32*)(mCode + 1)));
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
	CObject::Ptr right = mVarStack.pop();
	CObject::Ptr left = mVarStack.pop();
	mVarStack.push(addObjects(left, right));
}

LE_INSTRUCTION_HANDLER(eInstructionSubstract)
{
	LOG_INSTRUCTION(std::cout << "eInstructionSubstract");
	arithmeticOperation<std::minus>();
}

LE_INSTRUCTION_HANDLER(eInstructionMultiply)
{
	LOG_INSTRUCTION(std::cout << "eInstructionMultiply");
	arithmeticOperation<std::multiplies>();
}

LE_INSTRUCTION_HANDLER(eInstructionDivide)
{
	LOG_INSTRUCTION(std::cout << "eInstructionDivide");
	arithmeticOperation<std::divides>();
}

LE_INSTRUCTION_HANDLER(eInstructionNegate)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNegate");
	mVarStack.push(negateObject(mVarStack.pop()));
}

LE_INSTRUCTION_HANDLER(eInstructionEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionEqual");
	operateObjects<std::equal_to>();
}

LE_INSTRUCTION_HANDLER(eInstructionNotEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNotEqual");
	operateObjects<std::not_equal_to>();
}

LE_INSTRUCTION_HANDLER(eInstructionGreaterThan)
{
	LOG_INSTRUCTION(std::cout << "eInstructionGreaterThan");
	operateObjects<std::greater>();
}

LE_INSTRUCTION_HANDLER(eInstructionGreaterEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionGreaterEqual");
	operateObjects<std::greater_equal>();
}

LE_INSTRUCTION_HANDLER(eInstructionLessThan)
{
	LOG_INSTRUCTION(std::cout << "eInstructionLessThan");
	operateObjects<std::less>();
}

LE_INSTRUCTION_HANDLER(eInstructionLessEqual)
{
	LOG_INSTRUCTION(std::cout << "eInstructionLessEqual");
	operateObjects<std::less_equal>();
}

LE_INSTRUCTION_HANDLER(eInstructionNot)
{
	LOG_INSTRUCTION(std::cout << "eInstructionNot");
	mVarStack.push(new CNumber(!booleanFromObject(mVarStack.pop())));
}

LE_INSTRUCTION_HANDLER(eInstructionJumpIfTrue)
{
	SInt32 offset = *(SInt32*)(mCode + 1);
	LOG_INSTRUCTION(std::cout << "eInstructionJumpIfTrue : " << offset);
	mCode += sizeof(SInt32);
	if (booleanFromObject(mVarStack.pop())) { mCode += offset; }
}

LE_INSTRUCTION_HANDLER(eInstructionJump)
{
	LOG_INSTRUCTION(std::cout << "eInstructionJump : " << (*(SInt32*)(mCode + 1)));
	if ((*(SInt32*)(mCode + 1)) > 0)
		mCode += (*(SInt32*)(mCode + 1)) + sizeof(SInt32);
	else
		mCode += (*(SInt32*)(mCode + 1));
}

class CInternalFunction : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CInternalFunction)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CInternalFunction()
		{
			LE_ASSERT(false);
		}

		CInternalFunction(CSokriptVM* vm, const UInt8* start, UInt16 argsCount) :
			mVM(vm),
			mStart(start),
			mArgsCount(argsCount)
		{

		}

		CObject::Ptr operator()(UInt16 argsCount)
		{
			LE_ASSERT(argsCount == mArgsCount);
			UInt32 prevStackLine = mVM->mCurrentStackLine;
			mVM->mCurrentStackLine = mVM->mVarStack.position();
			const UInt8* code = mVM->mCode;

			CObject::Ptr result = mVM->performByteCode(mStart);

			UInt32 unwindVars = mVM->mVarStack.position() - prevStackLine - 1;
			mVM->mVarStack.decrease(unwindVars);

			mVM->mCode = code;
			mVM->mCurrentStackLine = prevStackLine;

			return result;
		}

	private:
		CSokriptVM* mVM;
		const UInt8* mStart;
		UInt16 mArgsCount;
};

LE_IMPLEMENT_RUNTIME_CLASS(CInternalFunction);

LE_INSTRUCTION_HANDLER(eInstructionPushFunction)
{
	UInt32 length = *((UInt32*)(mCode + 1));
	mCode += sizeof(UInt32);
	UInt16 argsCount = *((UInt16*)(mCode + 1));
	mCode += sizeof(UInt16);
	LOG_INSTRUCTION(std::cout << "eInstructionPushFunction, length: " << length << ", argsCount: " << argsCount);

	mVarStack.push(new CInternalFunction(this, mCode + 1, argsCount));
	mCode += length;
}

LE_INSTRUCTION_HANDLER(eInstructionCall)
{
	UInt16 argsCount = *((UInt16*)(mCode + 1));
	LOG_INSTRUCTION(std::cout << "eInstructionCall: " << argsCount);
	UInt32 varStackPosition = mVarStack.position();
	CObject* func = mVarStack.objectAtIndex(varStackPosition - argsCount - 1);
	CInternalFunction* internalFunc = dynamic_cast<CInternalFunction*>(func);
	CObject::Ptr result;
	if (internalFunc)
	{
		result = (*internalFunc)(argsCount);
	}
	else
	{
		CString selectorName = LESTR("__func__");
		if (func->respondsToSelector(selectorName))
		{
			std::vector<CBasicReferenceAny> arguments;
			arguments.reserve(argsCount);
			for (UInt32 i = varStackPosition - argsCount; i < varStackPosition; ++i)
			{
				arguments.push_back(mVarStack.objectAtIndex(i));
			}
			result = func->selector(selectorName)(arguments).value<CObject::Ptr>();
		}
		else
		{
			std::cout << "Object does not respond to selector " << selectorName << ": " << func->description() << std::endl;
		}

		mVarStack.decrease(argsCount);
	}

	mCode += sizeof(UInt16);
	mVarStack.pop(); // Pop function object
	mVarStack.push(result);
}

LE_INSTRUCTION_HANDLER(eInstructionPushExternal)
{
	UInt32 index = *(UInt32*)(mCode + 1);
	LOG_INSTRUCTION(std::cout << "eInstructionPushExternal: " << index);
	mVarStack.push(mExternalObjects.at(index));
	mCode += sizeof(UInt32);
}

void CSokriptVM::reset()
{
	mVarStack = SokriptVMStack<CObject::Ptr>();
	mExternalObjects.clear();
	mCurrentStackLine = 0;
}

CObject::Ptr CSokriptVM::performByteCode(const UInt8* startPos)
{
	mCode = startPos;
	if (!mCode)
	{
		mCode = static_cast<const UInt8*>(mBytecode->data());
	}

#ifdef LE_LOG_INSTRUCTIONS
	UInt32 startPosIndex = mCode - static_cast<const UInt8*>(mBytecode->data());
	std::cout << "Entering at position: " << startPosIndex << std::endl;
#endif

	while (*mCode != eInstructionReturn)
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
	}

#ifdef LE_LOG_INSTRUCTIONS
	std::cout << "Returning from position: " << startPosIndex << std::endl;
#endif

	LE_ASSERT(mVarStack.position());
	return mVarStack.pop();
}

	} // namespace le
} // namespace sokira
