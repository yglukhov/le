#if !defined SL_LE_core_slCObject_h
#define SL_LE_core_slCObject_h

#include <le/core/slCClass.h>
#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/template/function/slTCVariadicFunction.h>
#include <le/core/base/slCBasicAny.h>

namespace sokira
{
	namespace le
	{

class CDictionary;
class CString;
class CSelectorInvocation :
	public TCMonoTypeVariadicFunctionMixin<CSelectorInvocation, CBasicAny, CBasicReferenceAny>
{
	public:
		template <class TList>
		struct TResult
		{
			typedef CBasicAny result;
		};

		CSelectorInvocation(CObject* obj, ISelector* sel) :
			mObject(obj),
			mSelector(sel)
		{

		}

		using TCMonoTypeVariadicFunctionMixin<CSelectorInvocation, CBasicAny, CBasicReferenceAny>::operator();

		template <class TypeList>
		CBasicAny operator()(const TCTuple<TypeList>& arguments)
		{
			std::template vector<CBasicReferenceAny> v;
			v.reserve(TypeList::length);
			TSTupleToContainerCollector<TypeList>::fillContainerWithTupleValues(v, arguments);
			return this->operator()(v);
		}

		CBasicAny operator()(const std::vector<CBasicReferenceAny>& arguments);

	private:
		CObject* mObject;
		ISelector* mSelector;
};

////////////////////////////////////////////////////////////////////////////////
// CObject
////////////////////////////////////////////////////////////////////////////////
class CObject : public CSimpleRefCountable
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CObject)
		LE_RTTI_SELECTOR(serialize)
		LE_RTTI_SELECTOR(deserialize)
	LE_RTTI_END

	public:
//		CObject();
//		virtual ~CObject();

		virtual CString description() const;
		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);

		CSelectorInvocation selector(const CString& name);
		Bool respondsToSelector(const CString& name) const;
//		CAny performSelector(const CString& name, TCArray<CAny>& arguments);
//		CAny performConstSelector(const CString& name, TCArray<CAny>& arguments) const;
//		static CAny performStaticSelector(const CString& name, TCArray<CAny>& arguments);
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCObject_h
