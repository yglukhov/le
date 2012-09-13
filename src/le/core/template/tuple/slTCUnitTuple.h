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
		typedef TTypeList TypeList;

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

		template <class TContext>
		struct TSTuple :
			public _TSTupleUnit<TContext::I, TUnit<typename TContext::T> >,
			public TContext::Next
		{ };

		typename TTypeList::template Enumerate<TSTuple, _SNullType, _SNullType> mTuple;
};


	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_template_tuple_slTCUnitTuple_h
