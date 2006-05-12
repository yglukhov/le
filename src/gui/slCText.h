#pragma once

#include <common/config/slPrefix.h>
#include <string>

LE_NAMESPACE_START

class CPoint;

class CText
{
	public:
		CText();
		CText(const std::string& string, unsigned format = 0);
		CText(const char* string, unsigned format = 0);

		void draw(const CPoint& position) const;
		void format(unsigned Format = 0);
		void text(const char* textString);

	private:
		std::string mString;
		unsigned mFormat;
};

LE_NAMESPACE_END
