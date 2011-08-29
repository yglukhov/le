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

		void setSeed(UInt64 seed);
		void generateSeed();
		UInt64 seed() const;

		UInt32 position() const;
		void setPosition(UInt32 position);

		UInt32 nextUInt32();
		UInt32 nextUInt32(UInt32 startRange, UInt32 endRange);
		Float64 nextFloat64(); // from 0.0 to 1.0

	private:
		UInt64 mSeed;
		UInt32 mPosition;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCRandomGenerator_h
