#include "slCSimpleRefCountable.h"

namespace sokira
{
	namespace le
	{


CSimpleRefCountable::CSimpleRefCountable() :
	mRefCount(1)
{

}

CSimpleRefCountable::~CSimpleRefCountable()
{

}

void CSimpleRefCountable::retain() const
{
	++mRefCount;
}

void CSimpleRefCountable::release() const
{
	--mRefCount;
	if (!mRefCount)
	{
		delete this;
	}
}

	} // namespace le
} // namespace sokira
