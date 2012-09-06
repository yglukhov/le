#pragma once

#include <le/core/template/tuple/slTCTuple.h>
#include <le/core/template/function/slTSFunctionTraits.h>
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
		virtual UInt32 argumentsCount() const = 0;

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
			//TCTuple<typename TSFunctionTraits<FuncType>::ParamList> t;
			return CBasicAny();
		}

		virtual UInt32 argumentsCount() const
		{
			return TSFunctionTraits<FuncType>::ParamList::length;
		}

	private:
		FuncType mFunc;
};

	} // namespace le
} // namespace sokira
