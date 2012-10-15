#include <time.h>
#include "slCRandomGenerator.h"

namespace sokira
{
	namespace le
	{

static inline UInt64 randomWithSeed(UInt64 seed, UInt32& position)
{
	union SeedUnion
	{
		struct
		{
			UInt16 s0;
			UInt16 s1;
			UInt16 s2;
			UInt16 s3;
		};
	};
	++position;
	SeedUnion *s = (SeedUnion *)&seed;

	return (UInt64)(2111111111UL - position) * (UInt64)(s->s3 + position) +
		(UInt64)(1492 + position) * (UInt64)(s->s2 - position) +
		(UInt64)1776 * (UInt64)(s->s1 + position) +
		(UInt64)(5115 - position) * (UInt64)(s->s0 + position) +
		(UInt64)(s->s3 - position) * position;
}

CRandomGenerator::CRandomGenerator() :
	mPosition(0)
{
	generateSeed();
}

void CRandomGenerator::setSeed(UInt64 seed)
{
	mSeed = seed;
}

void CRandomGenerator::generateSeed()
{
	union
	{
		struct
		{
			UInt8 b0;
			UInt8 b1;
			UInt8 b2;
			UInt8 b3;
			UInt8 b4;
			UInt8 b5;
			UInt8 b6;
			UInt8 b7;
		};
		UInt32 u32;
		UInt64 u64;
	} seed, t, p;

	t.u32 = static_cast<UInt32>(time(NULL));
//	p.u32 = static_cast<UInt32>(this);
	seed.b0 = t.b3;
	seed.b1 = p.b1;
	seed.b2 = t.b2;
	seed.b3 = p.b3;
	seed.b4 = t.b1;
	seed.b5 = p.b2;
	seed.b6 = t.b0;
	seed.b7 = p.b0;

	seed.u64 *= p.b0 * t.b0;

	std::cout << "b0: " << (int)seed.b0 << std::endl;
	std::cout << "b1: " << (int)seed.b1 << std::endl;
	std::cout << "b2: " << (int)seed.b2 << std::endl;
	std::cout << "b3: " << (int)seed.b3 << std::endl;
	std::cout << "b4: " << (int)seed.b4 << std::endl;
	std::cout << "b5: " << (int)seed.b5 << std::endl;
	std::cout << "b6: " << (int)seed.b6 << std::endl;
	std::cout << "b7: " << (int)seed.b7 << std::endl;

	setSeed(seed.u64);
}

UInt64 CRandomGenerator::seed() const
{
	return mSeed;
}

UInt32 CRandomGenerator::position() const
{
	return mPosition;
}

void CRandomGenerator::setPosition(UInt32 position)
{
	mPosition = position;
}

UInt32 CRandomGenerator::nextUInt32()
{
	return (UInt32)randomWithSeed(mSeed, mPosition);
}

UInt32 CRandomGenerator::nextUInt32(UInt32 startRange, UInt32 endRange)
{
	return startRange + (nextUInt32() % (endRange - startRange));
}

Float64 CRandomGenerator::nextFloat64()
{
	return ((Float64)randomWithSeed(mSeed, mPosition) / (65536.*65536.) / 10);
}

	} // namespace le
} // namespace sokira
