#if !defined SL_LE_core_auxiliary_slCCommandLine_h
#define SL_LE_core_auxiliary_slCCommandLine_h

#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

class CCommandLine
{
	public:
		CCommandLine();
		CCommandLine(int argc, const char * const argv[]);

		void setArguments(int argc, const char * const argv[]);

		UInt32 argumentCount() const;
		CString argumentAtIndex(UInt32 index) const;
		CString executableName() const; // Same as argumentAtIndex(0)

		const char * const * argv() const;

	private:
		UInt32 mCount;
		const char * const * mArgs;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_auxiliary_slCCommandLine_h
