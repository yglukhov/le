#if !defined included_core_script_slCTokenizer_h
#define included_core_script_slCTokenizer_h

#include <iosfwd>
#include <string>
#include <vector>
#include <set>

#include <le/core/strategies/slCSimpleRefCountable.h>
#include <le/core/slTCPointer.h>
#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

typedef std::set<char> CCharSet;

enum ETokenMatchResult
{
	eTokenMatchResultInvalid = 0,
	eTokenMatchResultIncomplete,
	eTokenMatchResultEnough,
	eTokenMatchResultComplete
};

class ITokenMatcher : public CSimpleRefCountable
{
	public:
		virtual ETokenMatchResult match(WChar c) = 0;
		
		CString identifier() const
		{
			return mIdentifier;
		}

		void setIdentifier(const CString& identifier)
		{
			mIdentifier = identifier;
		}
	
		virtual CString token() const = 0;
		virtual void reset() = 0;
		virtual Float32 priority() const { return 1.0f; }
		virtual CObject::Ptr value() const { return new CString(token()); }

	private:
		CString mIdentifier;
};

class CConstStringTokenMatcher : public ITokenMatcher
{
	public:
	CConstStringTokenMatcher(const CString& token) :
		mToken(token)
	{

	};

	virtual ETokenMatchResult match(WChar c)
	{
		if (mToken.characterAtIndex(mIndex) == c)
		{
			++mIndex;
			if (mIndex == mToken.length())
			{
				return eTokenMatchResultComplete;
			}
			return eTokenMatchResultIncomplete;
		}
		return eTokenMatchResultInvalid;
	}

	virtual CString token() const
	{
		return mToken;
	}

	virtual void reset()
	{
		mIndex = 0;
	}

	virtual Float32 priority() const
	{
		return 2.0f;
	}
	
	private:
		CString mToken;
		UInt32 mIndex;
};

class CCharacterSetTokenMatcher : public ITokenMatcher
{
public:
	CCharacterSetTokenMatcher(const CString& charSet) :
		mCharSet(charSet)
	{

	};

	virtual ETokenMatchResult match(WChar c)
	{
		if (mCharSet.find(c) != -1)
		{
			mToken.append(c);
			return eTokenMatchResultEnough;
		}
		return eTokenMatchResultInvalid;
	}

	virtual CString token() const
	{
		return mToken;
	}

	virtual void reset()
	{
		mToken.clear();
	}

private:
	CString mToken;
	CString mCharSet;
};

class CIdentifierTokenMatcher : public ITokenMatcher
{
public:
	virtual ETokenMatchResult match(WChar c)
	{
		CString alpha = CString::createWithCharacterRange('a', 'z' - 'a' + 1);
		alpha += CString::createWithCharacterRange('A', 'Z' - 'A' + 1);
		alpha += "_";
		if (mToken.isEmpty())
		{
			if (alpha.find(c) == -1)
			{
				return eTokenMatchResultInvalid;
			}
			mToken.append(c);
			return eTokenMatchResultEnough;
		}
		
		CString numeric = CString::createWithCharacterRange('0', 10);
		if (numeric.find(c) != -1 || alpha.find(c) != -1)
		{
			mToken.append(c);
			return eTokenMatchResultEnough;
		}

		return eTokenMatchResultInvalid;
	}

	virtual CString token() const
	{
		return mToken;
	}

	virtual void reset()
	{
		mToken.clear();
	}

private:
	CString mToken;
};

class CStringLiteralTokenMatcher : public ITokenMatcher
{
public:

	virtual ETokenMatchResult match(WChar c)
	{
		if (mToken.isEmpty())
		{
			if (c == '\'' || c == '\"')
			{
				mToken.append(c);
				return eTokenMatchResultIncomplete;
			}
			return eTokenMatchResultInvalid;
		}

		mToken.append(c);
		if (c == '\'' || c == '\"')
		{
			if (mToken.characterAtIndex(0) == c && mToken.characterAtIndex(mToken.length() - 2) != '\\')
			{
				return eTokenMatchResultComplete;
			}
		}

		return eTokenMatchResultIncomplete;
	}

	virtual CString token() const
	{
		return mToken;
	}

	virtual void reset()
	{
		mToken.clear();
	}

private:
	CString mToken;
};



struct CToken
{
	CToken(const ITokenMatcher* matcher, UInt32 line, UInt32 column) :
		mMatcher(matcher), mLine(line), mColumn(column)
	{
		if (mMatcher)
		{
			mIdentifier = mMatcher->identifier();
			mValue = mMatcher->value();
		}
	}

	CToken() {}

	CString identifier() const
	{
		return mIdentifier;
	}

	CObject::Ptr value() const
	{
		return mValue;
	}

	const ITokenMatcher* mMatcher;
	UInt32 mLine;
	UInt32 mColumn;
	CString mIdentifier;
	CObject::Ptr mValue;
};

class CLexer : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CLexer)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CLexer();
		~CLexer();
		void setInputStream(std::istream* stream)
		{
			mStream = stream;
		}

		CToken nextToken();
		bool eof();

		UInt32 position() const
		{
			return 0;
		}
	
		void addMatcher(ITokenMatcher* matcher, const CString& identifier);
		void addIgnoredIdentifier(const CString& identifier);

	protected:
		std::map<CString, ITokenMatcher*> mTokenMatches;
		WChar nextChar();

	private:
		CToken nextTokenIncludingIgnored();
		std::istream* mStream;
		std::wstring mBuffer;
		std::set<CString> mIgnoredItems;
};

	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCTokenizer_h
