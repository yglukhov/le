#pragma once

#include "base/TSTuple.h"

template <class TTypeList, template <typename, unsigned int> class TUnit>
class TCUnitTuple
{
	TSTuple<typename TTypeList::list, TUnit> mTuple;

	public:
		template <unsigned int index>
		inline TUnit<typename TTypeList::TypeAt<index>::result, index>& unit()
		{
			return static_cast<TUnit<typename TTypeList::TypeAt<index>::result, index>&>(mTuple);
		}
};
