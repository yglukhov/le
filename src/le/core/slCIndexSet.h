#if !defined SL_LE_core_slCIndexSet_h
#define SL_LE_core_slCIndexSet_h

#include "slCString.h"

namespace sokira
{
	namespace le
	{

template <typename TLoc, typename TLen>
struct TSRange
{
	typedef TLoc TLocation;
	typedef TLen TLength;

	TLocation location;
	TLength length;

	TLocation end() const
	{
		return location + length;
	}
};

typedef TSRange<SInt32, UInt32> SRange;

template <typename TRange>
class TCIndexSet
{
	public:
		typedef typename TRange::TLocation TLocation;
		typedef typename TRange::TLength TLength;
		typedef std::vector<TRange> TRangeVector;
	
	
		TCIndexSet() { }

		TCIndexSet(const TRange& range)
		{
			addIndexesInRange(range);
		}

		TCIndexSet(TLocation index)
		{
			addIndex(index);
		}

		void addIndex(TLocation index)
		{
			TRange range;
			range.location = index;
			range.length = 1;
			addIndexesInRange(range);
		}

		TLocation end() const
		{
			return mRanges.size() ? mRanges.back().end() : 0;
		}

		void addIndexesInRange(const TRange& range)
		{
			if (range.location > end())
			{
				mRanges.push_back(range);
				return;
			}

			size_t i = 0;
			TLocation rangeEnd = range.end();
			for (; i < mRanges.size(); ++i)
			{
				if (rangeEnd < mRanges[i].location)
				{
					mRanges.insert(mRanges.begin() + i, range);
					return;
				}

				TLocation oldEnd = mRanges[i].end();
				if (range.location <= oldEnd)
				{
					if (range.location < mRanges[i].location)
					{
						mRanges[i].location = range.location;
					}

					if (oldEnd > rangeEnd) rangeEnd = oldEnd;
					mRanges[i].length = rangeEnd - mRanges[i].location;

					if (rangeEnd >= mRanges[i + 1].location)
					{
						// Find the closing range, and shrink the set
						size_t j = i + 1;
						for (; j < mRanges.size(); ++j)
						{
							oldEnd = mRanges[j].end();
							if (rangeEnd < oldEnd)
							{
								if (rangeEnd >= mRanges[j].location)
								{
									mRanges[i].length = oldEnd - mRanges[i].location;
								}
								break;
							}
						}

						++i;

						if (j < mRanges.size())
						{
							++j;
							mRanges.erase(mRanges.begin() + i, mRanges.begin() + j);
						}
					}
					return;
				}
			}
			LE_ASSERT(false);
		}

		void unionSet(const TCIndexSet& set)
		{
			for (typename TRangeVector::const_iterator it = set.indexRanges().begin(); it != set.indexRanges().end(); ++it)
			{
				addIndexesInRange(*it);
			}
		}

		Bool containsIndex(TLocation index) const
		{
			for (typename TRangeVector::const_iterator it = mRanges.begin(); it != mRanges.end(); ++it)
			{
				if (index >= it->location && index < it->end()) return true;
			}
			return false;
		}

		const TRangeVector& indexRanges() const
		{
			return mRanges;
		}

	private:
		TRangeVector mRanges;
};

class CIndexSet : public CObject, public TCIndexSet<SRange>
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CIndexSet)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CIndexSet() {}
		CIndexSet(const SRange& range) : TCIndexSet(range) {}
		CIndexSet(SRange::TLocation index) : TCIndexSet(index) {}
};

template <typename T>
std::ostream& operator << (std::ostream& stream, const TCIndexSet<T>& indexSet)
{
	typedef typename TCIndexSet<T>::TRangeVector TRangeVector;
	const TRangeVector& ranges = indexSet.indexRanges();
	stream << '[';
	Bool comma = false;
	for (typename TRangeVector::const_iterator it = ranges.begin(); it != ranges.end(); ++it)
	{
		if (comma)
		{
			stream << ", ";
		}
		else
		{
			comma = true;
		}
		stream << '{' << it->location << ", " << it->length << '}';
	}

	return stream << ']';
}
		
	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCIndexSet_h
