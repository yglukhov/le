#include "slAssert.h"
#include "slCLogControl.h"

////////////////////////////////////////////////////////////////////////////////
// ASSERT
////////////////////////////////////////////////////////////////////////////////
#if LE_FLAG_DEBUG

#include <le/core/slCObject.h>

namespace sokira
{
	namespace le
	{


void _le_assert(bool expression, const char* strExression, unsigned line, const char* file, const CObject* object, const char* message)
{
	std::ostream* log = CLogControl::instance()->currentEntry();

	if (!log)
	{
		std::cout << "Warning! Assertion failed, when CLogEntry is not available!\n Redirecting to stdout...\n";
		log = &std::cout;
	}

	if(!expression)
	{
		*log << "ASSERTION FAILED: " << std::endl;
		*log << "\tEXPRESSION: " << strExression  << std::endl;
		*log << "\tFILE: " << file << std::endl;
		*log << "\tLINE: " << line << std::endl;

		if(object)
			*log << "\tOBJECT: " << object->objectClass().name() << " <" << object << ">" << std::endl;

		if(message)
			*log << "\tMESSAGE: " << message << std::endl;
	}
}

	} // namespace le
} // namespace sokira

#endif // LE_FLAG_DEBUG

