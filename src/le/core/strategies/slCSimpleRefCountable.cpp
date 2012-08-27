#include <le/core/debug/slAssert.h>
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
	LE_ASSERT(mRefCount <= 1);
}

void CSimpleRefCountable::retain() const
{
	++mRefCount;
}

void CSimpleRefCountable::release() const
{
	LE_ASSERT(mRefCount >= 1);
	--mRefCount;
	if (!mRefCount)
	{
		delete this;
	}
}

	} // namespace le
} // namespace sokira
