#include "slCTime.h"

#define MILLISECONDS_IN_SECOND 100
#define SECONDS_IN_MINUTE 60
#define MILLISECONDS_IN_MINUTE (MILLISECONDS_IN_SECOND * SECONDS_IN_MINUTE)
#define MINUTES_IN_HOUR 60
#define MILLISECONDS_IN_HOUR (MINUTES_IN_HOUR * MILLISECONDS_IN_MINUTE)

LE_NAMESPACE_START

IMPLEMENT_RUNTIME_CLASS(CTime);

CTime::CTime() : mData(0)
{
	// TODO: complete this
}

CTime::CTime(UInt32 milliseconds) : mData(milliseconds)
{

}

CTime::CTime(UInt32 seconds, UInt32 milliseconds) :
	mData(	seconds * MILLISECONDS_IN_SECOND +
			milliseconds)
{

}

CTime::CTime(UInt32 minutes, UInt32 seconds, UInt32 milliseconds) :
	mData(	minutes * MILLISECONDS_IN_MINUTE +
			seconds * MILLISECONDS_IN_SECOND +
			milliseconds)
{

}
	
CTime::CTime(UInt32 hours, UInt32 minutes, UInt32 seconds, UInt32 milliseconds) :
	mData(	hours * MILLISECONDS_IN_HOUR +
			minutes * MILLISECONDS_IN_MINUTE +
			seconds * MILLISECONDS_IN_SECOND +
			milliseconds)
{

}

UInt32 CTime::milliseconds() const
{
	return (mData)?(mData%100):(0);
}

UInt64 CTime::timeToMilliseconds() const
{
	return mData;
}

void CTime::milliseconds(UInt32 value)
{
	mData -= (milliseconds() - value);
}

void CTime::timeWithMilliseconds(UInt64 value)
{
	mData = value;
}

UInt32 CTime::seconds() const
{
	// TODO: complete this
	throw 0;
	return 0;
}

UInt32 CTime::timeToSeconds(bool roundToNearest) const
{
	// TODO: complete this
	throw 0;
	return 0;
}

void CTime::seconds(UInt32 value)
{
	// TODO: complete this
	throw 0;
}

void CTime::timeWithSeconds(UInt32 value)
{
	mData = value * MILLISECONDS_IN_SECOND;
}

UInt32 CTime::minutes() const
{
	// TODO: complete this
	throw 0;
	return 0;
}

UInt32 CTime::timeToMinutes(bool roundToNearest) const
{
	// TODO: complete this
	throw 0;
	return 0;
}

void CTime::minutes(UInt32 value)
{
	// TODO: complete this
	throw 0;
}

void CTime::timeWithMinutes(UInt32 value)
{
	mData = value * MILLISECONDS_IN_MINUTE;
}


UInt32 CTime::hours() const
{
	// TODO: complete this
	throw 0;
	return 0;
}

UInt32 CTime::timeToHours(bool roundToNearest) const
{
	// TODO: complete this
	throw 0;
	return 0;
}

void CTime::hours(UInt32 value)
{
	// TODO: complete this
	throw 0;
}

void CTime::timeWithHours(UInt32 value)
{
	mData = value * MILLISECONDS_IN_HOUR;
}

void CTime::timeWithCurrentTime()
{
	// TODO: complete this
	throw 0;
}

LE_NAMESPACE_END
