#include "slAssert.h"

////////////////////////////////////////////////////////////////////////////////
// ASSERT
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

#include <common/slCObject.h>

LE_NAMESPACE_START


void _le_assert(bool expression, const char* strExression, unsigned line, const char* file, const CObject* object, const char* message)
{
	std::ostream& log = CLogEntry::defaultStream();

	if(!expression)
	{
		log << "ASSERTION FAILED: " << std::endl;
		log << "\tEXPRESSION: " << strExression  << std::endl;
		log << "\tFILE: " << file << std::endl;
		log << "\tLINE: " << line << std::endl;

		if(object)
			log << "\tOBJECT: " << object->objectClass()->name() << " <" << object << ">" << std::endl;

		if(message)
			log << "\tMESSAGE: " << message << std::endl;
	}
}

LE_NAMESPACE_END

#endif // DEBUG

