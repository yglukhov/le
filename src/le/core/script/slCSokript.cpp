#include "slCSokript.h"
#include "base/slCSokriptImpl.hp"

//#include "base/slCSokriptFlexLexer.hp" // This will also include parser declaration

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

void CSokript::runFromStream(std::istream& stream)
{
	mImpl->runFromStream(stream);
}

	} // namespace le
} // namespace sokira
