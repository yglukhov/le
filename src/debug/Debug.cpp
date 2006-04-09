#include "Debug.h"

#include "CFile.h"

////////////////////////////////////////////////////////////////////////////////
// ASSERT
////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG

#include "CObject.h"
#include "IClass.h"

void _assert(bool expression, const char* strExression, unsigned line, const char* file, const CObject* object, const char* message)
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

#endif // DEBUG

