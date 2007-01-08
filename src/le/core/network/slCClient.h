#pragma once

#include <le/core/config/slPrefix.h>
#include "slCConnection.h"

namespace sokira
{
	namespace le
	{

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

	} // namespace le
} // namespace sokira