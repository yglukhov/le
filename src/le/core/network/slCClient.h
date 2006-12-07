#pragma once

#include <le/core/config/slPrefix.h>
#include "slCConnection.h"

LE_NAMESPACE_START

class CClient : public CConnection
{
 public:	
	CClient(char* ipAddress, int port = 5050, bool connect = false);
	bool isConnected();
	bool connect();

private:
	char* mIpAddress;
	int mPort;
};

LE_NAMESPACE_END