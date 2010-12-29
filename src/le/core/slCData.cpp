#include <le/core/debug/slDebug.h>
#include <le/core/slCURL.h>
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
	if (mData)
	{
		free(mData);
	}
}

CData CData::createWithContentsOfURL(const CURL& url)
{
	CData result;
	FILE* file = fopen(url.path().cString(), "r");
	if (file)
	{
		UInt32 bufferSize = 1024;
		void* buffer = malloc(bufferSize);
		UInt32 readBytes;
		while (readBytes = fread(buffer, 1, bufferSize, file))
		{
			result.append(buffer, readBytes);
			if (readBytes < bufferSize)
			{
				break;
			}
		}
		free(buffer);
		fclose(file);
	}

	return result;
}
		
CData::DataLength CData::length() const
{
	return (mData)?(*(static_cast<DataLength*>(mData))):(0);
}

void CData::crop(DataLength toLength)
{
	if (toLength < length())
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
	if (mData)
	{
		free(mData);
		mData = NULL;
	}

	if (newData)
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

void CData::append(const CData& data)
{
	append(data.data(), data.length());
}

void CData::append(const void* data, DataLength len)
{
	DataLength curLength = length();
	DataLength newLength = curLength + len;
	void* newData = realloc(mData, newLength + sizeof(DataLength));
	if (newData)
	{
		mData = newData;
		memcpy((char*)mData + curLength + sizeof(DataLength), data, len);
		*(static_cast<DataLength*>(mData)) = newLength;
	}
	else if (mData)
	{
		std::cout << "ERROR CData out of memory!" << std::endl;
		free(mData);
		mData = NULL;
	}
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

void CData::writeToURL(const CURL& url) const
{
	FILE* file = fopen(url.path().cString(), "w");
	if (file)
	{
		fwrite(data(), 1, length(), file);
		fclose(file);
	}
}

	} // namespace le
} // namespace sokira
