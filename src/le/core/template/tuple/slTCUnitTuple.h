#if !defined SL_LE_core_template_tuple_slTCUnitTuple_h
#define SL_LE_core_template_tuple_slTCUnitTuple_h

#include <le/core/template/typelist/slTSTypeList.h>

namespace sokira
{
	namespace le
	{

template <class TTypeList, template <typename> class TUnit>
class TCUnitTuple
{
	public:
		template <unsigned int index>
		inline TUnit<typename TTypeList::template TypeAt<index>::result>& unit()
		{
			typedef TUnit<typename TTypeList::template TypeAt<index>::result> Unit;
			return static_cast<Unit&>(static_cast<_TSTupleUnit<index, Unit>&>(mTuple));
		}

		template <unsigned int index>
		inline const TUnit<typename TTypeList::template TypeAt<index>::result>& unit() const
		{
			typedef TUnit<typename TTypeList::template TypeAt<index>::result> Unit;
			return static_cast<const Unit&>(static_cast<const _TSTupleUnit<index, Unit>&>(mTuple));
		}

	private:
		template <unsigned i, class T>
		struct _TSTupleUnit : public T
		{ };

		template <class TList, template <typename> class TUnit, unsigned i = 0>
		struct TSTuple :
			public _TSTupleUnit<i, TUnit<typename TList::Front> >,
			public TSTuple<typename TList::PopFront, TUnit, i+1>
		{ };

		template <template <typename> class TUnit, unsigned i>
		struct TSTuple <TSTypeList<>, TUnit, i>
		{ };

		TSTuple<TTypeList, TUnit> mTuple;
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_tuple_slTCUnitTuple_h
