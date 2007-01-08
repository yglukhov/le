#pragma once

#include "slTypes.h"
#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{

class CTime : public CObject
{
	LE_DECLARE_RUNTIME_CLASS(CTime);

	public:
		CTime(); // init with current time
		CTime(UInt32 milliseconds);
		CTime(UInt32 seconds, UInt32 milliseconds);
		CTime(UInt32 minutes, UInt32 seconds, UInt32 milliseconds);
		CTime(UInt32 hours, UInt32 minutes, UInt32 seconds, UInt32 milliseconds);

		UInt32 milliseconds() const;
		UInt64 timeToMilliseconds() const;

		void milliseconds(UInt32 value);
		void timeWithMilliseconds(UInt64 value);

		UInt32 seconds() const;
		UInt32 timeToSeconds(bool roundToNearest = false) const;

		void seconds(UInt32 value);
		void timeWithSeconds(UInt32 value);

		UInt32 minutes() const;
		UInt32 timeToMinutes(bool roundToNearest = false) const;

		void minutes(UInt32 value);
		void timeWithMinutes(UInt32 value);

		UInt32 hours() const;
		UInt32 timeToHours(bool roundToNearest = false) const;

		void hours(UInt32 value);
		void timeWithHours(UInt32 value);

		void timeWithCurrentTime();

		const CTime& operator += (const CTime& rhs) { mData += rhs.mData; return *this; }

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

	private:
		UInt64 mData;
};

	} // namespace le
} // namespace sokira
