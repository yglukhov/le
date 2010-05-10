#pragma once

#include <le/core/config/slPrefix.h>
#include <map>
#include <list>

namespace sokira
{
	namespace le
	{

class CObject;

enum ENotification
{
	eNotificationIdle = 1,
	eNotificationWindowDeleted = 2,
	eNotification2,
	eNotification3,
	//...
	eLastNotification
};

////////////////////////////////////////////////////////////////////////////////
// CNotification - sent as a parameter to notification handler.
class CNotification
{
	public:
		CNotification(CObject*, ENotification, void*);

		ENotification notification() const;
		CObject* sender() const;
		void* data() const;

	private:
		void*	mData;
		CObject* mSender;
		ENotification mNotification;
};

////////////////////////////////////////////////////////////////////////////////
// CNotificationCenter
class CNotificationCenter
{
	// Interface
	public:
		static CNotificationCenter* instance();

		template <class T /* : public CObject */, class TFuncRetType>
		void addObserver(T* observer, TFuncRetType(T::*function)(CNotification&), ENotification notification,
								CObject* sender = NULL);
		void removeObserver(CObject* observer, ENotification notification, const CObject* sender = NULL);
		void removeObserver(CObject* observer);
		void postNotification(ENotification notification, CObject* sender, void* data = NULL,
									 CObject* receiver = NULL, bool postAsCallBack = false);

		void fire();
	// Implementation
	private:
		CNotificationCenter();
		~CNotificationCenter();

		bool observerExists(CObject*);
		void dispatchCallBack(ENotification, CObject*, void*, CObject*);


	// Data
	private:

		struct SMapKey
		{
			CObject* observer;
			const CObject* sender;
			ENotification notification;

			SMapKey(CObject* Observer, const CObject* Sender, ENotification Notification) :
				observer(Observer), sender(Sender), notification(Notification)
			{

			}

			bool operator < (const SMapKey& rhs) const
			{
				return (observer < rhs.observer) || (sender < rhs.sender) || (notification < rhs.notification);
			}
		};

		class INotifier
		{
			public:
				virtual void notify(CObject*, CNotification&) = 0;
				virtual ~INotifier() {}
		};

		typedef std::map<SMapKey, INotifier*> CNotifierMap;
		CNotifierMap mNotifierMap;

		struct SNotificationData;
		typedef std::list<SNotificationData*> CNotificationList;
		CNotificationList mNotificationList;

		friend struct observer_equals;
		friend struct concrete_observer;
		friend struct other_observers;
};


////////////////////////////////////////////////////////////////////////////////
// Implementation
template<class T, class TFuncRetType>
void CNotificationCenter::addObserver(T* observer, TFuncRetType(T::*function)(CNotification&),
													ENotification notification, CObject* sender)
{
	class CNotifier : public INotifier
	{
		typedef TFuncRetType(T::*TFunction)(CNotification&);
		TFunction mFunction;

		void notify(CObject* observer, CNotification& notification)
		{
			(((T*)observer)->*mFunction)(notification);
		}

		public:
			CNotifier(TFunction function) : mFunction(function)
			{
			}
	};

	mNotifierMap.insert(CNotifierMap::value_type(CMapKey(observer, sender, notification),
																new CNotifier(function)));
}


	} // namespace le
} // namespace sokira
