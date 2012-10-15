#if !defined SL_LE_core_script_slCSokript_h
#define SL_LE_core_script_slCSokript_h

#include "slCScript.h"

namespace sokira
{
	namespace le
	{


class CSokript : public CScript
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CSokript)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CSokript();
		virtual bool compileStream(std::istream& stream, std::ostream& ostream);
		virtual CObject::Ptr runBytecode(const CData& data);

		virtual void addExternalObject(const CString& name, CObject::Ptr object);
		virtual void addExternalFunction(const CString& name, TScriptFunction function);

	private:
		std::map<CString, CObject::Ptr> mExternalObjects;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_script_slCSokript_h
