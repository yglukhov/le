#pragma once

namespace sokira
{
	namespace le
	{

class ISelector
{

};

template <typename FuncType>
class TCSelector : public ISelector
{
	public:
		TCSelector(FuncType func, const char* name) :
			mFunc(func),
			mName(name)
		{

		}

	private:
		FuncType mFunc;
		const char* mName;
};

	} // namespace le
} // namespace sokira
