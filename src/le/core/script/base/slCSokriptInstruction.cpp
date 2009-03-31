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
	if ((mInstruction == eInstructionPushVar && !mProcessed)
		|| (mInstruction == eInstructionAssign && !mProcessed)
		|| (mInstruction == eInstructionCall && !mProcessed)
		|| (mInstruction == eInstructionStartFunction && !mProcessed)
		|| mInstruction == eInstructionPushStr
		|| mInstruction == eInstructionPushFloat
		|| mInstruction == eInstructionPushInt)
		delete mArg;
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
			result += dynamic_cast<CString*> (mArg)->length() + 1;
			// No break here

		case eInstructionAssign:
		case eInstructionPushVar:
		case eInstructionJumpIfFalse:
		case eInstructionCall:
		case eInstructionStartFunction:
		case eInstructionSetSymbolsCount:
			result += sizeof(UInt32);
			break;

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

CSokriptInstruction* CSokriptInstruction::postProcessBytecode(CSokriptInstruction* instruction)
{
	UInt32 symbolIndexCounter = 0;
	std::map<CString, UInt32> symbolMap;

	for (CSokriptInstruction* i = instruction; i; i = i->mNext)
	{
		LE_ASSERT(!i->mProcessed);
		switch (i->mInstruction)
		{
			case eInstructionPushVar:
				{
					CString* string = dynamic_cast<CString*> (i->mArg);
					std::map<CString, UInt32>::iterator it = symbolMap.find(*string);
					LE_ASSERT(it != symbolMap.end());
					delete i->mArg;
					i->mArg = (CObject*)it->second;
				}
				break;
			case eInstructionAssign:
				{
					CString* string = dynamic_cast<CString*> (i->mArg);
					std::map<CString, UInt32>::iterator it = symbolMap.find(*string);
					if (it == symbolMap.end())
					{
						symbolMap.insert(std::make_pair(*string, symbolIndexCounter));
						delete i->mArg;
						i->mArg = (CObject*)symbolIndexCounter;
						++symbolIndexCounter;
					}
					else
					{
						delete i->mArg;
						i->mArg = (CObject*)it->second;
					}
				}
				break;

			case eInstructionCall:
				{
					CString* string = dynamic_cast<CString*> (i->mArg);
					std::map<CString, UInt32>::iterator it = symbolMap.find(*string);
					LE_ASSERT(it != symbolMap.end());
					delete i->mArg;
					i->mArg = (CObject*)it->second;
				}
				break;
			case eInstructionStartFunction:
				{
					CString* string = dynamic_cast<CString*> (i->mArg);
					std::map<CString, UInt32>::iterator it = symbolMap.find(*string);
					if (it == symbolMap.end())
					{
						symbolMap.insert(std::make_pair(*string, symbolIndexCounter));
						delete i->mArg;
						i->mArg = (CObject*)symbolIndexCounter;
						++symbolIndexCounter;
					}
					else
					{
						delete i->mArg;
						i->mArg = (CObject*)it->second;
					}
				}
				break;

			default:
				break;
		}

		i->mProcessed = true;
	}

	CSokriptInstruction* result = instruction;

	if (!symbolMap.empty())
	{
		result = new CSokriptInstruction(eInstructionSetSymbolsCount);
		result->mProcessed = true;
		result->mArg = (CObject*)(UInt32)symbolMap.size();
		result->addInstruction(instruction);
	}

	return result;
}

void CSokriptInstruction::optimizeByteCode(CSokriptInstruction* instruction)
{

}

void CSokriptInstruction::dumpBytecodeToStream(CSokriptInstruction* instruction, std::ostream& stream)
{
	for (CSokriptInstruction* i = instruction; i; i = i->mNext)
	{
		LE_ASSERT(i->mProcessed);
		UInt8 command = static_cast<UInt8> (i->mInstruction);
		stream.write((const char*)&command, sizeof(command));
		switch (command)
		{
			case eInstructionPushVar:
			case eInstructionAssign:
			case eInstructionSetSymbolsCount:
			case eInstructionJumpIfFalse:
			case eInstructionCall:
			case eInstructionStartFunction:
				{
					UInt32 intValue = (UInt32)i->mArg;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;
			case eInstructionJump:
			case eInstructionJumpIfTrue:
				{
					SInt32 intValue = (SInt32)i->mArg;
					stream.write((const char*)&intValue, sizeof(intValue));
				}
				break;
			case eInstructionPushStr:
				{
					CString* string = dynamic_cast<CString*> (i->mArg);
					UInt32 size = string->length() + 1;
					stream.write((const char*)&size, sizeof(size));
					stream.write(string->cString(), size);
				}
				break;
			case eInstructionPushFloat:
				{
					Float32 value = dynamic_cast<CNumber*>(i->mArg)->valueAsFloat32();
					stream.write((const char*)&value, sizeof(value));
				}
				break;
			default:
				break;
		}
	}
}

void CSokriptInstruction::showAll(int i)
{
	show(i);
	if (mNext) mNext->showAll(i + 1);
}

void CSokriptInstruction::show(int i)
{
	if (mInstruction > eInstructionCount_)
		std::cout << i << ": INVALID(" << mInstruction << ");" << std::endl;
	std::cout << i << ": " << strings[mInstruction];

	switch (mInstruction)
	{
		case eInstructionAssign:
		case eInstructionPushVar:
			if (mProcessed)
				std::cout << ": \"" << (UInt32)mArg << "\"";
			else
				std::cout << ": \"" << *(dynamic_cast<CString*> (mArg)) << "\"";
			break;

		case eInstructionPushStr:
			std::cout << ": \"" << *(dynamic_cast<CString*> (mArg)) << "\"";
			break;

		case eInstructionPushFloat:
			std::cout << ": \"" << dynamic_cast<CNumber*> (mArg)->valueAsFloat32() << "\"";
			break;

		case eInstructionSetSymbolsCount:
			std::cout << ": \"" << (UInt32)mArg << "\"";
			break;

		case eInstructionJumpIfFalse:
		{
			UInt32 offset = (UInt32)mArg;
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
			SInt32 offset = (SInt32)mArg;
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
