#pragma once

#include <le/core/config/slPrefix.h>

namespace sokira
{
	namespace le
	{

class CNonCopyable
{
	protected:
		CNonCopyable() {}
	private:
		CNonCopyable(const CNonCopyable&) {}
		const CNonCopyable& operator = (const CNonCopyable&) { return *this; }
};

	} // namespace le
} // namespace sokira
