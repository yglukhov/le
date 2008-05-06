////////////////////////////////////////////////////////////////////////////////
// S.O.K.I.R.A. labs - some_project
//
// Copyright:
//      Here goes the copyright text. This text can be very long and be more
//  than one line. In that case it is indented for one tab only, while the first
//  line of it is indented for two lines.
//
// Title: slCData.h
// Type: header
// Location: le/core
// Description:
//      This is the description text, which has to be formatted just like
//  copyright text.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{
////////////////////////////////////////////////////////////////////////////////
// Class: CData
// Intended to represent binary data and its compression.
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
