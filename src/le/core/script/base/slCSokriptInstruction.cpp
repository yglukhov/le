#include <vector>
#include <sstream>
#include <algorithm> // for std::find
#include <le/core/slCNumber.h>

#include "slCSokriptInstruction.hp"


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CSokriptInstruction);


const char* CSokriptInstruction::nameFromCode(EInstruction instruction)
{
#define _LE_INSTRUCTION_STRING_LIST(instruction) #instruction ,

	static const char * strings[] =
	{
		"eInstructionNOP",
		_LE_FOR_INSTRUCTION_LIST(_LE_INSTRUCTION_STRING_LIST)
		"eInstructionCount_"
	};

#undef _LE_INSTRUCTION_STRING_LIST

	if (instruction < 0 || instruction >= eInstructionCount_)
	{
		return NULL;
	}

	return strings[instruction];
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
			result += mObjArg1.upcast<CString>()->length() + 1;
			// No break here

		case eInstructionPushExternal:
		case eInstructionSetSymbolsCount:
			result += sizeof(UInt32);
			break;

		case eInstructionDeclareExternalSymbol:
		case eInstructionDeclareSymbol:
			result += mObjArg1.upcast<CString>()->length() + 1;
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

static SInt32 findVarInArgs(std::list<CString>* args, const CString& var)
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

template <class Table>
SInt32 symbolFromSymbolTable(Table& table, const CString& symbol, bool externalLink)
{
	SInt32 i = 0;
	for (typename Table::iterator it = table.begin(); it != table.end(); ++it)
	{
		if (it->first == symbol)
		{
			if (externalLink)
			{
				it->second = true;
			}
			return i;
		}
		++i;
	}

	table.push_back(typename Table::value_type(symbol, externalLink));
	return i;
}

CSokriptInstruction::Ptr CSokriptInstruction::postProcessBytecode(CSokriptInstruction::Ptr instruction, std::list<CString>* arguments)
{
	UInt32 symbolIndexCounter = 0;
	std::map<CString, SInt32> varMap;

	typedef std::vector<std::pair<CString, bool> > TExternalSymbols;

	TExternalSymbols externalSymbols;

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
					CString::Ptr string = i->mObjArg1.upcast<CString>();
					SInt32 argIndex = findVarInArgs(arguments, *string);

					Bool symbolFound = true;

					if (argIndex == 0)
					{
						std::map<CString, SInt32>::iterator it = varMap.find(*string);
						if (it == varMap.end())
						{
							if (finalStage)
							{
								argIndex = symbolFromSymbolTable(externalSymbols, *string, true);
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
					CString::Ptr string = i->mObjArg1.upcast<CString>();
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

					i->mSInt32Arg1 = argIndex;
				}
				break;

				case eInstructionGetProperty:
				case eInstructionSetProperty:
				{
					CString::Ptr string = i->mObjArg1.upcast<CString>();
					i->mUInt32Arg1 = symbolFromSymbolTable(externalSymbols, *string, false);
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

	for (TExternalSymbols::reverse_iterator it = externalSymbols.rbegin(); it != externalSymbols.rend(); ++it)
	{
		CSokriptInstruction::Ptr newInstruction = new CSokriptInstruction(eInstructionDeclareExternalSymbol, new CString(it->first));
		if (!it->second)
		{
			newInstruction->mInstruction = eInstructionDeclareSymbol;
		}
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
			case eInstructionSetProperty:
			case eInstructionGetProperty:
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

			case eInstructionDeclareExternalSymbol:
			case eInstructionDeclareSymbol:
				{
					CString::Ptr string = i->mObjArg1.upcast<CString>();
					stream.write(string->UTF8String(), string->length() + 1);
				}
				break;

			case eInstructionPushStr:
				{
					CString::Ptr string = i->mObjArg1.upcast<CString>();
					UInt32 size = string->length() + 1;
					stream.write((const char*)&size, sizeof(size));
					stream.write(string->UTF8String(), size);
				}
				break;

			case eInstructionPushFloat:
				{
					Float32 value = i->mObjArg1.upcast<CNumber>()->valueAsFloat32();
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
	s << i << ": " << nameFromCode(mInstruction);

	switch (mInstruction)
	{
		case eInstructionAssign:
		case eInstructionPushVar:
		case eInstructionSetProperty:
		case eInstructionGetProperty:
			if (mProcessed)
				s << ": \"" << mSInt32Arg1 << "\"";
			else
				s << ": \"" << mObjArg1->description() << "\"";
			break;

		case eInstructionDeclareExternalSymbol:
		case eInstructionDeclareSymbol:
		case eInstructionPushStr:
			s << ": \"" << mObjArg1->description() << "\"";
			break;

		case eInstructionPushFloat:
			s << ": \"" << mObjArg1.upcast<CNumber>()->valueAsFloat32() << "\"";
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
