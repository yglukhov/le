#if !defined _slCObject_h_included_
#define _slCObject_h_included_

#include <le/core/slCClass.h>

namespace sokira
{
	namespace le
	{

class CDictionary;
class CString;

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
		virtual ~CObject();

		CString description() const;
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

//		CAny performSelector(const CString& name, TCArray<CAny>& arguments);
//		CAny performConstSelector(const CString& name, TCArray<CAny>& arguments) const;
//		static CAny performStaticSelector(const CString& name, TCArray<CAny>& arguments);
};

	} // namespace le
} // namespace sokira

#endif // !defined _slCObject_h_included_
