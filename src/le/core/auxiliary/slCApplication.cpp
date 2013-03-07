#include <le/core/slCClassFactory.h>
#include "slCApplication.h"
#include "slCBundle.h"

namespace sokira
{
	namespace le
	{

static CApplication* gCurrentApplication = NULL;

CApplication::CApplication() :
	mPreferences(NULL)
{

}

CApplication::~CApplication()
{
	delete mPreferences;
}

CApplication* CApplication::currentApplication()
{
	return gCurrentApplication;
}

int CApplication::run(int argc, const char * const argv[])
{
	CApplication* prevApplication = gCurrentApplication;
	gCurrentApplication = this;

	mCommandLine.setArguments(argc, argv);

	// Verify the delegate. Create one from Info.plist file, if the delegate is
	// not set until now.
	if (!mDelegate)
	{
		CString delegateClass = mainBundle().infoDictionary().valueAsStringForKey("SLAppDelegateClass");
		setDelegateClass(delegateClass);
		if (!mDelegate)
		{
			mDelegate = CClassFactory::defaultInstance()->bestSubclassOfClassWithParameters(CApplicationDelegate::staticClass(), CDictionary()).create<CApplicationDelegate>();
			if (!mDelegate)
			{
				std::cout << "Could not create delegate of class \"" << delegateClass << "\"" << std::endl;
				char c;
				std::cin >> c;
				return 1;
			}
			std::cout << "delegate class: " << mDelegate->objectClass().name() << std::endl;
		}
	}

	mDelegate->_setApplication(this);

	int result = runApplication();
	gCurrentApplication = prevApplication;
	return result;
}

void CApplication::quit()
{
	// Subclasses have to override this function so that runApplication() will return upon this call
}

Bool CApplication::canQuit() const
{
	return true;
}

CCommandLine CApplication::commandLine() const
{
	return mCommandLine;
}

CPreferences* CApplication::preferences()
{
	if (!mPreferences) mPreferences = new CPreferences(mainBundle().identifier());
	return mPreferences;
}

void CApplication::setDelegate(CApplicationDelegate::Ptr delegate)
{
	mDelegate = delegate;
}

bool CApplication::setDelegateClass(const CString& className)
{
	CClassFactory* factory = CClassFactory::defaultInstance();
	TCPointer<CApplicationDelegate> delegate = factory->create<CApplicationDelegate>((const CBasicString&)className);

	if (delegate)
	{
		mDelegate = delegate;
		return true;
	}

	return false;
}

SInt32 CApplication::runApplication()
{
	return 0;
}

CApplicationDelegate::Ptr CApplication::delegate()
{
	return mDelegate;
}

CBundle CApplication::mainBundle() const
{
	return CBundle(mCommandLine.argumentAtIndex(0));
}


	} // namespace le
} // namespace sokira
