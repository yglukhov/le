#include <common/debug/slDebug.h>
#include "slCData.h"


LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CData);


CData::CData() :
	mData(NULL)
{

}

CData::CData(const void* theData, DataLength length) :
	mData(NULL)
{
	data(theData, length);
}

CData::CData(const CData& theData) :
	mData(NULL)
{
	data(theData.mData, theData.length());
}

CData::~CData()
{
	if(mData)
	{
		free(mData);
	}
}

CData::DataLength CData::length() const
{
	return (mData)?(*(static_cast<DataLength*>(mData))):(0);
}

void CData::crop(DataLength toLength)
{
	if(toLength < length())
	{
		*(static_cast<DataLength*>(mData)) = toLength;
	}
}

const void* CData::data() const
{
	return static_cast<const void*>(static_cast<const DataLength*>(mData) + 1);
}

void CData::data(const void* newData, DataLength length)
{
	if(mData)
	{
		free(mData);
		mData = NULL;
	}

	if(newData)
	{
		mData = malloc(length + sizeof(DataLength));
		*(static_cast<DataLength*>(mData)) = length;
		memcpy(static_cast<void*>(static_cast<DataLength*>(mData) + 1), newData, length);
	}
}

const CData& CData::operator = (const CData& newData)
{
	data(newData.mData, newData.length());
	return *this;
}

LE_NAMESPACE_END
