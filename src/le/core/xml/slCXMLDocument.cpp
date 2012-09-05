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
	initWithStream(stream);
}

CXMLDocument::CXMLDocument(std::istream& stream) :
	mRootNode(NULL),
	mCurrentNode(NULL)
{
	initWithStream(stream);
}

void CXMLDocument::initWithStream(std::istream& stream)
{
	if (stream)
	{
		CXMLParser parser;
		parser.setTrimsWhitespace();
		parser.setOnStartTag(bind(&CXMLDocument::onStartTag, this, bindTo(0), bindTo(1), bindTo(2)));
		parser.setOnEndTag(bind(&CXMLDocument::onEndTag, this, bindTo(0), bindTo(1)));
		parser.setOnError(bind(&CXMLDocument::onError, this, bindTo(0), bindTo(1)));
		parser.setOnData(bind(&CXMLDocument::onData, this, bindTo(0), bindTo(1)));
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
//	std::cout << "onStartTag: " << name << std::endl;
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
