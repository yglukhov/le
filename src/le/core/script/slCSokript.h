#if !defined SL_LE_core_script_slCSokript_h
#define SL_LE_core_script_slCSokript_h

#include "slCScript.h"

namespace sokira
{
	namespace le
	{

class CSokriptImpl;

class CSokript : public CScript
{
	public:
		CSokript();
		~CSokript();

		virtual void runFromStream(std::istream& stream);

	private:
		CSokriptImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_script_slCSokript_h
