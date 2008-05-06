#pragma once

#include <le/core/slTypes.h>

#if !defined _WIN32
#include <dirent.h> // posix header
#endif

namespace sokira
{
	namespace le
	{

enum EFolderNode
{
	eFolderNodeUnknown = 0,
	eFolderNodeFolder,
	eFolderNodeRegular,
	eFolderNodeLink,
	eFolderNodeFIFO, // DO NOT USE
	eFolderNodeChr, // DO NOT USE
	eFolderNodeBlk, // DO NOT USE
	eFolderNodeSocket, // DO NOT USE
	eFolderNodeWht // DO NOT USE
};

////////////////////////////////////////////////////////////////////////////////
// class CFolder - used to enumerate through folder contents, create folders
// and delete files or folders.
////////////////////////////////////////////////////////////////////////////////
class CFolder
{
	public:
		//////////////////////////////////////////////////////////////////////////
		// Construction & destruction
		CFolder();
		~CFolder();

		//////////////////////////////////////////////////////////////////////////
		// Opening
		EStatus open(const char* path, unsigned openFlags);
		void close();

		//////////////////////////////////////////////////////////////////////////
		// Navigating
		bool rewindNode();
		bool nextNode();
		bool endNode() const;

		//////////////////////////////////////////////////////////////////////////
		// Gettting node info
		const char* curNodeName() const;
		EFolderNode curNodeType() const;

		//////////////////////////////////////////////////////////////////////////
		// Remove current node, and iterate to next node. Returns false, if
		// reached end node.
		bool removeCurNode();

#if !defined _WIN32
	private:
		DIR* mDir;
		dirent* mEntry;
#endif
};

	} // namespace le
} // namespace sokira
