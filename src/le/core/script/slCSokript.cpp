#include "slCSokript.h"
#include "base/slCSokriptImpl.hp"

namespace sokira
{
	namespace le
	{

CSokriptOld::CSokriptOld() :
	mImpl(new CSokriptImpl())
{

}

CSokriptOld::~CSokriptOld()
{
	delete mImpl;
}

void CSokriptOld::addFunction(const CString& name, CObject* (*function)(CObject*))
{
	mImpl->addFunction(name, function);
}

void CSokriptOld::runBytecode(const CData& bytecode)
{
	mImpl->runBytecode(bytecode);
}

void CSokriptOld::compileFromStream(std::istream& input, std::ostream& output)
{
	mImpl->compileFromStream(input, output);
}

	} // namespace le
} // namespace sokira
