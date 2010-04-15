#if !defined SL_LE_sound_slCSource_h
#define SL_LE_sound_slCSource_h

#include <le/core/slCURL.h>

namespace sokira
{
	namespace le
	{

class CSourceImpl;

class CSource
{
	public:
		CSource();
		CSource(const CSource& source);
		~CSource();
		Bool loadFromURL(const CURL& url);
		void setPosition();
		void setVolume();
		void play();
		void pause();
		void stop();

		const CSource& operator = (const CSource& source);

	// private:
		CSource(CSourceImpl* impl);

	private:
		CSourceImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_sound_slCSource_h
