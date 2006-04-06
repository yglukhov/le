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
	_CLog log(__PRETTY_FUNCTION__, true);

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


////////////////////////////////////////////////////////////////////////////////
// LOG
////////////////////////////////////////////////////////////////////////////////
std::ostream* _CLog::sLogStream = NULL;
std::string _CLog::sWhiteSpace;

_CLog::_CLog(const std::string& func, bool quiet) : mFunc(func), mQuiet(quiet)
{
	if(!sLogStream)
	{
		CFile* file = CFile::createWithPath("log.txt");
		// TODO: remove this hack
		sLogStream = (file)?(static_cast<std::ostream*>(static_cast<void*>(file))):(&std::cout);
	}

	if(!mQuiet)
	{
		*sLogStream << sWhiteSpace << mFunc << '\n' << sWhiteSpace << '{' << std::endl;
		sWhiteSpace.push_back('\t');
	}
}

_CLog::~_CLog()
{
	if(!mQuiet)
	{
		sWhiteSpace.erase(0, 1);
		*sLogStream << sWhiteSpace << '}' << std::endl;
	}
}
