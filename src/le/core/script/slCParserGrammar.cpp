//
//  slCParserGrammar.cpp
//  le
//
//  Created by Yuriy Glukhov on 10/1/12.
//
//

#include <le/core/slCNumber.h>
#include <le/core/template/function/slTCBind.h>
#include "slCParserGrammar.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CParserGrammar);

CParserGrammar::CParserGrammar() :
	mFinalized(false)
{

}

CParserGrammar::~CParserGrammar()
{
	for (std::vector<SRule*>::const_iterator it = mRules.begin(); it != mRules.end(); ++it)
	{
		delete *it;
	}

	for (std::map<CString, ITokenMatcher*>::const_iterator it = mTokens.begin(); it != mTokens.end(); ++it)
	{
		it->second->release();
	}
}

void CParserGrammar::addRule(const CString& identifier, const std::vector<CString>& subIdentifiers, TRuleHandler handler)
{
	mFinalized = false;
	SRule* rule = new SRule;
	rule->identifier = identifier;
	rule->subIdentifiers = subIdentifiers;
	rule->handler = handler;
	mRules.push_back(rule);
}

void CParserGrammar::addTerminal(const CString& identifier, ITokenMatcher* matcher, TRuleHandler handler)
{
	matcher->retain();
	mTokens.insert(std::make_pair(identifier, matcher));
}

void CParserGrammar::setAssociativity(const CString& identifier, EAssociativity associativity)
{
	mAssociativities[terminalForIdentifier(identifier)] = associativity;
}

void CParserGrammar::setPrecedence(const CString& identifier, SInt precedence)
{
	mPrecedences[terminalForIdentifier(identifier)] = precedence;
}

CString CParserGrammar::terminalForIdentifier(const CString& identifier) const
{
	SRule* foundRule = NULL;
	CString result;
	for (std::vector<SRule*>::const_iterator it = mRules.begin(); it != mRules.end(); ++it)
	{
		SRule* rule = *it;
		if (rule->identifier == identifier)
		{
			LE_ASSERT(!foundRule);
			LE_ASSERT(rule->subIdentifiers.size() == 1);
			foundRule = rule;
			result = rule->subIdentifiers[0];
		}
	}
	
	if (result.isEmpty())
	{
		result = identifier;
	}
	return result;
}

CParserGrammar::CGrammarReader CParserGrammar::operator [] (const CString& identifier)
{
	return CGrammarReader(this, identifier);
}

void CParserGrammar::finalize() const
{
	if (!mFinalized)
	{
		mFinalized = true;

		mTerminals.clear();
		mNonTerminals.clear();

		for (std::map<CString, ITokenMatcher*>::const_iterator it = mTokens.begin(); it != mTokens.end(); ++it)
		{
			mTerminals.insert(it->first);
		}

		for (std::vector<SRule*>::const_iterator it = mRules.begin(); it != mRules.end(); ++it)
		{
			SRule* iRule = *it;

			if (mTerminals.find(iRule->identifier) == mTerminals.end())
			{
				mNonTerminals.insert(iRule->identifier);
			}

			for (std::vector<CString>::const_iterator jIt = iRule->subIdentifiers.begin(); jIt != iRule->subIdentifiers.end(); ++jIt)
			{
				if (mTerminals.find(*jIt) == mTerminals.end())
				{
					if (mNonTerminals.find(*jIt) == mNonTerminals.end())
					{
						if (ruleWithIdentifierExists(*jIt))
						{
							mNonTerminals.insert(*jIt);
						}
						else
						{
							mTerminals.insert(*jIt);
						}
					}
				}
			}
		}
	}
}

bool CParserGrammar::isTerminal(const CString& identifier) const
{
	finalize();
	return mTerminals.find(identifier) != mTerminals.end();
}

bool CParserGrammar::isNonTerminal(const CString& identifier) const
{
	finalize();
	return mNonTerminals.find(identifier) != mNonTerminals.end();
}

CParserGrammar::EAssociativity CParserGrammar::associativityForTerminal(const CString& identifier) const
{
	std::map<CString, EAssociativity>::const_iterator it = mAssociativities.find(identifier);
	if (it == mAssociativities.end())
	{
		return eAssociativityUndefined;
	}
	return it->second;
}

SInt CParserGrammar::precedenceForTerminal(const CString& identifier) const
{
	std::map<CString, SInt>::const_iterator it = mPrecedences.find(identifier);
	if (it == mPrecedences.end())
	{
		return 0;
	}
	return it->second;
}

ITokenMatcher* CParserGrammar::matcherForTerminal(const CString& identifier) const
{
	std::map<CString, ITokenMatcher*>::const_iterator it = mTokens.find(identifier);
	if (it == mTokens.end())
	{
		return NULL;
	}
	return it->second;
}

bool CParserGrammar::ruleWithIdentifierExists(const CString& identifier) const
{
	for (std::vector<SRule*>::const_iterator it = mRules.begin(); it != mRules.end(); ++it)
	{
		if ((*it)->identifier == identifier) return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////////////
// CParserGrammarReader

CParserGrammar::CGrammarReader::CGrammarReader(CParserGrammar* grammar, const CString& identifier) :
	mParser(grammar),
	mIdentifier(identifier)
{

}

CParserGrammar::CGrammarReader::~CGrammarReader()
{
	flush();
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator >> (const CString& obj)
{
	flush();
	mSubIdentifiers.push_back(obj);
	return *this;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator >> (char c)
{
	CString str; str.append(c);
	return *this >> str;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator >> (TCPointer<ITokenMatcher> matcher)
{
	CString str = uniqueIdentifierForMatcher(matcher.get());
	mParser->addTerminal(str, matcher.get(), TRuleHandler());
	return *this >> str;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (const CString& obj)
{
	mSubIdentifiers.push_back(obj);
	return *this;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (const TRuleHandler& obj)
{
	LE_ASSERT(!mHandler);
	mHandler = obj;
	return *this;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (const char* obj)
{
	return *this << CString(obj);
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (char c)
{
	CString str; str.append(c);
	return *this << str;
}

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (TCPointer<ITokenMatcher> matcher)
{
	CString str = uniqueIdentifierForMatcher(matcher.get());
	mParser->addTerminal(str, matcher.get(), TRuleHandler());
	return *this << str;
}

struct TSPassFunc
{
	CObject::Ptr operator() (std::vector<CObject::Ptr>& objects) { return objects.at(mIndex); }
	int mIndex;
};

CParserGrammar::CGrammarReader& CParserGrammar::CGrammarReader::operator << (int pass)
{
	TSPassFunc handler;
	handler.mIndex = pass;
	return *this << handler;
}

void CParserGrammar::CGrammarReader::flush()
{
	if (!mSubIdentifiers.empty())
	{
		if (mIdentifier == "%left" || mIdentifier == "%right" || mIdentifier == "%none")
		{
			SInt precedence = 0;
			for (std::map<CString, SInt>::const_iterator it = mParser->mPrecedences.begin(); it != mParser->mPrecedences.end(); ++it)
			{
				if (it->second > precedence)
				{
					precedence = it->second;
				}
			}

			++precedence;
			EAssociativity assoc = eAssociativityNone;
			if (mIdentifier == "%left")
			{
				assoc = eAssociativityLeft;
			}
			else if (mIdentifier == "%right")
			{
				assoc = eAssociativityRight;
			}

			for (std::vector<CString>::const_iterator it = mSubIdentifiers.begin(); it != mSubIdentifiers.end(); ++it)
			{
				mParser->setAssociativity(*it, assoc);
				mParser->setPrecedence(*it, precedence);
			}
		}
		else
		{
			if (mSubIdentifiers.size() == 1 && mSubIdentifiers[0].isEmpty())
			{
				mSubIdentifiers.clear(); // Empty production
			}
			mParser->addRule(mIdentifier, mSubIdentifiers, mHandler);
		}
		mSubIdentifiers.clear();
		mHandler = TRuleHandler();
	}
}

CString CParserGrammar::CGrammarReader::uniqueIdentifierForMatcher(ITokenMatcher* matcher) const
{
	UInt32 maxId = 0;
	for (std::map<CString, ITokenMatcher*>::const_iterator it = mParser->mTokens.begin(); it != mParser->mTokens.end(); ++it)
	{
		CString identifier = it->first;
		if (identifier.hasPrefix("%%"))
		{
			UInt32 idNum = CNumber(identifier.subString(2, 0)).valueAsUInt32();
			if (idNum > maxId)
			{
				maxId = idNum;
			}
		}
	}

	++maxId;
	return LESTR("%%") + CNumber(maxId).valueAsString();
}


	} // namespace le
} // namespace sokira
