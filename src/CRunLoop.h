#pragma once

enum EEventType
{
	eMouseEvent
};

class CRunLoopMessage
{
	public:
		CRunLoopMessage(ERunLoopMessage message, CObject* receiver, CObject* sender = NULL, void* data = NULL);
		
		
		ERunLoopMessage mMessage;
		CObject* receiver, CObject* sender = NULL
};

class CMainLoop
{
	public:
		CMainLoop();

		void start();
		void stop();

		void pushMessage(ERunLoopMessage message, CObject* receiver, CObject* sender = NULL, void* data = NULL);

		bool popMessage(CRunLoopMessage& message);
		bool peekMessage(CRunLoopMessage& message);

	private:
		std::list<CRunLoopMessage> mMessageQueue;
};