#include <iostream>
#include "slCLexer.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CLexer);

CLexer::CLexer()
{

}

CLexer::~CLexer()
{
	std::map<CString, ITokenMatcher*>::iterator end = mTokenMatches.end();
	for (std::map<CString, ITokenMatcher*>::iterator it = mTokenMatches.begin();
		 it != end; ++it)
	{
		it->second->release();
	}
}

WChar CLexer::nextChar()
{
	char result;
	if (mBuffer.length())
	{
		WChar t = mBuffer[0];
		result = t;
		mBuffer.erase(mBuffer.begin());
	}
	else
	{
		mStream->read(&result, 1);
	}
	return result;
}

CToken CLexer::nextToken()
{
	CToken result;
	do
	{
		result = nextTokenIncludingIgnored();
	} while (result.mMatcher && mIgnoredItems.find(result.identifier()) != mIgnoredItems.end());

//	std::cout << "Return: " << result.identifier() << std::endl;
	return result;
}

CToken CLexer::nextTokenIncludingIgnored()
{
	std::map<CString, ITokenMatcher*>::iterator end = mTokenMatches.end();
	for (std::map<CString, ITokenMatcher*>::iterator it = mTokenMatches.begin();
		 it != end; ++it)
	{
		it->second->reset();
	}

	std::map<CString, ITokenMatcher*> allMatchers = mTokenMatches;
	std::set<ITokenMatcher*> matchedMatchers;

	std::wstring buffer;

	while (!eof())
	{
		WChar c = nextChar();
		
		if (mStream->fail() && mStream->eof())
		{
			break;
		}

		buffer.push_back(c);
		Bool unmatchedMatchersExist = false;
		for (std::map<CString, ITokenMatcher*>::iterator it = allMatchers.begin(); it != allMatchers.end(); ++it)
		{
			ITokenMatcher* matcher = it->second;
			if (matcher)
			{
				ETokenMatchResult res = matcher->match(c);
				Bool removeMatcher = false;
				if (res == eTokenMatchResultInvalid)
				{
					removeMatcher = true;
				}
				else if (res == eTokenMatchResultComplete)
				{
					matchedMatchers.insert(matcher);
					removeMatcher = true;
				}
				else if (res == eTokenMatchResultEnough)
				{
					matchedMatchers.insert(matcher);
				}

				if (removeMatcher)
				{
					it->second = NULL;
				}
				else
				{
					unmatchedMatchersExist = true;
				}
			}
		}

		if (!unmatchedMatchersExist)
		{
			break;
		}
	}

	if (eof() && !buffer.empty())
	{
		for (std::map<CString, ITokenMatcher*>::iterator it = allMatchers.begin(); it != allMatchers.end(); ++it)
		{
			matchedMatchers.insert(it->second);
		}

		matchedMatchers.erase(NULL);
	}

	if (!matchedMatchers.empty())
	{
		ITokenMatcher* bestMatch = *(matchedMatchers.begin());
		UInt32 bestLength = bestMatch->token().length();
		std::set<ITokenMatcher*>::iterator end = matchedMatchers.end();
		for (std::set<ITokenMatcher*>::iterator it = matchedMatchers.begin(); it != end; ++it)
		{
			UInt32 len = (*it)->token().length();
			if (len > bestLength || (len == bestLength && (*it)->priority() > bestMatch->priority()))
			{
				bestLength = len;
				bestMatch = *it;
			}
		}

		LE_ASSERT(bestMatch);
		mBuffer.insert(mBuffer.begin(), buffer.begin() + bestLength, buffer.end());

//		std::cout << "return: " << bestMatch->identifier() << std::endl;
		return CToken(bestMatch, 0, 0);
	}

//	std::cout << "return NULL\n";

	return CToken(NULL, 0, 0);
}

bool CLexer::eof()
{
	return mBuffer.empty() && mStream->eof();
}

void CLexer::addMatcher(ITokenMatcher* pMatcher, const CString& identifer)
{
	pMatcher->retain();
	pMatcher->setIdentifier(identifer);
	mTokenMatches[identifer] = pMatcher;
}

void CLexer::addIgnoredIdentifier(const CString& identifier)
{
	mIgnoredItems.insert(identifier);
}

	} // namespace le
} // namespace sokira
