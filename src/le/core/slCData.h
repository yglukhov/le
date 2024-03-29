////////////////////////////////////////////////////////////////////////////////
// S.O.K.I.R.A. labs - le
//
// Copyright:
//      Here goes the copyright text. This text can be very long and be more
//  than one line. In that case it is indented for one tab only, while the first
//  line of it is indented for two lines.
//
//****c* core/CData [ Documentation in ROBODoc format ]
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CURL;

////////////////////////////////////////////////////////////////////////////////
// Class:
//		CData
//
// Description:
//		Intended to represent binary data and its compression.
class CData : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CData)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	// Type: DataLength
	// Scalar type to represent data length. Currently it is <UInt32>.
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

		static CData createWithContentsOfURL(const CURL& url);

		DataLength length() const;
		void crop(DataLength toLength);

		const void* data() const;
		void setData(const void* newData, DataLength length);
		const CData& operator = (const CData& newData);

		void append(const CData& data);
		void append(const void* data, DataLength length);

		CData compressedData(ECompressionMethod method) const;
		CData decompressedData() const;

		ECompressionMethod compressionMethod() const;
		void compress(ECompressionMethod method);
		void decompress();

		Bool operator == (const CData& rhs) const;
		Bool operator != (const CData& rhs) const { return !(*this == rhs); }

		void writeToURL(const CURL& url) const;
	private:
		void* mData;
};

	} // namespace le
} // namespace sokira

/*******/
