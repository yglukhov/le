#include "slCClient.h"

#include <le/core/debug/slDebug.h>
#include <iostream>

#if defined _WIN32
	#include "winsock2.h"
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <iostream>
#endif

#ifndef _WIN32
	#define SOCKET int
	#define INVALID_SOCKET -1
#endif

namespace sokira
{
	namespace le
	{

CClient::CClient(char* ipAddress, int port, bool needConnect) :
	mIpAddress(ipAddress), mPort(port)
{
	LE_ENTER_LOG;
	if (needConnect)
	{
		connect();
	}
}

bool CClient::connect()
{
	LE_ENTER_LOG;
	mSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == mSocket)
	{
		LE_IF_LOG(log << "Failed to create socket\n");
		return false;
	}

	struct sockaddr_in name;
#ifndef _WIN32
	name.sin_len = sizeof(name);
#endif
	name.sin_family = AF_INET;
	name.sin_port = mPort;
	name.sin_addr.s_addr = ::inet_addr(mIpAddress);
	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));

	int result;
	result = ::connect((SOCKET)mSocket, (struct sockaddr*)&name, sizeof(name));

	if (result == INVALID_SOCKET)
	{
		mSocket = INVALID_SOCKET;
	}
	return isConnected();
}

bool CClient::isConnected()
{
	LE_ENTER_LOG;
	return mSocket != INVALID_SOCKET;
}

	} // namespace le
} // namespace sokira