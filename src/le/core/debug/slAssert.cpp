#include "slAssert.h"
#include "slCAssertControl.h"
#include "slCAssertionPolicy.h"

////////////////////////////////////////////////////////////////////////////////
// ASSERT
////////////////////////////////////////////////////////////////////////////////

namespace sokira
{
	namespace le
	{


void _le_assert(bool expression, const char* strExression, unsigned line, const char* file, const CObject* object, const char* message)
{
	if(!expression)
	{
		CAssertControl::instance()->assertionPolicy()->performAssert(strExression, line, file, object, message);
	}
}

	} // namespace le
} // namespace sokira
