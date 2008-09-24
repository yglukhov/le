#include <le/core/slCDictionary.h>
#include "slCXMLParser.h"

namespace sokira
{
	namespace le
	{

enum EOption
{
	eOptionTrimWhitespace = LE_SET_BIT(0)
};

CXMLParser::CXMLParser() :
	mFlags(0),
	mLine(0),
	mColumn(0)
{

}

Bool CXMLParser::parseStream(std::istream& stream)
{
	mStream = static_cast<void*>(&stream);
	mNextChar = &CXMLParser::nextNChar;
	mIsEOF = &CXMLParser::isNEOF;
	return parse();
}

Bool CXMLParser::parseStream(std::wistream& stream)
{
	mStream = static_cast<void*>(&stream);
	mNextChar = &CXMLParser::nextWChar;
	mIsEOF = &CXMLParser::isWEOF;
	return parse();
}

WChar CXMLParser::nextNChar()
{
	return static_cast<std::istream*>(mStream)->get();
}

WChar CXMLParser::nextWChar()
{
	return static_cast<std::wistream*>(mStream)->get();
}

Bool CXMLParser::isNEOF()
{
	return static_cast<std::istream*>(mStream)->eof();
}

Bool CXMLParser::isWEOF()
{
	return static_cast<std::wistream*>(mStream)->eof();
}

WChar CXMLParser::nextChar()
{
	WChar c = (this->*mNextChar)();
	if (c == '\n')
	{
		++mLine;
		mColumn = 1;
	}
	else ++mColumn;

	return c;
}

Bool CXMLParser::isEOF()
{
	return (this->*mIsEOF)();
}

void CXMLParser::setOnStartTag(TOnStartTag& onStartTag)
{
	mOnStartTag = onStartTag;
}

void CXMLParser::setOnEndTag(TOnEndTag& onEndTag)
{
	mOnEndTag = onEndTag;
}

void CXMLParser::setOnData(TOnData& onData)
{
	mOnData = onData;
}

void CXMLParser::setOnError(TOnError& onError)
{
	mOnError = onError;
}

void CXMLParser::setTrimsWhitespace(Bool trimWhitespace)
{
	if (trimWhitespace)
		mFlags |= eOptionTrimWhitespace;
	else
		mFlags &= ~eOptionTrimWhitespace;
}

Bool CXMLParser::trimsWhitespace() const
{
	return mFlags & eOptionTrimWhitespace;
}

UInt32 CXMLParser::line() const
{
	return mLine;
}

UInt32 CXMLParser::column() const
{
	return mColumn;
}

void CXMLParser::onStartTag(const CString& tagName, const TArrtibutes& attrs)
{
	if (mOnStartTag) mOnStartTag(this, tagName, attrs);
}

void CXMLParser::onEndTag(const CString& tagName)
{
	if (mOnEndTag) mOnEndTag(this, tagName);
}

void CXMLParser::onData(CString data)
{
	if (mOnData)
	{
		if (mFlags & eOptionTrimWhitespace) data.trimWhitespace();
		if (!data.isEmpty()) mOnData(this, data);
	}
}

void CXMLParser::onError(const CString& error)
{
	if (mOnError) mOnError(this, error);
}

Bool CXMLParser::parse()
{
	enum
	{
		eStateData = 0,
		eStateStartTagName = LE_SET_BIT(0),
		eStateEndTagName = LE_SET_BIT(1),
		eStateAttrName = LE_SET_BIT(2),
		eStateAttrValue = LE_SET_BIT(3)
	};

	UInt32 state = eStateData;

	mLine = 1;
	mColumn = 0;

	CString str; // Here we store tag name or data
	CString attrName;
	CString attrValue;
	TArrtibutes attrs;

	while (!isEOF())
	{
		WChar c = nextChar();

		if (c == '<')
		{
			if (state != eStateData) onError("unexpected token \"<\"");

			onData(str);
			str.clear();
			state = eStateStartTagName;
			continue;
		}
		else if (c == '>')
		{
			if (state & eStateStartTagName)
			{
				if (!attrName.isEmpty())
				{
					attrs[attrName] = attrValue;
					attrName.clear();
					attrValue.clear();
				}
				onStartTag(str, attrs);
				attrs.clear();
			}

			if (state & eStateEndTagName)
			{
				onEndTag(str);
			}

			str.clear();
			state = eStateData;
		}
		else if (c == '/')
		{
			if (state & eStateStartTagName)
			{
				if (str.isEmpty())
					state = eStateEndTagName;
				else
					state |= eStateEndTagName;
			}
			else
				str.append(c);
		}
		else if (state & (eStateEndTagName) && CString::isWhitespace(c))
		{
		//	if (!str.isEmpty()) str.append(c);
		}
		else if (state & (eStateStartTagName) && CString::isWhitespace(c))
		{
			if (!str.isEmpty())
				state |= eStateAttrName;
		}
		else if (state & eStateAttrName)
		{
			if (CString::isWhitespace(c))
			{
				attrs[attrName] = attrValue;
				attrName.clear();
			}
			else if (c == '=')
			{
				state &= ~eStateAttrName;
				state |= eStateAttrValue;
			}
			else
				attrName.append(c);
		}
		else if (state & eStateAttrValue)
		{
			if (CString::isWhitespace(c) || c == '\"')
			{
				if (!attrValue.isEmpty())
				{
					attrs[attrName] = attrValue;
					attrName.clear();
					attrValue.clear();
					state &= ~eStateAttrName;
					state |= eStateAttrValue;
				}
			}
			else
				attrValue.append(c);
		}
		else
			str.append(c);
	}
	return true;
}

	} // namespace le
} // namespace sokira
