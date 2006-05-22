#pragma once

#if defined _WIN32
	#include "winsock2.h"
#endif

#include <list>

class CCOnnection;

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
#if defined _WIN32
	SOCKET mSock;
#else
	int mSock;
#endif
	std::list<CConnection*> mConnectionList;
};