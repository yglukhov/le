#include "slCBundle.h"

namespace sokira
{
	namespace le
	{

CBundle::CBundle()
{

}

CBundle::CBundle(const CString& path)
{

}

CBundle::CBundle(const CURL& url)
{

}


CURL CBundle::url() const
{
	return CURL();
}

CURL CBundle::infoPlistUrl() const
{
	return CURL();
}

CURL CBundle::resourcesUrl() const
{
	return CURL();
}

CURL CBundle::executableUrl() const
{
	return CURL();
}

	} // namespace le
} // namespace sokira
