#if !defined SL_LE_sound_slCSoundContext_h
#define SL_LE_sound_slCSoundContext_h


namespace sokira
{
	namespace le
	{

class CSource;

class CSoundContext
{
	public:
		CSoundContext();
		CSource createSource();
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_sound_slCSource_h
