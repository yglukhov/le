#if !defined included_core_script_slCScript_h
#define included_core_script_slCScript_h

#include <le/core/slCData.h>

namespace sokira
{
	namespace le
	{

typedef CObject::Ptr (*TScriptFunction)(CObject::Ptr);

class CScript : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CScript)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		virtual bool compileStream(std::istream& stream, std::ostream& ostream);
		virtual CObject::Ptr runBytecode(const CData& data);
		
		virtual CObject::Ptr runScript(const CString& script);
		virtual CObject::Ptr runStream(std::istream& stream);

		virtual void addExternalObject(const CString& name, CObject::Ptr object);
		virtual void addExternalFunction(const CString& name, TScriptFunction function);
};

	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCScript_h
