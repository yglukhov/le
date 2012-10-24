#include <le/core/io/slCDataStream.h>
#include <le/core/slCString.h>
#include "slCScript.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CScript);

bool CScript::compileStream(std::istream& stream, std::ostream& ostream)
{
	return false;
}

CObject::Ptr CScript::runBytecode(const CData& data)
{
	return NULL;
}

CObject::Ptr CScript::runScript(const CString& script)
{
	CInputDataStream stream(script.UTF8String(), script.length());
	return runStream(stream);
}

CObject::Ptr CScript::runStream(std::istream& stream)
{
	CDataStream compiledDataStream;
	if (!compileStream(stream, compiledDataStream))
	{
		return NULL;
	}

	CData bytecode(compiledDataStream.c_data(), compiledDataStream.size());
	return runBytecode(bytecode);
}

void CScript::addExternalObject(const CString& name, CObject::Ptr object)
{

}

void CScript::addExternalSelector(ISelector* selector)
{

}

	} // namespace le
} // namespace sokira
