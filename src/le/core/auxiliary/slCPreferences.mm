#include "slCPreferences.h"

#include <Cocoa/Cocoa.h>

namespace sokira
{
	namespace le
	{


// static CDictionary 


CPreferences::CPreferences()
{
	NSAutoreleasePool * pool = [NSAutoreleasePool new];
	NSArray * libraries = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
	NSLog(@"%@", libraries);
	NSString * str = [libraries objectAtIndex:0];
	NChar* cStr = new NChar[[str length]];
	[str getCString:cStr maxLength: [str length] encoding: NSASCIIStringEncoding];
	[pool release];
	CString path = CString::__CStringNoCopyDeallocWithDelete(cStr);
}

static inline CFNumberRef createCFTypeWithValue(SInt64 value)
{
	return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt64Type, &value);
}

//static inline CFNumberRef createCFTypeWithValue(SInt32 value)
//{
//	return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &value);
//}
//
//static inline CFNumberRef createCFTypeWithValue(SInt16 value)
//{
//	return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt16Type, &value);
//}
//
//static inline CFNumberRef createCFTypeWithValue(SInt8 value)
//{
//	return CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt8Type, &value);
//}

static inline CFStringRef createCFTypeWithValue(const CString& value)
{
	return CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, value.cString(), kCFStringEncodingASCII, kCFAllocatorNull);
}

template <typename T>
static void _setValueForKey(const CString& key, const T& value)
{
	CFStringRef cfKey = createCFTypeWithValue(key);
	CFShow(CFSTR("key: "));
	CFShow(cfKey);
	if (cfKey)
	{
		CFTypeRef cfType = createCFTypeWithValue(value);
		if (cfType)
		{
			CFPreferencesSetAppValue(cfKey, cfType, kCFPreferencesCurrentApplication);
			CFPreferencesAppSynchronize(kCFPreferencesCurrentApplication);
			CFRelease(cfType);
		}
		CFRelease(cfKey);
	}
}

void CPreferences::setValueForKey(const CString& key, SInt64 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, SInt32 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, SInt16 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, SInt8 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, UInt64 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, UInt32 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, UInt16 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, UInt8 value) { _setValueForKey(key, value); }
void CPreferences::setValueForKey(const CString& key, const CString& value) { _setValueForKey(key, value); }


template <typename T>
static inline CFTypeID typeIdForValue();

template <>
static inline CFTypeID typeIdForValue<SInt64>()
{
	return CFNumberGetTypeID();
}

template <>
static inline CFTypeID typeIdForValue<CString>()
{
	return CFStringGetTypeID();
}

template <typename T>
static inline T getCFValue(CFTypeRef value);

template <>
static inline SInt64 getCFValue<SInt64>(CFTypeRef value)
{
	SInt64 result;
	CFNumberGetValue((CFNumberRef)value, kCFNumberSInt32Type, &result);
	return result;
}

template <>
static inline CString getCFValue<CString>(CFTypeRef value)
{
	CFIndex length = CFStringGetLength((CFStringRef)value);
	NChar* str = new NChar[length + 1];
	CFStringGetCString((CFStringRef)value, str, length + 1, kCFStringEncodingASCII);
	return CString::__CStringNoCopyDeallocWithDelete(str);
}

template <typename T>
static T _valueForKey(const CString& key, const T& defaultValue)
{
	CFStringRef cfKey = createCFTypeWithValue(key);
	T result = defaultValue;
	if (cfKey)
	{
		CFTypeRef value = CFPreferencesCopyAppValue(cfKey, kCFPreferencesCurrentApplication);
		if (value)
		{
			if (CFGetTypeID(value) == typeIdForValue<T>())
			{
				result = getCFValue<T>(value);
			}
			CFRelease(value);
		}

		CFRelease(cfKey);
	}
	return result;
}

SInt64 CPreferences::valueForKey(const CString& key, SInt64 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
SInt32 CPreferences::valueForKey(const CString& key, SInt32 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
SInt16 CPreferences::valueForKey(const CString& key, SInt16 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
SInt8 CPreferences::valueForKey(const CString& key, SInt8 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
UInt64 CPreferences::valueForKey(const CString& key, UInt64 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
UInt32 CPreferences::valueForKey(const CString& key, UInt32 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
UInt16 CPreferences::valueForKey(const CString& key, UInt16 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
UInt8 CPreferences::valueForKey(const CString& key, UInt8 defaultValue) const { return _valueForKey<SInt64>(key, defaultValue); }
CString CPreferences::valueForKey(const CString& key, const CString& defaultValue) const { return _valueForKey<CString>(key, defaultValue); }

	} // namespace le
} // namespace sokira
