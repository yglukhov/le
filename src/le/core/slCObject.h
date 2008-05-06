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
	LE_RTTI_END

	public:
		CObject();
		virtual ~CObject();

		CString description() const;
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
};

	} // namespace le
} // namespace sokira

#endif // !defined _slCObject_h_included_
