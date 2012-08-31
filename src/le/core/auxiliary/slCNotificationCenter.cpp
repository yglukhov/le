//#include "slTypes.h"
#include <map>

#include "slCNotificationCenter.h"
#include <le/core/debug/slDebug.h>

#include <algorithm>

namespace sokira
{
	namespace le
	{

struct SObserverData
{
	SObserverData(const TCFunction<void, TSTypeList<const CNotification&> >& function, const CObject* sender) :
		mFunction(function),
		mSender(sender)
	{

	}

	TCFunction<void, TSTypeList<const CNotification&> > mFunction;
	const CObject* mSender;
};

typedef std::map<CString, std::list<SObserverData> > TCObserversMap;

CNotification::CNotification(CObject* sender, const CString& name, CObject::Ptr userInfo) :
	mUserInfo(userInfo), mSender(sender), mName(name)
{

}

CObject::Ptr CNotification::userInfo() const
{
	return mUserInfo;
}

CString CNotification::name() const
{
	return mName;
}

CObject* CNotification::sender() const
{
	return mSender;
}

CNotificationCenter::CNotificationCenter() :
	mObservers(new TCObserversMap())
{

}

CNotificationCenter::~CNotificationCenter()
{
	delete static_cast<TCObserversMap*>(mObservers);
}

CNotificationCenter* CNotificationCenter::instance()
{
	static CNotificationCenter center;
	return &center;
}

void CNotificationCenter::addObserver(const TCFunction<void, TSTypeList<const CNotification&> >& function, const CString& notificationName, const CObject* sender)
{
	(*static_cast<TCObserversMap*>(mObservers))[notificationName].push_back(SObserverData(function, sender));
}

struct SObserverRemover
{
	SObserverRemover(const CFunctionDescriptor& function, const CObject* sender) : mDescriptor(function), mSender(sender) { }

	Bool operator()(const SObserverData& data)
	{
		return (!mSender || data.mSender == mSender) && CFunctionDescriptor(data.mFunction) == mDescriptor;
	}

	CFunctionDescriptor mDescriptor;
	const CObject* mSender;
};

void CNotificationCenter::removeObserver(const CFunctionDescriptor& function, const CString& notificationName, const CObject* sender)
{
	TCObserversMap::iterator it = static_cast<TCObserversMap*>(mObservers)->find(notificationName);
	if (it != static_cast<TCObserversMap*>(mObservers)->end())
	{
		it->second.remove_if(SObserverRemover(function, sender));
	}
}

void CNotificationCenter::postNotification(const CNotification& notification)
{
	TCObserversMap::iterator it = static_cast<TCObserversMap*>(mObservers)->find(notification.name());
	if (it != static_cast<TCObserversMap*>(mObservers)->end())
	{
		const CObject* sender = notification.sender();
		for (std::list<SObserverData>::iterator obsIt = it->second.begin(); obsIt != it->second.end(); ++obsIt)
		{
			if (!obsIt->mSender || obsIt->mSender == sender)
			{
				obsIt->mFunction(notification);
			}
		}
	}
}

void CNotificationCenter::postNotification(CObject* sender, const CString& name, CObject::Ptr userInfo)
{
	postNotification(CNotification(sender, name, userInfo));
}

void CNotificationCenter::scheduleNotification(const CNotification& notification)
{
	mScheduledNotifications.push_back(notification);
}

void CNotificationCenter::scheduleNotification(CObject* sender, const CString& name, CObject::Ptr userInfo)
{
	scheduleNotification(CNotification(sender, name, userInfo));
}

void CNotificationCenter::fire()
{
	for (std::list<CNotification>::iterator it = mScheduledNotifications.begin(); it != mScheduledNotifications.end(); ++it)
	{
		postNotification(*it);
	}

	mScheduledNotifications.clear();
}


	} // namespace le
} // namespace sokira
