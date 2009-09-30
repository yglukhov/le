#if !defined SL_LE_core_xml_slCXMLNode_h
#define SL_LE_core_xml_slCXMLNode_h

#include <vector>
#include <map>
#include <le/core/slCString.h>

namespace sokira
{
	namespace le
	{

class CXMLNode;
typedef std::vector<CXMLNode*> CXMLNodeArray;

class CXMLNode
{
	public:
		CXMLNode(const CString& name, const std::map<CString, CString>& attributes, CXMLNode* parentNode);
		~CXMLNode();
		CString name() const;

		CXMLNode* parent();
		CXMLNodeArray children();
		CXMLNodeArray childrenWithName(const CString& name);
		CXMLNode* firstChildWithName(const CString& name);

		UInt32 childrenCount() const;

		Bool hasAttribute(const CString& name) const;
		CString attribute(const CString& name) const;

		void addChild(CXMLNode* child);


		void dump(std::ostream& stream);

	private:
		CString mName;
		std::map<CString, CString> mAttributes;
		CXMLNodeArray mChildren;
		CXMLNode* mParent;
};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_xml_slCXMLNode_h
