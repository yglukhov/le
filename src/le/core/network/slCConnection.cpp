#include "slCConnection.h"

#include <le/core/debug/slDebug.h>

#if defined _WIN32
	#pragma comment(lib, "Ws2_32")
	#include "winsock2.h"
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <iostream>
	#include <unistd.h>
#endif

#ifndef _WIN32
	#define SOCKET int
	#define INVALID_SOCKET -1
#endif

namespace sokira
{
	namespace le
	{

void* CConnection::read(unsigned length, int* realLength)
{
	LE_ENTER_LOG;
	if (mSocket != -1)
	{
		void* data = new char[length];
		*realLength = ::recv((SOCKET)mSocket, (char*)data, length, 0);
		
		return data;
	}
	else
	{
		*realLength = 0;
		return NULL;
	}
}

int CConnection::write(void* data, unsigned bytes)
{
	LE_ENTER_LOG;
	if ((SOCKET)mSocket != -1)
	{
		return ::send((SOCKET)mSocket, (char*)data, bytes, 0);
	}
	else
	{
		return -1;
	}
}

CConnection::CConnection(int socket) :
	mSocket(socket)
{
	LE_ENTER_LOG;
}

CConnection::~CConnection()
{
	LE_ENTER_LOG;
	if ((SOCKET)mSocket != -1)
	{
		::shutdown((SOCKET)mSocket, 2);
#if defined _WIN32		
		::closesocket((SOCKET)mSocket);
#else
		::close((SOCKET)mSocket);
#endif
	}
}

	} // namespace le
} // namespace sokira
