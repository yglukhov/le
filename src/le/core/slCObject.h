#if !defined SL_LE_core_slCObject_h
#define SL_LE_core_slCObject_h

#include <le/core/slCClass.h>

namespace sokira
{
	namespace le
	{

class CDictionary;
class CString;
class CSelectorInvocation;

////////////////////////////////////////////////////////////////////////////////
// CObject
////////////////////////////////////////////////////////////////////////////////
class CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CObject)
		LE_RTTI_SELECTOR(serialize)
		LE_RTTI_SELECTOR(deserialize)
	LE_RTTI_END

	public:
		CObject();
		virtual ~CObject();

		CString description() const;
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

		CSelectorInvocation selector(const CString& name);
//		CAny performSelector(const CString& name, TCArray<CAny>& arguments);
//		CAny performConstSelector(const CString& name, TCArray<CAny>& arguments) const;
//		static CAny performStaticSelector(const CString& name, TCArray<CAny>& arguments);

		// Memory manadgement
		void retain();
		void release();

	private:
		UInt32 mRefCount;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCObject_h
