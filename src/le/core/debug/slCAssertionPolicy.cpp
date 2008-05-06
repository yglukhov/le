#include <le/core/slCObject.h>

#include "slCAssertionPolicy.h"
#include "slCLogControl.h"

namespace sokira
{
	namespace le
	{

static void logAssert(const CString& expression, UInt lineNumber,
								const CString& fileName, const CObject *object,
								const CString& message)
{
	std::ostream* log = CLogControl::instance()->currentEntry();

	if (!log)
	{
		std::cout << "Warning! Assertion failed, when CLogEntry is not available!\n Redirecting to stdout...\n";
		log = &std::cout;
	}

	*log << "ASSERTION FAILED: " << std::endl;
	*log << "\tEXPRESSION: " << expression  << std::endl;
	*log << "\tFILE: " << fileName << std::endl;
	*log << "\tLINE: " << lineNumber << std::endl;

	if (object)
		*log << "\tOBJECT: " << object->objectClass().name() << " <" << object << ">" << std::endl;

	if (!message.isEmpty())
		*log << "\tMESSAGE: " << message << std::endl;
}

void CAssertionPolicy::performAssert(const CString& expression, UInt lineNumber,
								const CString& fileName, const CObject *object,
								const CString& message)
{
#if LE_FLAG_DEBUG
	std::cerr << "assertion \"" << expression << "\" failed: file \"" <<
		fileName << "\", line " << lineNumber << std::endl;
	logAssert(expression, lineNumber, fileName, object, message);
	abort();
#endif // LE_FLAG_DEBUG
}

void CUnitTestingAssertionPolicy::performAssert(const CString& expression,
				UInt lineNumber, const CString& fileName, const CObject *object,
				const CString& message)
{
	std::cerr << fileName << ":" << lineNumber << ": error: assertion \"" << expression << "\" failed";// << std::endl;
	if (!message.isEmpty())
		std::cerr << ": " << message;
	std::cerr << std::endl;
	logAssert(expression, lineNumber, fileName, object, message);
	exit(1);
}

	} // namespace le
} // namespace sokira
