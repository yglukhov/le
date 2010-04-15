#include <le/core/io/slCDataStream.h>
#include "slCScript.h"

namespace sokira
{
	namespace le
	{

CScript::~CScript()
{

}

void CScript::addFunction(const CString& name, CObject* (*function)(CObject*))
{

}

void CScript::addClass(const CClass& theClass)
{

}

//	virtual void addInstance(const CString& name, instance);

void CScript::runFromStream(std::istream& stream)
{
	CDataStream data;
	compileFromStream(stream, data);
	runBytecode(CData(data.c_data(), data.size()));
}

void CScript::runBytecode(const CData& bytecode)
{

}

void CScript::compileFromStream(std::istream& input, std::ostream& output)
{

}

	} // namespace le
} // namespace sokira
