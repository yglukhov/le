#pragma once

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CData : public CObject
{
	LE_DECLARE_RUNTIME_CLASS(CData);

	typedef UInt32 DataLength;

	public:
		enum ECompressionMethod
		{
			eCompressionMethodNone = 0,
			eCompressionMethodZip,
			eCompressionMethodRar
			// ...
		};

		CData();
		CData(const void* data, DataLength length);
		CData(const CData& data);
		~CData();

		DataLength length() const;
		void crop(DataLength toLength);

		const void* data() const;
		void setData(const void* newData, DataLength length);
		const CData& operator = (const CData& newData);

		CData compressedData(ECompressionMethod method) const;
		CData decompressedData() const;

		ECompressionMethod compressionMethod() const;
		void compress(ECompressionMethod method);
		void decompress();

	private:
		void* mData;
};

	} // namespace le
} // namespace sokira
