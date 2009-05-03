#include "slCSokript.h"
#include "base/slCSokriptImpl.hp"

namespace sokira
{
	namespace le
	{

CSokript::CSokript() :
	mImpl(new CSokriptImpl())
{

}

CSokript::~CSokript()
{
	delete mImpl;
}

void CSokript::addFunction(const CString& name, CObject* (*function)(CObject*))
{
	mImpl->addFunction(name, function);
}

void CSokript::runBytecode(const CData& bytecode)
{
	mImpl->runBytecode(bytecode);
}

void CSokript::compileFromStream(std::istream& input, std::ostream& output)
{
	mImpl->compileFromStream(input, output);
}

	} // namespace le
} // namespace sokira
