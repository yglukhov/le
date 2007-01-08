#pragma once

#include <list>
#include <le/core/config/slPrefix.h>

namespace sokira
{
	namespace le
	{

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

	} // namespace le
} // namespace sokira
