#include "slCVariant.h"

LE_NAMESPACE_START

CVariant::CVariant() :
	mImpl(NULL)
{

}

CVariant::CVariant(const CVariant& copy) :
	mImpl(copy.mImpl->copy())
{

}

const CVariant& CVariant::operator = (const CVariant& copy)
{
	mImpl.reset(copy.mImpl->copy());
	return *this;
}

bool CVariant::operator == (const CVariant& rhs) const
{
	if (mImpl.get())
	{
		return mImpl->compare(rhs.mImpl.get());
	}

	if (rhs.mImpl.get())
	{
		return rhs.mImpl->compare(mImpl.get());
	}

	return true;
}

LE_NAMESPACE_END
