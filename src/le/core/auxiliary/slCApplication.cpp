#include <le/core/slCClassFactory.h>
#include "slCApplication.h"
#include "slCApplicationDelegate.h"

namespace sokira
{
	namespace le
	{

CApplication::CApplication() :
	mDelegate(NULL)
{

}

static inline Bool loadDelegateFromInfoPlist(CApplication* app)
{
	// TODO: Complete this.
	return app->setDelegateClass("This class name should be loaded from info.plist");
}

int CApplication::run(int argc, const char * const argv[])
{
	mCommandLine.setArguments(argc, argv);

	// Verify the delegate. Create one from Info.plist file, if the delegate is
	// not set until now.
	if (!mDelegate)
	{
		if (!loadDelegateFromInfoPlist(this))
		{
			std::cerr << "Application delegate could not be loaded" << std::endl;
			return 1;
		}
	}

	mDelegate->_setApplication(this);

	return runApplication();
}

void CApplication::quit()
{
	// Subclasses have to override this function so that runApplication() will return upon this call 
}

CCommandLine CApplication::commandLine() const
{
	return mCommandLine;
}

void CApplication::setDelegate(CApplicationDelegate& delegate)
{
	mDelegate = &delegate;
	mOwnDelegate = false;
}

bool CApplication::setDelegateClass(const CString& className)
{
	CClassFactory* factory = CClassFactory::defaultInstance();
	TCPointer<CApplicationDelegate> delegate = factory->create<CApplicationDelegate>((const CBasicString&)className);

	if (delegate)
	{
		if (mOwnDelegate) delete mDelegate;
		mDelegate = delegate.get();
		delegate.retain();
		mOwnDelegate = true;
		return true;
	}

	return false;
}

SInt32 CApplication::runApplication()
{
	return 0;
}

CApplicationDelegate* CApplication::delegate()
{
	return mDelegate;
}

CBundle CApplication::mainBundle() const
{
	return CBundle(mCommandLine.argumentAtIndex(0));
}


	} // namespace le
} // namespace sokira
