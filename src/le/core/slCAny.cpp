
#include "base/slTCAnyContainer.h"
#include "slCAny.h"

namespace sokira
{
	namespace le
	{

IAnyContainer::~IAnyContainer()
{

}

CAny::CAny() :
	mValue(NULL)
{
	std::cout << "default constructor\n";
}

CAny::CAny(const CAny& copy) :
	mValue(copy.mValue->copy())
{
	std::cout << "copy constructor\n";
}

CAny::~CAny()
{
	delete mValue;
}

CAny::CAny(IAnyContainer* container) :
	mValue(container)
{

}

const CAny& CAny::operator = (const CAny& copy)
{
	std::cout << "copy =\n";
	delete mValue;
	mValue = copy.mValue->copy();
	return *this;
}

	} // namespace le
} // namespace sokira
