#include <time.h>
#include "slCRandomGenerator.h"

namespace sokira
{
	namespace le
	{

CRandomGenerator::CRandomGenerator()
{
	generateSeed();
}

void CRandomGenerator::setSeed(UInt32 seed)
{
	mSeed = seed;
	mNext = seed;
}

void CRandomGenerator::generateSeed()
{
	setSeed(static_cast<UInt32>(time(NULL)));
}

UInt32 CRandomGenerator::seed() const
{
	return mSeed;
}

UInt32 CRandomGenerator::nextUInt32()
{
	return nextFloat64() * mNext;
}

UInt32 CRandomGenerator::nextUInt32(UInt32 startRange, UInt32 endRange)
{
	return startRange + (nextUInt32() % (endRange - startRange));
}

Float64 CRandomGenerator::nextFloat64()
{
	mNext = (mNext * 9301 + 49297) % 233280;
	return (Float64)mNext / 233280.0;
}

	} // namespace le
} // namespace sokira
