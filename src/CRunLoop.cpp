#include "CRunLoop.h"

static CMainLoop* _mainLoop = NULL;

CMainLoop::CMainLoop()
{
	_mainLoop = this;
}

void CMainLoop::start()
{

}

void CMainLoop::stop()
{

}

void CMainLoop::pushMessage(ERunLoopMessage message, CObject* receiver, CObject* sender, void* data)
{

}

bool CMainLoop::popMessage(CRunLoopMessage& message)
{

}

bool CMainLoop::peekMessage(CRunLoopMessage& message)
{

}