#include <vector>
#include <sstream>
#include <le/core/slCNumber.h>

#include "slCSokriptInstruction.hp"


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CSokriptInstruction);

#define _LE_INSTRUCTION_STRING_LIST(instruction) #instruction ,

static const char * strings[] =
{
	"eInstructionNOP",
	_LE_FOR_INSTRUCTION_LIST(_LE_INSTRUCTION_STRING_LIST)
	"eInstructionCount_"
};

CSokriptInstruction::~CSokriptInstruction()
{
	LE_ASSERT(this);
	if ((mInstruction == eInstructionPushVar && !mProcessed)
		|| (mInstruction == eInstructionAssign && !mProcessed)
		|| (mInstruction == eInstructionCall && !mProcessed)
		|| (mInstruction == eInstructionCallExternal && !mProcessed)
		|| (mInstruction == eInstructionStartFunction && !mProcessed)
		|| mInstruction == eInstructionPushStr
		|| mInstruction == eInstructionDeclareExternalFunction
		|| mInstruction == eInstructionPushFloat
		|| mInstruction == eInstructionPushInt)
	{
		if (mObjArg1)
		{
			mObjArg1->release();
		}
	}

	if (mNext)
	{
		mNext->release();
	}
}
		
CSokriptInstruction* CSokriptInstruction::createIfThenElse(CSokriptInstruction* expression,
											 CSokriptInstruction* ifPart,
											 CSokriptInstruction* elsePart)
{
	if (elsePart)
	{
		CSokriptInstruction* firstJump = new CSokriptInstruction(eInstructionJumpIfTrue);
		firstJump->mSInt32Arg1 = elsePart->length();


		if (ifPart)
		{
			CSokriptInstruction* secondJump = new CSokriptInstruction(eInstructionJump);
			secondJump->mSInt32Arg1 = ifPart->length();
			secondJump->addInstruction(ifPart);
			elsePart->addInstruction(secondJump);
		}

		firstJump->addInstruction(elsePart);
		expression->addInstruction(firstJump);
		return expression;
	}

	// else
	
	if (ifPart)
	{
		CSokriptInstruction* jump = new CSokriptInstruction(eInstructionJumpIfTrue);
		jump->mUInt32Arg1 = ifPart->length();
		jump->addInstruction(ifPart);
		CSokriptInstruction* invert = new CSokriptInstruction(eInstructionNot);
		invert->addInstruction(jump);
		expression->addInstruction(invert);
	}
	else
		expression->addInstruction(new CSokriptInstruction(eInstructionDiscard));
	
	return expression;
}

CSokriptInstruction* CSokriptInstruction::createLoop(
									   CSokriptInstruction* expression,
									   CSokriptInstruction* loopPart)
{
	if (loopPart)
	{
		expression->addInstruction(new CSokriptInstruction(eInstructionNot));
		CSokriptInstruction* jumpBack = new CSokriptInstruction(eInstructionJump);
		CSokriptInstruction* jump = new CSokriptInstruction(eInstructionJumpIfTrue);
		jump->mUInt32Arg1 = loopPart->length() + jumpBack->length();
		jump->addInstruction(loopPart);
		expression->addInstruction(jump);
		jumpBack->mSInt32Arg1 = -(SInt32)(expression->length() + 1);
		loopPart->addInstruction(jumpBack);
	}
	else
	{
		CSokriptInstruction* jumpBack = new CSokriptInstruction(eInstructionJumpIfTrue);
		jumpBack->mSInt32Arg1 = -(SInt32)(expression->length() + 1);
		expression->addInstruction(jumpBack);
	}
	
	return expression;
}

CSokriptInstruction* CSokriptInstruction::createFunctionDefinition(char* name, std::list<CString>* args,
															CSokriptInstruction* instruction)
{
	if (instruction)
		instruction->addReturn0Instruction();
	else
		instruction = return0Instruction();

	instruction = CSokriptInstruction::postProcessBytecode(instruction, args).retain().get();

	CSokriptInstruction* functionStart = new CSokriptInstruction(eInstructionStartFunction,
													new CString(CString::__CStringNoCopyDeallocWithFree(name)));

	functionStart->mUInt32Arg2 = instruction->length();
	functionStart->addInstruction(instruction);

	return functionStart;
}

CSokriptInstruction* CSokriptInstruction::return0Instruction()
{
	CSokriptInstruction* result = new CSokriptInstruction(eInstructionPushFloat, new CNumber());
	result->addInstruction(new CSokriptInstruction(eInstructionReturn));
	return result;
}


UInt32 CSokriptInstruction::length() const
{
	UInt32 result = selfLength();
	if (mNext) result += mNext->length();
	return result;
}

UInt32 CSokriptInstruction::selfLength() const
{
	UInt32 result = 1;
	switch (mInstruction)
	{
		case eInstructionPushStr:
		case eInstructionDeclareExternalFunction:
			result += dynamic_cast<CString*> (mObjArg1)->length() + 1;
			// No break here

		case eInstructionCall:
		case eInstructionCallExternal:
		case eInstructionStartFunction:
		case eInstructionSetSymbolsCount:
			result += sizeof(UInt32);
			break;

		case eInstructionAssign:
		case eInstructionPushVar:
		case eInstructionJump:
		case eInstructionJumpIfTrue:
			result += sizeof(SInt32);
			break;

		case eInstructionPushFloat:
			result += sizeof(Float32);
			break;

		default:
			break;
	}
	return result;
}

static inline SInt32 findVarInArgs(std::list<CString>* args, const char* var)
{
	SInt32 result = 0;
	for (std::list<CString>::iterator it = args->begin(); it != args->end(); ++it)
	{
		if (*it == var)
			break;
		++result;
	}

	return args->size() - result;
}

CSokriptInstruction::Ptr CSokriptInstruction::postProcessBytecode(CSokriptInstruction::Ptr instruction, std::list<CString>* arguments)
{
	UInt32 symbolIndexCounter = 0;
	std::map<CString, SInt32> varMap;
	std::map<CString, UInt32> functionMap;
	std::vector<CString> externFunctions;

	bool finalStage = !arguments;

	bool argsShoudBeDeleted = false;
	if (!arguments)
	{
		arguments = new std::list<CString>();
		argsShoudBeDeleted = true;
	}

	UInt32 offset = 0;

	for (CSokriptInstruction* i = instruction; i; i = i->mNext)
	{
		if (!i->mProcessed)
		{
			i->mProcessed = true;
			switch (i->mInstruction)
			{
				case eInstructionPushVar:
					{
						CString* string = dynamic_cast<CString*> (i->mObjArg1);
						SInt32 argIndex = findVarInArgs(arguments, string->cString());

						if (argIndex == 0)
						{
							std::map<CString, SInt32>::iterator it = varMap.find(*string);
							LE_ASSERT(it != varMap.end());
							argIndex = it->second;
						}
						else
							argIndex = -argIndex;

						delete i->mObjArg1;
						i->mSInt32Arg1 = argIndex;
					}
					break;

				case eInstructionAssign:
					{
						CString* string = dynamic_cast<CString*> (i->mObjArg1);
						SInt32 argIndex = findVarInArgs(arguments, string->cString());

						if (argIndex == 0)
						{
							std::map<CString, SInt32>::iterator it = varMap.find(*string);
							if (it == varMap.end())
							{
								varMap.insert(std::make_pair(*string, symbolIndexCounter));
								argIndex = symbolIndexCounter;
								++symbolIndexCounter;
							}
							else
								argIndex = it->second;
						}
						else
							argIndex = -argIndex;

						delete i->mObjArg1;
						i->mSInt32Arg1 = argIndex;
					}
					break;

				case eInstructionCall:
					{
						CString* string = dynamic_cast<CString*> (i->mObjArg1);
						std::map<CString, UInt32>::iterator it = functionMap.find(*string);
						if (it != functionMap.end())
						{
							delete i->mObjArg1;
							i->mUInt32Arg1 = offset - it->second + 1;
						}
						else if (finalStage)
						{
							std::vector<CString>::iterator it = std::find(externFunctions.begin(), externFunctions.end(), *string);
							if (it == externFunctions.end())
							{
								externFunctions.push_back(*dynamic_cast<CString*> (i->mObjArg1));
								delete i->mObjArg1;
								i->mUInt32Arg1 = externFunctions.size() - 1;
							}
							else
							{
								delete i->mObjArg1;
								i->mUInt32Arg1 = it - externFunctions.begin();
							}
							i->mInstruction = eInstructionCallExternal;
						}
						else
							i->mProcessed = false;
					}
					break;

				case eInstructionStartFunction:
					{
						CString* string = dynamic_cast<CString*> (i->mObjArg1);
						functionMap[*string] = offset + i->selfLength();
						delete i->mObjArg1;
						i->mSInt32Arg1 = i->mUInt32Arg2;
						i->mInstruction = eInstructionJump;
					}
					break;

				default:
					i->mProcessed = false;
			}
		}

		offset += i->selfLength();
	}

	if (argsShoudBeDeleted) delete arguments;

	CSokriptInstruction::Ptr result = instruction;

	if (!varMap.empty())
	{
		result = new CSokriptInstruction(eInstructionSetSymbolsCount);
		result->mProcessed = true;
		result->mUInt32Arg1 = varMap.size();
		result->addInstruction(instruction);
	}

	for (UInt32 i = 0; i < externFunctions.size(); ++i)
	{
		CSokriptInstruction* newInstruction = new CSokriptInstruction(eInstructionDeclareExternalFunction, new CString(externFunctions[externFunctions.size() - i - 1]));
		newInstruction->addInstruction(result);
		result = newInstruction;
	}

	return result;
}

CSokriptInstruction::Ptr CSokriptInstruction::optimizeByteCode(CSokriptInstruction::Ptr instruction)
{
	return instruction;
}

void CSokriptInstruction::dumpBytecodeToStream(const CSokriptInstruction* instruction, std::ostream& stream)
{
	for (const CSokriptInstruction* i = instruction; i; i = i->mNext)
	{
		UInt8 command = static_cast<UInt8> (i->mInstruction);
		stream.write((const char*)&command, sizeof(command));
		switch (command)
		{
			case eInstructionSetSymbolsCount:
			case eInstructionCall:
			case eInstructionCallExternal:
				{
					UInt32 intValue = i->mUInt32Arg1;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;

			case eInstructionPushVar:
			case eInstructionAssign:
			case eInstructionJump:
			case eInstructionJumpIfTrue:
				{
					SInt32 intValue = i->mSInt32Arg1;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;

			case eInstructionDeclareExternalFunction:
			case eInstructionPushStr:
				{
					CString* string = dynamic_cast<CString*> (i->mObjArg1);
					UInt32 size = string->length() + 1;
					stream.write((const char*)&size, sizeof(size));
					stream.write(string->cString(), size);
				}
				break;

			case eInstructionPushFloat:
				{
					Float32 value = dynamic_cast<CNumber*>(i->mObjArg1)->valueAsFloat32();
					stream.write((const char*)&value, sizeof(value));
				}
				break;

			default:
				break;
		}
	}
}

void CSokriptInstruction::showAll(std::ostream& s, int i) const
{
	show(s, i);
	if (mNext) mNext->showAll(s, i + 1);
}

void CSokriptInstruction::show(std::ostream& s, int i) const
{
	if (mInstruction > eInstructionCount_)
		s << i << ": INVALID(" << mInstruction << ");" << std::endl;
	s << i << ": " << strings[mInstruction];

	switch (mInstruction)
	{
		case eInstructionAssign:
		case eInstructionPushVar:
			if (mProcessed)
				s << ": \"" << mSInt32Arg1 << "\"";
			else
				s << ": \"" << *(dynamic_cast<CString*> (mObjArg1)) << "\"";
			break;

		case eInstructionDeclareExternalFunction:
		case eInstructionPushStr:
			s << ": \"" << *(dynamic_cast<CString*> (mObjArg1)) << "\"";
			break;

		case eInstructionPushFloat:
			s << ": \"" << dynamic_cast<CNumber*> (mObjArg1)->valueAsFloat32() << "\"";
			break;

		case eInstructionCallExternal:
		case eInstructionSetSymbolsCount:
			s << ": \"" << mUInt32Arg1 << "\"";
			break;

		case eInstructionJump:
		case eInstructionJumpIfTrue:
		{
			SInt32 offset = mSInt32Arg1;
			UInt32 instrCount = 0;
			SInt32 instrSize = 0;
			if (offset > 0)
			{
				for(CSokriptInstruction* j = mNext; j && instrSize <= offset; j = j->mNext)
				{
					instrSize += j->selfLength();
					++instrCount;
				}
			}

			s << ": \"" << offset << "\"" << " target: ";
			if (instrCount)
				s << i + instrCount;
			else
				s << "negative";

			break;
		}

		default: ;
	}

	s << ";" << std::endl;
}

CString CSokriptInstruction::description() const
{
	std::stringstream stream;
	showAll(stream);
	return stream.str().c_str();
}

	} // namespace le
} // namespace sokira
