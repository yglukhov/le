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
		|| (mInstruction == eInstructionStartFunction && !mProcessed)
		|| mInstruction == eInstructionPushStr
		|| mInstruction == eInstructionDeclareExternalSymbols
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

CSokriptInstruction::Ptr CSokriptInstruction::createLoop(
									   CSokriptInstruction::Ptr expression,
									   CSokriptInstruction::Ptr loopPart)
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
		case eInstructionDeclareExternalSymbols:
			result += dynamic_cast<CString*> (mObjArg1)->length() + 1;
			// No break here

		case eInstructionPushExternal:
		case eInstructionStartFunction:
		case eInstructionSetSymbolsCount:
			result += sizeof(UInt32);
			break;

		case eInstructionPushFunction:
			result += sizeof(UInt32) + sizeof(UInt16);
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

		case eInstructionCall:
			result += sizeof(UInt16);
			break;

		default:
			break;
	}
	return result;
}

static inline SInt32 findVarInArgs(std::list<CString>* args, const CString& var)
{
	if (args)
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

	return 0;
}

CSokriptInstruction::Ptr CSokriptInstruction::postProcessBytecode(CSokriptInstruction::Ptr instruction, std::list<CString>* arguments)
{
	UInt32 symbolIndexCounter = 0;
	std::map<CString, SInt32> varMap;

	std::vector<CString> externalSymbols;

	bool finalStage = !arguments;

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
						SInt32 argIndex = findVarInArgs(arguments, *string);

						Bool symbolFound = true;

						if (argIndex == 0)
						{
							std::map<CString, SInt32>::iterator it = varMap.find(*string);
							if (it == varMap.end())
							{
								if (finalStage)
								{
									std::vector<CString>::iterator it = std::find(externalSymbols.begin(), externalSymbols.end(), *string);
									if (it == externalSymbols.end())
									{
										argIndex = externalSymbols.size();
										externalSymbols.push_back(*string);
									}
									else
									{
										argIndex = it - externalSymbols.begin();
									}
									i->mInstruction = eInstructionPushExternal;
								}
								else
								{
									symbolFound = false;
								}
							}
							else
							{
								argIndex = it->second;
							}
						}
						else
							argIndex = -argIndex;

						if (symbolFound)
						{
							i->mObjArg1->release();
							i->mSInt32Arg1 = argIndex;
						}
						else
						{
							i->mProcessed = false;
						}
					}
					break;

				case eInstructionAssign:
					{
						CString* string = dynamic_cast<CString*> (i->mObjArg1);
						SInt32 argIndex = findVarInArgs(arguments, *string);

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

				default:
					i->mProcessed = false;
			}
		}

		offset += i->selfLength();
	}

	CSokriptInstruction::Ptr result = instruction;

	if (!varMap.empty())
	{
		result = new CSokriptInstruction(eInstructionSetSymbolsCount);
		result->mProcessed = true;
		result->mUInt32Arg1 = varMap.size();
		result->addInstruction(instruction);
	}

	if (!externalSymbols.empty())
	{
		CString* symbols = new CString;
		bool first = true;
		for (std::vector<CString>::iterator it = externalSymbols.begin(); it != externalSymbols.end(); ++it)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				symbols->append('\n');
			}
			symbols->append(*it);
		}
		CSokriptInstruction* newInstruction = new CSokriptInstruction(eInstructionDeclareExternalSymbols, symbols);
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
			case eInstructionPushExternal:
			case eInstructionSetSymbolsCount:
				{
					UInt32 intValue = i->mUInt32Arg1;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;

			case eInstructionPushFunction:
				{
					UInt32 intValue = i->mUInt32Arg1;
					stream.write((const char*)&intValue, sizeof(intValue));
					UInt16 intValue2 = i->mUInt16Arg2;
					stream.write((const char*)&intValue2, sizeof(intValue2));
				}
				break;

			case eInstructionCall:
				{
					UInt16 intValue = i->mUInt16Arg1;
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

			case eInstructionDeclareExternalSymbols:
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

		case eInstructionDeclareExternalSymbols:
		case eInstructionPushStr:
			s << ": \"" << *(dynamic_cast<CString*> (mObjArg1)) << "\"";
			break;

		case eInstructionPushFloat:
			s << ": \"" << dynamic_cast<CNumber*> (mObjArg1)->valueAsFloat32() << "\"";
			break;

		case eInstructionPushExternal:
		case eInstructionSetSymbolsCount:
			s << ": \"" << mUInt32Arg1 << "\"";
			break;

		case eInstructionCall:
			s << ": \"" << mUInt16Arg1 << "\"";
			break;

		case eInstructionJump:
		case eInstructionJumpIfTrue:
		case eInstructionPushFunction:
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
