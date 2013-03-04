#if !defined SL_LE_core_slCRandomGenerator_h
#define SL_LE_core_slCRandomGenerator_h

#include "slCObject.h"

namespace sokira
{
	namespace le
	{

class CRandomGenerator : public CObject
{
	public:
		CRandomGenerator();

		void setSeed(UInt32 seed);
		void generateSeed();
		UInt32 seed() const;

		UInt32 nextUInt32();
		UInt32 nextUInt32(UInt32 startRange, UInt32 endRange);
		Float64 nextFloat64(); // from 0.0 to 1.0

	private:
		UInt32 mSeed;
		UInt32 mNext;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCRandomGenerator_h
