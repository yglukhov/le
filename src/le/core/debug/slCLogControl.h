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
		void attachToStandardOutput(UInt32 minPriority);

		void setCurrentEntry(CLogEntry* entry);
		CLogEntry* currentEntry() const;

		void attachToStream(std::ostream* theStream, UInt32 severity, bool deleteOnEnd = true);

		void increaseWhiteSpace()
		{
			mWhiteSpace += '\t';
		}

		void decreaseWhiteSpace()
		{
			mWhiteSpace.erase(0, 1);
		}

	public:
		Bool mRespectEntries;


	protected:

		virtual int sync();
		virtual int overflow(int c = EOF);

		
	private:
		CLogEntry* mCurrentEntry;
//	std::list<std::pair<UInt32, std::ostream*> > mStreams;
		typedef TCTuple<TSTypeList<UInt32, std::ostream*, bool> > CStreamTuple;
		std::list<CStreamTuple> mStreams;
		std::string mWhiteSpace;
		std::string mBuffer;
};

	} // namespace le
} // namespace sokira

#endif // not defined H_included_slCLogControl
