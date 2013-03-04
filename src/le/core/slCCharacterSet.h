#if !defined SL_LE_core_slCCharacterSet_h
#define SL_LE_core_slCCharacterSet_h

#include "slCIndexSet.h"

namespace sokira
{
	namespace le
	{

class CCharacterSet : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CCharacterSet)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	typedef TSRange<WChar, UInt32> TRange;
	typedef TCIndexSet<TRange> TSet;

	public:
		CCharacterSet() {}

		CCharacterSet(const CString& string)
		{
			addCharactersFromString(string);
		}

		void addCharactersFromString(const CString& string)
		{
			UInt32 count = string.length();
			for (UInt32 i = 0; i < count; ++i)
			{
				addCharacter(string.characterAtIndex(i));
			}
		}

		void addCharacter(WChar firstChar)
		{
			mSet.addIndex(firstChar);
		}

		void addCharactersInRange(WChar firstChar, UInt32 rangeLength)
		{
			TRange range;
			range.location = firstChar;
			range.length = rangeLength;
			mSet.addIndexesInRange(range);
		}

		CString allCharacters() const
		{
			CString result;
			for (typename TSet::TRangeVector::const_iterator it = mSet.indexRanges().begin(); it != mSet.indexRanges().end(); ++it)
			{
				for (UInt32 i = 0; i < it->length; ++i)
				{
					result.append((WChar)(it->location + i));
				}
			}
			return result;
		}

	private:
		TSet mSet;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCCharacterSet_h
