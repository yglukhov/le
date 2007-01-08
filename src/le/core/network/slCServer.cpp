#include "slCServer.h"
#include "slCConnection.h"

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

#if defined _WIN32
	#include "winsock2.h"
#endif

#ifndef _WIN32
	#define SOCKET int
	#define INVALID_SOCKET -1
#else
	#define socklen_t int
#endif

namespace sokira
{
	namespace le
	{

CServer::CServer(unsigned port)
{
	LE_ENTER_LOG;
	mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == (SOCKET)mSock)
	{
		IF_LOG(log << "Failed to create socket\n");
	}

	struct sockaddr_in name;
#ifndef _WIN32
	name.sin_len = sizeof(name);
#endif
	name.sin_family = AF_INET;
	name.sin_port = port;
	name.sin_addr.s_addr = inet_addr("");
	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));

#if defined _WIN32
	if (SOCKET_ERROR == bind((SOCKET)mSock, (struct sockaddr*)&name, sizeof(name)))
#else
	if (0 != bind((SOCKET)mSock, (struct sockaddr*)&name, name.sin_len))
#endif
	{
#if defined _WIN32		
		::closesocket((SOCKET)mSock);
#else
		::close((SOCKET)mSock);
#endif
		IF_LOG(log << "Failed to bind socket\n");
		/*(SOCKET)*/mSock = INVALID_SOCKET;
		return;
	}
	
#if defined _WIN32
	if (SOCKET_ERROR == listen((SOCKET)mSock, 1))
#else
	if (0 != listen((SOCKET)mSock, 1))
#endif
	{
#if defined _WIN32		
		::closesocket((SOCKET)mSock);
#else
		::close((SOCKET)mSock);
#endif
		/*(SOCKET)*/mSock = INVALID_SOCKET;
		IF_LOG(log << "Failed to listen socket\n");

		return;
	}
}

CConnection* CServer::accept()
{
	LE_ENTER_LOG;
	struct sockaddr addr;
	socklen_t length = sizeof(sockaddr);
	int connectionSocket = ::accept((SOCKET)mSock, &addr, &length);

	if (connectionSocket != INVALID_SOCKET)
	{
		IF_LOG(log << "Succesfully connected to client\n");
		
		CConnection* connect = new CConnection(connectionSocket);
		mConnectionList.push_back(connect);
		return connect;
	}
	
	return NULL;
}

CServer::~CServer()
{
	LE_ENTER_LOG;
	if ((SOCKET)mSock != INVALID_SOCKET)
	{
		::shutdown((SOCKET)mSock, 2);
#if defined _WIN32		
		::closesocket((SOCKET)mSock);
#else
		::close((SOCKET)mSock);
#endif
	}
}

	} // namespace le
} // namespace sokira