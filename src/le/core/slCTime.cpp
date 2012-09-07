#include "slCTime.h"
#include <le/core/slCDictionary.h>

#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
#include <sys/time.h>
#else
//#error Define time!
#include <windows.h>
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
#endif

#define MICROSECONDS_IN_MILLISECOND 1000
#define MILLISECONDS_IN_SECOND 1000
#define SECONDS_IN_MINUTE 60
#define MILLISECONDS_IN_MINUTE (MILLISECONDS_IN_SECOND * SECONDS_IN_MINUTE)
#define MINUTES_IN_HOUR 60
#define MILLISECONDS_IN_HOUR (MINUTES_IN_HOUR * MILLISECONDS_IN_MINUTE)

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTime);

static const CString cMillisecondsKey = LESTR("ms");
static const CString cSecondsKey = LESTR("s");
static const CString cMinutesKey = LESTR("m");
static const CString cHoursKey = LESTR("h");


CTime::CTime()
{
	setCurrentTime();
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
	return (mData)?(mData % MILLISECONDS_IN_SECOND):(0);
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
	UInt32 result = mData / MILLISECONDS_IN_SECOND;
	return (result)?(result % SECONDS_IN_MINUTE):(0);
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
	UInt32 result = mData / MILLISECONDS_IN_MINUTE;
	return (result)?(result % MINUTES_IN_HOUR):(0);
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
	return mData / MILLISECONDS_IN_HOUR;
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

void CTime::setCurrentTime()
{
#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
	timeval tp;
	gettimeofday(&tp, NULL);
	mData = tp.tv_sec * MILLISECONDS_IN_SECOND + tp.tv_usec / MICROSECONDS_IN_MILLISECOND;
#else
	// Define a structure to receive the current Windows filetime
	FILETIME ft;

	// Initialize the present time to 0 and the timezone to UTC
	unsigned __int64 tmpres = 0;
	//static int tzflag = 0;

	GetSystemTimeAsFileTime(&ft);
 
	// The GetSystemTimeAsFileTime returns the number of 100 nanosecond 
	// intervals since Jan 1, 1601 in a structure. Copy the high bits to 
	// the 64 bit tmpres, shift it left by 32 then or in the low 32 bits.
	tmpres |= ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;

	// Convert to microseconds by dividing by 10
	tmpres /= 10;

	// The Unix epoch starts on Jan 1 1970.  Need to subtract the difference 
	// in seconds from Jan 1 1601.
	tmpres -= DELTA_EPOCH_IN_MICROSECS;

	// Finally change microseconds to seconds and place in the seconds value. 
	// The modulus picks up the microseconds.
	mData =  (long)(tmpres / 1000000UL) * MILLISECONDS_IN_SECOND + (long)(tmpres % 1000000UL) / MICROSECONDS_IN_MILLISECOND;
#endif
}

void CTime::serialize(CDictionary& toDictionary) const
{
	toDictionary.setValueForKey(cMillisecondsKey, milliseconds());
	toDictionary.setValueForKey(cSecondsKey, seconds());
	toDictionary.setValueForKey(cMinutesKey, minutes());
	toDictionary.setValueForKey(cHoursKey, hours());
}

void CTime::deserialize(const CDictionary& fromDictionary)
{
	UInt32 ms = fromDictionary.valueAsUInt32ForKey(cMillisecondsKey);
	UInt32 s = fromDictionary.valueAsUInt32ForKey(cSecondsKey);
	UInt32 m = fromDictionary.valueAsUInt32ForKey(cMinutesKey);
	UInt32 h = fromDictionary.valueAsUInt32ForKey(cHoursKey);
	mData = h * MILLISECONDS_IN_HOUR +
			m * MILLISECONDS_IN_MINUTE +
			s * MILLISECONDS_IN_SECOND +
			ms;
}


	} // namespace le
} // namespace sokira
