#if !defined H_included_slCLogControl
#define H_included_slCLogControl

#include <streambuf>
#include <list>

#include <le/core/slCString.h>
#include <le/core/thread/slTCThreadSingletone.h>

namespace sokira
{
	namespace le
	{

class CLogEntry;

class CLogControl :
	public std::streambuf,
	public TCThreadSingletone<CLogControl>
{
	public:
		CLogControl();
		~CLogControl();

		void attachToFile(const CString& name, UInt32 minPriority);
		void attachToScreen(UInt32 minPriority);

		void currentEntry(CLogEntry* entry);
		CLogEntry* currentEntry() const;

		void attachToStream(std::ostream* theStream, UInt32 severity);

		void increaseWhiteSpace()
		{
			mWhiteSpace += '\t';
		}

		void decreaseWhiteSpace()
		{
			mWhiteSpace.erase(0, 1);
		}

	protected:

		virtual int sync();
		virtual int overflow(int c = EOF);

	private:
		CLogEntry* mCurrentEntry;
		std::list<std::pair<UInt32, std::ostream*> > mStreams;
		std::string mWhiteSpace;
		std::string mBuffer;
};

	} // namespace le
} // namespace sokira

#endif // not defined H_included_slCLogControl
