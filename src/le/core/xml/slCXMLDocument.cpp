#include <fstream>
#include <le/core/slCURL.h>
#include <le/core/template/function/slTCBind.h>
#include "slCXMLDocument.h"
#include "slCXMLNode.h"

namespace sokira
{
	namespace le
	{

CXMLDocument::CXMLDocument(const CURL& url) :
	mRootNode(NULL),
	mCurrentNode(NULL)
{
	std::ifstream stream(url.path().cString());
	if (stream)
	{
		CXMLParser parser;
		parser.setTrimsWhitespace();
		CXMLParser::TOnStartTag onStart = bind(&CXMLDocument::onStartTag, this, bindTo(0), bindTo(1), bindTo(2));
		parser.setOnStartTag(onStart);
		CXMLParser::TOnEndTag onEnd = bind(&CXMLDocument::onEndTag, this, bindTo(0), bindTo(1));
		parser.setOnEndTag(onEnd);
		CXMLParser::TOnEndTag onError = bind(&CXMLDocument::onError, this, bindTo(0), bindTo(1));
		parser.setOnError(onError);
		CXMLParser::TOnData onData = bind(&CXMLDocument::onData, this, bindTo(0), bindTo(1));
		parser.setOnData(onData);
		parser.parseStream(stream);
	}
}

CXMLDocument::~CXMLDocument()
{
	delete mRootNode;
}

CXMLNode* CXMLDocument::rootNode()
{
	return mRootNode;
}

void CXMLDocument::onStartTag(CXMLParser* parser, CString name, CXMLParser::TArrtibutes attributes)
{
	CXMLNode* newNode = new CXMLNode(name, attributes, mCurrentNode);
	if (mCurrentNode)
	{
		mCurrentNode->addChild(newNode);
	}
	else
	{
		mRootNode = newNode;
	}
	mCurrentNode = newNode;
}

void CXMLDocument::onEndTag(CXMLParser*, CString tagName)
{
	CXMLNode* oldNode = mCurrentNode->parent();
	if (oldNode)
		mCurrentNode = oldNode;
}

void CXMLDocument::onData(CXMLParser* parser, CString data)
{

}

void CXMLDocument::onError(CXMLParser* parser, CString error)
{

}

void CXMLDocument::dump(std::ostream& stream)
{
	if (mRootNode)
		mRootNode->dump(stream);
	else
		stream << "(null)" << std::endl;
}


	} // namespace le
} // namespace sokira
