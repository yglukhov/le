//
//  slCStopWatch.cpp
//  le
//
//  Created by Yuriy Glukhov on 8/28/12.
//
//

#include "slCStopWatch.h"

namespace sokira
{
	namespace le
	{

CStopWatch::CStopWatch() :
	mMilliseconds(0)
{

}

void CStopWatch::reset()
{
	mMilliseconds = 0;
}

void CStopWatch::start()
{
	mStartTime.setCurrentTime();
}

void CStopWatch::pause()
{
	mMilliseconds += CTime() - mStartTime;
}

UInt64 CStopWatch::milliseconds() const
{
	return mMilliseconds;
}

	} // namespace le
} // namespace sokira
