
#include "CClient.h"

#if defined _WIN32

#include "winsock2.h"

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#endif

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
#if defined _WIN32
	if (INVALID_SOCKET == mSocket)
#else	
	if (-1 == mSocket)
#endif
	{
		std::cout << "Failed to create socket\n";
		return false;
	}

	struct sockaddr_in name;
	name.sin_len = sizeof(name);
	name.sin_family = AF_INET;
	name.sin_port = mPort;
	name.sin_addr.s_addr = ::inet_addr(mIpAddress);
	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));

	int result;
	result = ::connect(mSocket, (struct sockaddr*)&name, name.sin_len);
#if defined _WIN32
	if (result == INVALID_SOCKET)
#else
	if (result == -1)
#endif
	{
		mSocket = -1;
	}
	return isConnected();
}