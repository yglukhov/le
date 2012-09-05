#pragma once

#include "slCBasicAny.h"

namespace sokira
{
	namespace le
	{

class ISelector
{
	public:
		ISelector(const char* name) :
			mName(name)
		{

		}

		virtual ~ISelector() {}

		inline const char* name() const
		{
			return mName;
		}

		virtual CBasicAny operator() (const std::vector<CBasicAny>& arguments) const = 0;

	private:
		const char* mName;
};

template <typename FuncType>
class TCSelector : public ISelector
{
	public:
		TCSelector(FuncType func, const char* name) :
			ISelector(name),
			mFunc(func)
		{

		}

		virtual CBasicAny operator() (const std::vector<CBasicAny>& arguments) const
		{
			return CBasicAny();
		}

	private:
		FuncType mFunc;
};

	} // namespace le
} // namespace sokira
