#pragma once

#include "base/slTSTuple.h"

LE_NAMESPACE_START

template <class TTypeList, template <typename> class TUnit>
class TCUnitTuple
{
	TSTuple<TTypeList, TUnit> mTuple;

	public:
		template <unsigned int index>
		inline TUnit<typename TTypeList::template TypeAt<index>::result>& unit()
		{
			typedef typename TTypeList::template TypeAt<index>::result UnitType; 
			return static_cast<TUnit<UnitType>&>(static_cast<_TSTupleUnit<index, TUnit<UnitType> >&>(mTuple));
		//	return static_cast<TUnit<typename TTypeList::template TypeAt<index>::result, index>&>(mTuple);
		}

		template <unsigned int index>
		inline const TUnit<typename TTypeList::template TypeAt<index>::result>& unit() const
		{
			typedef typename TTypeList::template TypeAt<index>::result UnitType; 
			return static_cast<const TUnit<UnitType>&>(static_cast<const _TSTupleUnit<index, TUnit<UnitType> >&>(mTuple));
		//	return static_cast<const TUnit<typename TTypeList::template TypeAt<index>::result, index>&>(mTuple);
		}
};


LE_NAMESPACE_END
