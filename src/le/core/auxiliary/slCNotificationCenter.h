#pragma once

#include <list>

#include <le/core/config/slPrefix.h>
#include <le/core/slCString.h>
#include <le/core/template/function/slTCFunction.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
// CNotification - sent as a parameter to notification handler.
class CNotification
{
	public:
		CNotification() : mSender(NULL) {};
		CNotification(CObject* sender, const CString& name, CObject::Ptr userInfo = NULL);

		CString name() const;
		CObject* sender() const;
		CObject::Ptr userInfo() const;

	private:
		CObject::Ptr mUserInfo;
		CObject* mSender;
		CString mName;
};

////////////////////////////////////////////////////////////////////////////////
// CNotificationCenter
class CNotificationCenter
{
	// Interface
	public:
		static CNotificationCenter* instance();

		void addObserver(const TCFunction<void, TSTypeList<const CNotification&> >& function, const CString& notificationName, const CObject* sender = NULL);
		void removeObserver(const CFunctionDescriptor& function, const CString& notificationName, const CObject* sender = NULL);

		void postNotification(const CNotification& notification);
		void postNotification(CObject* sender, const CString& name, CObject::Ptr userInfo = NULL);

		void scheduleNotification(const CNotification& notification);
		void scheduleNotification(CObject* sender, const CString& name, CObject::Ptr userInfo = NULL);

		void fire();

	// Implementation
	private:
		CNotificationCenter();
		~CNotificationCenter();

		bool observerExists(CObject*);
		void dispatchNotification(const CNotification& notification);

	// Data
	private:
		void* mObservers;
		std::list<CNotification> mScheduledNotifications;
};

	} // namespace le
} // namespace sokira
