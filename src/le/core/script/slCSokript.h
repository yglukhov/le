#if !defined SL_LE_core_script_slCSokript_h
#define SL_LE_core_script_slCSokript_h

#include "slCScript.h"

namespace sokira
{
	namespace le
	{

class CSokriptImpl;

class CSokriptOld : public CScript
{
	public:
		CSokriptOld();
		~CSokriptOld();

		virtual void addFunction(const CString& name, CObject* (*function)(CObject*));

		virtual void runBytecode(const CData& bytecode);
		virtual void compileFromStream(std::istream& input, std::ostream& output);

	private:
		CSokriptImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_script_slCSokript_h
