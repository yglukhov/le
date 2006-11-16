#pragma once

#include <common/slCObject.h>

LE_NAMESPACE_START

class CData : public CObject
{
	DECLARE_RUNTIME_CLASS(CData);

	typedef UInt32 DataLength;

	public:
		CData();
		CData(const void* data, DataLength length);
		CData(const CData& data);
		~CData();

		DataLength length() const;
		void crop(DataLength toLength);

		const void* data() const;
		void data(const void* newData, DataLength length);
		const CData& operator = (const CData& newData);

	private:
		void* mData;
};

LE_NAMESPACE_END
