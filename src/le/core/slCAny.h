#if !defined SL_LE_core_slCAny_h
#define SL_LE_core_slCAny_h

#include "slCObject.h"
#include <le/core/base/slCBasicAny.h>

namespace sokira
{
	namespace le
	{

class CAny : public CObject, public CBasicAny
{
	LE_RTTI_BEGIN
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELF(CAny)
	LE_RTTI_END

	public:
		CAny() {}

		template <typename T>
		CAny(T value) :
			CBasicAny(value)
		{

		}
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCAny_h
