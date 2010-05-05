#include <fstream>
#include "slCPreferences.h"
#include "slCWorkspace.h"

namespace sokira
{
	namespace le
	{

static inline const char* preferencesFilePath()
{
	return CWorkspace().userPreferencesURL().path().cString();
}

CPreferences::CPreferences() :
	CDictionary("preferences")
{
//	NSAutoreleasePool * pool = [NSAutoreleasePool new];
//	NSArray * libraries = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
//	NSLog(@"%@", libraries);
//	NSString * str = [libraries objectAtIndex:0];
//	NChar* cStr = new NChar[[str length]];
//	[str getCString:cStr maxLength: [str length] encoding: NSASCIIStringEncoding];
//	[pool release];
//	CString path = CString::__CStringNoCopyDeallocWithDelete(cStr);

	std::ifstream stream(preferencesFilePath());
	append(CDictionary::createFromStream(stream));
}

void CPreferences::flush() const
{
	std::ofstream stream(preferencesFilePath());
	dump(stream);
}

	} // namespace le
} // namespace sokira
