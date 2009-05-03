#include <vector>
#include <le/core/slCNumber.h>

#include "slCSokriptInstruction.hp"


namespace sokira
{
	namespace le
	{

#define _LE_INSTRUCTION_STRING_LIST(instruction) #instruction ,

static char * strings[] =
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
		delete mObjArg1;
	delete mNext;
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

		case eInstructionJumpIfFalse:
		case eInstructionCall:
		case eInstructionCallExternal:
		case eInstructionStartFunction:
		case eInstructionSetSymbolsCount:
			result += sizeof(UInt32);
			break;

		case eInstructionAssign:
		case eInstructionPushVar:
		case eInstructionJump:
		case eInstructionJumpToReturn:
		case eInstructionJumpIfTrue:
			result += sizeof(SInt32);
			break;

		case eInstructionPushFloat:
			result += sizeof(Float32);
			break;

		case eInstructionReturn:
			result += sizeof(UInt16);
			break;

		default:
			break;
	}
	return result;
}

static inline SInt32 findVarInArgs(std::list<char*>* args, const char* var)
{
	SInt32 result;
	for (std::list<char*>::iterator it = args->begin(); it != args->end(); ++it)
	{
		if (!strcmp(*it, var))
			break;
		++result;
	}

	return args->size() - result;
}

CSokriptInstruction* CSokriptInstruction::postProcessBytecode(CSokriptInstruction* instruction, std::list<char*>* arguments)
{
	UInt32 symbolIndexCounter = 0;
	std::map<CString, SInt32> varMap;
	std::map<CString, UInt32> functionMap;
	std::vector<CString> externFunctions;

	bool finalStage = !arguments;

	if (!arguments) arguments = new std::list<char*>();

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

	delete arguments;

	CSokriptInstruction* result = instruction;

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

CSokriptInstruction* CSokriptInstruction::optimizeByteCode(CSokriptInstruction* instruction)
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
			case eInstructionJumpIfFalse:
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

			case eInstructionReturn:
				{
					UInt16 intValue = i->mUInt16Arg1;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;

			default:
				break;
		}
	}
}

void CSokriptInstruction::showAll(int i) const
{
	show(i);
	if (mNext) mNext->showAll(i + 1);
}

void CSokriptInstruction::show(int i) const
{
	if (mInstruction > eInstructionCount_)
		std::cout << i << ": INVALID(" << mInstruction << ");" << std::endl;
	std::cout << i << ": " << strings[mInstruction];

	switch (mInstruction)
	{
		case eInstructionAssign:
		case eInstructionPushVar:
			if (mProcessed)
				std::cout << ": \"" << mSInt32Arg1 << "\"";
			else
				std::cout << ": \"" << *(dynamic_cast<CString*> (mObjArg1)) << "\"";
			break;

		case eInstructionDeclareExternalFunction:
		case eInstructionPushStr:
			std::cout << ": \"" << *(dynamic_cast<CString*> (mObjArg1)) << "\"";
			break;

		case eInstructionPushFloat:
			std::cout << ": \"" << dynamic_cast<CNumber*> (mObjArg1)->valueAsFloat32() << "\"";
			break;

		case eInstructionCallExternal:
		case eInstructionSetSymbolsCount:
			std::cout << ": \"" << mUInt32Arg1 << "\"";
			break;

		case eInstructionReturn:
			std::cout << ": " << mUInt16Arg1;
			break;

		case eInstructionJumpIfFalse:
		{
			UInt32 offset = mUInt32Arg1;
			UInt32 instrCount = 0;
			UInt32 instrSize = 0;
			for(CSokriptInstruction* j = mNext; j && instrSize <= offset; j = j->mNext)
			{
				instrSize += j->selfLength();
				++instrCount;
			}

			std::cout << ": \"" << offset << "\"" << " target: " << i + instrCount;
			break;
		}

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

			std::cout << ": \"" << offset << "\"" << " target: ";
			if (instrCount)
				std::cout << i + instrCount;
			else
				std::cout << "negative";

			break;
		}

		default: ;
	}

	std::cout << ";" << std::endl;
}

	} // namespace le
} // namespace sokira
