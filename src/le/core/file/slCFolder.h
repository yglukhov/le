#pragma once

#include <le/core/config/slPrefix.h>
#include <le/gui/slConstants.h> // TODO: Remove dependency from GUI lib

#if !defined _WIN32
#include <dirent.h> // posix header
#endif

LE_NAMESPACE_START

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

LE_NAMESPACE_END
