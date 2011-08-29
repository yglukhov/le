#pragma once

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

		inline const char* name() const
		{
			return mName;
		}

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

	private:
		FuncType mFunc;
};

	} // namespace le
} // namespace sokira
