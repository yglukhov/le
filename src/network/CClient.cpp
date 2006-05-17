
#include "CClient.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

CClient::CClient(char* ipAddress, int port, bool needConnect) :
	mIpAddress(ipAddress), mPort(port)
{
	if (needConnect)
	{
		connect();
	}
}

bool CClient::connect()
{
	mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (-1 == mSocket)
	{
		std::cout << "Failed to create socket\n";
		return false;
	}

	struct sockaddr_in name;
	name.sin_len = sizeof(name);
	name.sin_family = AF_INET;
	name.sin_port = mPort;
	name.sin_addr.s_addr = inet_addr(mIpAddress);
	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));

	int result;
	result = ::connect(mSocket, (struct sockaddr*)&name, name.sin_len);
	
	if (result == -1)
	{
		mSocket = -1;
	}
	return isConnected();
}