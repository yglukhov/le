//#include "slTypes.h"
#include "slCNotificationCenter.h"
#include <common/debug/slDebug.h>

#include <algorithm>

LE_NAMESPACE_START

struct observer_equals
{
	observer_equals(CObject* observer) : mObserver(observer)
	{
	}

	bool operator()(const CNotificationCenter::CNotifierMap::value_type& elem)
	{
		return elem.first.observer == mObserver;
	}

	CObject* mObserver;
};

struct concrete_observer
{
	concrete_observer(CObject* observer, ENotification notif, CObject* sender) :
		mObserver(observer), mNotif(notif), mSender(sender)
	{
	}

	bool operator()(const CNotificationCenter::CNotifierMap::value_type& elem)
	{
		return (elem.first.observer == mObserver && elem.first.notification == mNotif &&
					(elem.first.sender == NULL || elem.first.sender == mSender));
	}

	CObject* mObserver;
	ENotification mNotif;
	CObject* mSender;
};

struct other_observers
{
	other_observers(ENotification notif, CObject* sender) :
		mNotif(notif), mSender(sender)
	{
	}

	bool operator()(const CNotificationCenter::CNotifierMap::value_type& elem)
	{
		return (elem.first.notification == mNotif &&
					(elem.first.sender == NULL || elem.first.sender == mSender));
	}

	ENotification mNotif;
	CObject* mSender;
};

bool CNotificationCenter::observerExists(CObject* observer)
{
	CNotifierMap::iterator end = mNotifierMap.end();

	return (find_if(mNotifierMap.begin(), end, observer_equals(observer)) != end);
}

CNotification::CNotification(CObject* sender, ENotification notif, void* data) :
	mSender(sender), mNotification(notif), mData(data)
{

}

void* CNotification::data() const
{
	return mData;
}

ENotification CNotification::notification() const
{
	return mNotification;
}

CObject* CNotification::sender() const
{
	return mSender;
}

CNotificationCenter::CNotificationCenter()
{

}

CNotificationCenter::~CNotificationCenter()
{

}

CNotificationCenter* CNotificationCenter::instance()
{
	static CNotificationCenter center;
	return &center;
}

void CNotificationCenter::removeObserver(CObject* observer, ENotification notification, const CObject* sender)
{
	CNotifierMap::iterator it = mNotifierMap.find(SMapKey(observer, sender, notification));
	if(it != mNotifierMap.end())
	{
		//releaseObserver(observer);
		delete it->second;
		mNotifierMap.erase(it);
	}
}

void CNotificationCenter::removeObserver(CObject* observer)
{
	CNotifierMap::iterator end = mNotifierMap.end();
	observer_equals finder(observer);
	CNotifierMap::iterator it = find_if(mNotifierMap.begin(), end, finder);
	while(it != end)
	{
		//releaseObserver(observer);
		delete it->second;
		mNotifierMap.erase(it);
		it = find_if(it, end, finder);
	}
}

void CNotificationCenter::dispatchCallBack(ENotification notification, CObject* sender, void* data, CObject* observer)
{
	CNotification notifObject(sender, notification, data);

	// Sending to concrete observer
	if(observer)
	{
		if(!observerExists(observer))
			return;

		CNotifierMap::iterator end = mNotifierMap.end();
		concrete_observer finder(observer, notification, sender);
		CNotifierMap::iterator it = find_if(mNotifierMap.begin(), end, finder);
		while(it != end)
		{
			it->second->notify(observer, notifObject);
			it = find_if(++it, end, finder);
		}

		return;
	}

	// Sending to other observers
	CNotifierMap::iterator end = mNotifierMap.end();
	other_observers finder(notification, sender);
	CNotifierMap::iterator it = find_if(mNotifierMap.begin(), end, finder);
	while(it != end)
	{
		it->second->notify(it->first.observer, notifObject);
		it = find_if(++it, end, finder);
	}
}

struct CNotificationCenter::SNotificationData
{
	SNotificationData(ENotification Notification, CObject* Sender, void* Data,
							CObject* Receiver) :
		notification(Notification), sender(Sender), data(Data), receiver(Receiver)
	{

	}

	ENotification notification;
	CObject* sender;
	void* data;
	CObject* receiver;
};

void CNotificationCenter::postNotification(ENotification notification, CObject* sender, void* data, CObject* receiver, bool postAsCallBack)
{
	if (postAsCallBack)
	{
		dispatchCallBack(notification, sender, data, receiver);
	}
	else
	{
		mNotificationList.push_back(new SNotificationData(notification, sender,
																				data, receiver));
	}
}

void CNotificationCenter::fire()
{
	while(!mNotificationList.empty())
	{
		SNotificationData* notifData = *mNotificationList.begin();
		dispatchCallBack(notifData->notification, notifData->sender, notifData->data, notifData->receiver);
		delete notifData;
		mNotificationList.pop_front();
	}
}


LE_NAMESPACE_END
