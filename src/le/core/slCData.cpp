#include <le/core/debug/slDebug.h>
#include "slCData.h"


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CData);


CData::CData() :
	mData(NULL)
{

}

CData::CData(const void* theData, DataLength length) :
	mData(NULL)
{
	setData(theData, length);
}

CData::CData(const CData& theData) :
	mData(NULL)
{
	setData(theData.mData, theData.length());
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

void CData::setData(const void* newData, DataLength length)
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
	setData(newData.mData, newData.length());
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
// Compression routines
// TODO: complete
CData CData::compressedData(ECompressionMethod method) const
{
	return *this;
}

CData CData::decompressedData() const
{
	return *this;
}

CData::ECompressionMethod CData::compressionMethod() const
{
	return eCompressionMethodNone;
}

void CData::compress(ECompressionMethod method)
{

}

void CData::decompress()
{

}

	} // namespace le
} // namespace sokira
