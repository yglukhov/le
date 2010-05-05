#if !defined SL_LE_core_auxiliary_slCWorkspace_h
#define SL_LE_core_auxiliary_slCWorkspace_h

namespace sokira
{
	namespace le
	{

class CURL;

class CWorkspace
{
	public:
		CURL userPreferencesURL() const;
		CURL userHomeURL() const;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCWorkspace_h
