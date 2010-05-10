#pragma once

#include "base/slTSTuple.h"

namespace sokira
{
	namespace le
	{

template <class TTypeList, template <typename> class TUnit>
class TCUnitTuple
{
	TSTuple<TTypeList, TUnit> mTuple;

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
};


	} // namespace le
} // namespace sokira
