#include <iostream>
#include "slCTokenizer.h"

namespace sokira
{
	namespace le
	{

static bool allCharsIn(const char* string, const char* set)
{
	for (; *string; ++string)
	{
		if (!strchr(set, *string))
			return false;
	}

	return true;
}

static inline bool allCharsIn(const char* string, char ch1, char ch2)
{
	for (; *string; ++string)
	{
		if (*string < ch1 || *string > ch2)
			return false;
	}

	return true;
}

class CSpacePunctuationNumericMatch : public ITokenMatch
{
	public:
		virtual ETokenType match(const char* string) const
		{
			return allCharsIn(string, '0', '9')
					?
						eTokenTypeNumericLiteral
					:
					(
						allCharsIn(string, " \t\n")
						?
							eTokenTypeSpace
						:
						(
							allCharsIn(string, "+-/*'\\!@#$%^&(){}[]=?<>,.|~`;")
							?
								eTokenTypePunctuation
							:
								eTokenTypeUnknown
						)
					);
		}
};

class CIdentifierMatch : public ITokenMatch
{
	public:
		virtual ETokenType match(const char* string) const
		{
			if ((*string >= 'a' && *string <= 'z') ||
				(*string >= 'A' && *string <= 'Z'))
			{
				for (++string; *string; ++string)
				{
					if ((*string < 'a' || *string > 'z') &&
						(*string < 'A' || *string > 'Z') &&
						(*string < '0' || *string > '9'))
					{
						return eTokenTypeUnknown;
					}
				}

				return eTokenTypeIdentifier;
			}

			return eTokenTypeUnknown;
		}
};

CTokenizer::CTokenizer()
{
	mTokenMatches.push_back(new CSpacePunctuationNumericMatch());
	mTokenMatches.push_back(new CIdentifierMatch());
}

CTokenizer::~CTokenizer()
{
	std::vector<ITokenMatch*>::iterator end = mTokenMatches.end();
	for (std::vector<ITokenMatch*>::iterator it = mTokenMatches.begin();
		it != end; ++it)
	{
		delete *it;
	}
}

CToken CTokenizer::nextToken()
{
	CToken result(mBuffer);

	do
	{
		bool found = false;
		std::vector<ITokenMatch*>::iterator end = mTokenMatches.end();
		for (std::vector<ITokenMatch*>::iterator it = mTokenMatches.begin();
			it != end; ++it)
		{
			ETokenType res = (*it)->match(mBuffer.c_str());
			if (res != eTokenTypeUnknown)
			{
				result.token = mBuffer;
				result.type = res;
				found = true;
			}
		}

		if (!found)
		{
			break;
		}

		char ch;
		mStream->read(&ch, 1);
		if (eof())
		{
			break;
		}
		mBuffer += ch;

	} while (true);

	mBuffer.erase(0, result.token.size());
	return result;
}

bool CTokenizer::eof()
{
	return mStream->eof();
}

	} // namespace le
} // namespace sokira
