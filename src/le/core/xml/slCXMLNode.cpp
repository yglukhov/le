#include "slCXMLNode.h"

namespace sokira
{
	namespace le
	{

CXMLNode::CXMLNode(const CString& name, const std::map<CString, CString>& attributes, CXMLNode* parentNode) :
	mName(name),
	mAttributes(attributes),
	mParent(parentNode)
{

}

CXMLNode::~CXMLNode()
{
	for (CXMLNodeArray::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		delete *it;
	}
}


CString CXMLNode::name() const
{
	return mName;
}

CXMLNode* CXMLNode::parent()
{
	return mParent;
}

CXMLNodeArray CXMLNode::children()
{
	return mChildren;
}

CXMLNodeArray CXMLNode::childrenWithName(const CString& name)
{
	CXMLNodeArray result;
	for (CXMLNodeArray::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if ((*it)->name() == name)
		{
			result.push_back(*it);
		}
	}
	return result;
}

CXMLNode* CXMLNode::firstChildWithName(const CString& name)
{
	for (CXMLNodeArray::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		if ((*it)->name() == name)
		{
			return *it;
		}
	}
	return NULL;
}

UInt32 CXMLNode::childrenCount() const
{
	return mChildren.size();
}

Bool CXMLNode::hasAttribute(const CString& name) const
{
	return mAttributes.find(name) != mAttributes.end();
}

CString CXMLNode::attribute(const CString& name) const
{
	std::map<CString, CString>::const_iterator it = mAttributes.find(name);
	return (it == mAttributes.end())?(CString()):(it->second);
}

void CXMLNode::addChild(CXMLNode* child)
{
	mChildren.push_back(child);
}


void CXMLNode::dump(std::ostream& stream)
{
	stream << "<" << mName << " ";
	for (std::map<CString, CString>::iterator it = mAttributes.begin(); it != mAttributes.end(); ++it)
	{
		stream << it->first << "=\"" << it->second << "\" ";
	}

	stream << ">" << std::endl;

	for (CXMLNodeArray::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		(*it)->dump(stream);
	}

	stream << "</" << mName << ">" << std::endl;
}

	} // namespace le
} // namespace sokira
