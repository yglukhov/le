#include "CConnection.h"

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