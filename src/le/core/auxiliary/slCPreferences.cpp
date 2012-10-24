#include <fstream>
#include "slCPreferences.h"
#include "slCWorkspace.h"

namespace sokira
{
	namespace le
	{

CPreferences::CPreferences(const CString& domain) :
	CDictionary("preferences"),
	mDomain(domain)
{
	std::ifstream stream(filePath());
	append(CDictionary::createFromStream(stream));
}

CPreferences::~CPreferences()
{
	flush();
}

void CPreferences::flush() const
{
	std::ofstream stream(filePath());
	dump(stream);
}

const NChar* CPreferences::filePath() const
{
	CURL url = CWorkspace().userPreferencesURL();
	url.appendPathComponent(mDomain);
	return url.path().UTF8String();
}

	} // namespace le
} // namespace sokira
