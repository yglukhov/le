#pragma once

#include <le/core/config/slPrefix.h>

LE_NAMESPACE_START

class CNonCopyable
{
	protected:
		CNonCopyable() {}
	private:
		CNonCopyable(const CNonCopyable&) {}
		const CNonCopyable& operator = (const CNonCopyable&) { return *this; }
};

LE_NAMESPACE_END
