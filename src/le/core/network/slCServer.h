#pragma once

#include <list>
#include <le/core/config/slPrefix.h>

LE_NAMESPACE_START

class CConnection;

class CServer
{
 public:
	CServer(unsigned port);
	~CServer();

	void start();
	bool isStarted();
	
	unsigned connectoins();
	CConnection* connectionAtIndex(unsigned index);
	CConnection* accept();
	void disconnect(CConnection* connect);
	void disconnectAll();
 private:
 	char* mHost;
 	unsigned mPort;
//#if defined _WIN32
//	SOCKET mSock;
//#else
	int mSock;
//#endif
	std::list<CConnection*> mConnectionList;
};

LE_NAMESPACE_END
