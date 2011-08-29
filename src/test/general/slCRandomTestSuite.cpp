#include "slCRandomTestSuite.h"
#include <le/core/slCRandomGenerator.h>

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CRandomTestSuite);

void CRandomTestSuite::testRandom()
{
	CRandomGenerator generator;

	UInt32 maxNumber = 1000;
	UInt32* hits = new UInt32[maxNumber];

	bzero(hits, sizeof(UInt32) * maxNumber);

	for (UInt32 i = 0; i < 100000000; ++i)
	{
		++hits[generator.nextUInt32(0, maxNumber)];
	}

	UInt32 minHits = 0;
	UInt32 maxHits = 0;
	UInt32 averageHits = 0;

	for (UInt32 i = 0; i < maxNumber; ++i)
	{
		if (minHits > hits[i])
		{
			minHits = hits[i];
		}

		if (maxHits < hits[i])
		{
			maxHits = hits[i];
		}
	}

	std::cout << "Min: " << minHits << std::endl;
	std::cout << "Max: " << maxHits << std::endl;

	delete [] hits;
}

	} // namespace le
} // namespace sokira
