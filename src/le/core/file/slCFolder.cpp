#include "slCFolder.h"
#include <le/core/debug/slDebug.h>

namespace sokira
{
	namespace le
	{

#if defined _WIN32
	#pragma message(__FILE__ " : warning LE: Folders are not implemented for Win32 yet.")
#endif

CFolder::CFolder()
#if !defined _WIN32
: mDir(NULL), mEntry(NULL)
#endif
{

}

CFolder::~CFolder()
{
	close();
}

//////////////////////////////////////////////////////////////////////////
// Opening
EStatus CFolder::open(const char* path, unsigned openFlags)
{
#if !defined _WIN32
	// TODO: make processing of openFlags
	mDir = opendir(path);
	return (mDir)?(eStatusOK):(eStatusOpenFailed);
#else
	return eStatusErrorOpenFailed;
#endif
}

void CFolder::close()
{
#if !defined _WIN32
	if(mDir)
	{
		closedir(mDir);
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
// Navigating
bool CFolder::rewindNode()
{
#if !defined _WIN32
	LE_ASSERT(mDir != NULL);

	rewinddir(mDir);
#endif
	return nextNode();
}

bool CFolder::nextNode()
{
#if !defined _WIN32
	LE_ASSERT(mDir != NULL);

	mEntry = readdir(mDir);
#endif
	return endNode();
}

bool CFolder::endNode() const
{
#if !defined _WIN32
	return (mEntry != NULL);
#else
	return true;
#endif
}

//////////////////////////////////////////////////////////////////////////
// Gettting node info
const char* CFolder::curNodeName() const
{
#if !defined _WIN32
	LE_ASSERT(mEntry != NULL);
	return mEntry->d_name;
#else
	return NULL;
#endif
}

EFolderNode CFolder::curNodeType() const
{
#if !defined _WIN32
	LE_ASSERT(mEntry != NULL);
	switch(mEntry->d_type)
	{
		case DT_DIR:		return eFolderNodeFolder;
		case DT_FIFO:		return eFolderNodeFIFO;
		case DT_CHR:		return eFolderNodeChr;
		case DT_BLK:		return eFolderNodeBlk;
		case DT_REG:		return eFolderNodeRegular;
		case DT_LNK:		return eFolderNodeLink;
		case DT_SOCK:		return eFolderNodeSocket;
		case DT_WHT:		return eFolderNodeWht;
		default:;
	}
#endif

	return eFolderNodeUnknown;
}

//////////////////////////////////////////////////////////////////////////
// Remove current node, and iterate to next node. Returns false, if
// reached end node.
bool CFolder::removeCurNode()
{
	// TODO: complete this
	return nextNode();
}


	} // namespace le
} // namespace sokira
