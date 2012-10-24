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
	if (mPushBackChar)
	{
		WChar res = mPushBackChar;
		mPushBackChar = 0;
		return res;
	}

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

void CXMLParser::setOnStartTag(const TOnStartTag& onStartTag)
{
	mOnStartTag = onStartTag;
}

void CXMLParser::setOnEndTag(const TOnEndTag& onEndTag)
{
	mOnEndTag = onEndTag;
}

void CXMLParser::setOnData(const TOnData& onData)
{
	mOnData = onData;
}

void CXMLParser::setOnError(const TOnError& onError)
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
		if (trimsWhitespace()) data.trimWhitespace();
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
		eStateInTag = LE_SET_BIT(0),
		eStateInStartTag = LE_SET_BIT(1),
		eStateInEndTag = LE_SET_BIT(2),
		eStateInTagName = LE_SET_BIT(3),
		eStateInAttrName = LE_SET_BIT(4),
		eStateInAttrValue = LE_SET_BIT(5)
	};

	UInt32 state = 0;

	mLine = 1;
	mColumn = 0;
	mPushBackChar = 0;

	CString str; // Here we store tag name or data
	CString attrName;
	CString attrValue;
	TArrtibutes attrs;

	while (!isEOF())
	{
		WChar c = nextChar();

		if (!state)
		{
			if (c == L'<')
			{
				onData(str);
				str.clear();
				state = eStateInTag;
			}
			else
				str.append(c);
		}
		else if (state & eStateInTagName)
		{
			if (CString::isWhitespace(c) || c == L'>' || c == L'/')
			{
				state &= ~eStateInTagName;
				mPushBackChar = c;
			}
			else
				str.append(c);
		}
		else if (state & eStateInAttrName)
		{
			if (CString::isWhitespace(c) || c == L'=' || c == L'>')
			{
				state &= ~eStateInAttrName;
				mPushBackChar = c;
			}
			else
				attrName.append(c);
		}
		else if (state & eStateInAttrValue)
		{
			bool charIsSpecial = CString::isWhitespace(c) || (c == L'>');
			if (c == '"' && attrValue.hasPrefix("\""))
			{
				attrValue.erase(0, 1);
				state &= ~eStateInAttrValue;
				attrs[attrName] = attrValue;
				attrName.clear();
				attrValue.clear();
			}
			else if (charIsSpecial && !attrValue.hasPrefix("\""))
			{
				state &= ~eStateInAttrValue;
				attrs[attrName] = attrValue;
				attrName.clear();
				attrValue.clear();
			}
			else
				attrValue.append(c);
		}
		else if (state & eStateInStartTag)
		{
			if (c == L'>')
			{
				if (!attrName.isEmpty())
				{
					attrs[attrName] = CString();
					attrName.clear();
				}

				onStartTag(str, attrs);
				str.clear();
				attrs.clear();
				state &= ~(eStateInStartTag | eStateInTag);
			}
			else if (c == L'=')
			{
				if (attrName.isEmpty())
				{
					onError("unexpected token \"=\"");
				}
				else
				{
					state |= eStateInAttrValue;
				}
			}
			else if (c == L'/')
			{
				onStartTag(str, attrs);
				attrs.clear();
				state &= ~eStateInStartTag;
				state |= eStateInEndTag;
			}
			else if (!CString::isWhitespace(c))
			{
				if (!attrName.isEmpty())
				{
					attrs[attrName] = CString();
					attrName.clear();
				}

				attrName.append(c);
				state |= eStateInAttrName;
			}
		}
		else if (state & eStateInEndTag)
		{
			if (c == L'>')
			{
				onEndTag(str);
				str.clear();
				state &= ~(eStateInTag | eStateInEndTag);
			}
		}
		else if (state & eStateInTag)
		{
			if (c == L'/')
			{
				if (str.isEmpty())
				{
					state |= eStateInEndTag | eStateInTagName;
				}
				else
					onError("unexpected token \"/\"");
			}
			else if (!CString::isWhitespace(c))
			{
				state |= eStateInStartTag | eStateInTagName;
				str.append(c);
			}
		}
	}
	return true;
}

	} // namespace le
} // namespace sokira
