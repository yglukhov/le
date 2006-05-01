#pragma once

#include "base/slTSTuple.h"

LE_NAMESPACE_START

template <class TTypeList, template <typename, unsigned int> class TUnit>
class TCUnitTuple
{
	TSTuple<typename TTypeList::_headNode, TUnit> mTuple;

	public:
		template <unsigned int index>
		inline TUnit<typename TTypeList::template TypeAt<index>::result, index>& unit()
		{
			return static_cast<TUnit<typename TTypeList::template TypeAt<index>::result, index>&>(mTuple);
		}

		template <unsigned int index>
		inline const TUnit<typename TTypeList::template TypeAt<index>::result, index>& unit() const
		{
			return static_cast<const TUnit<typename TTypeList::template TypeAt<index>::result, index>&>(mTuple);
		}
};


LE_NAMESPACE_END
