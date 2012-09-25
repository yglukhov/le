#if !defined SL_LE_core_strategies_slCSimpleRefCountable_h
#define SL_LE_core_strategies_slCSimpleRefCountable_h

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

class CSimpleRefCountable
{
	public:
		CSimpleRefCountable();
		CSimpleRefCountable(const CSimpleRefCountable& copy);
		virtual ~CSimpleRefCountable();

		void retain() const;
		void release() const;

		CSimpleRefCountable& operator=(const CSimpleRefCountable& rhs)
		{
			// Never copy mRefCount
			return *this;
		}

	private:
		mutable UInt32 mRefCount;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_strategies_slCSimpleRefCountable_h
