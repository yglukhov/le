#include "Server.h"
#include "CConnection.h"

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



CServer::CServer(int port)
{
	mSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#if defined _WIN32
	if (INVALID_SOCKET == mSock)
#else	
	if (-1 == mSock)
#endif
	{
		std::cout << "Failed to create socket\n";
		//return -1;
	}

	struct sockaddr_in name;
	name.sin_len = sizeof(name);
	name.sin_family = AF_INET;
	name.sin_port = port;
	name.sin_addr.s_addr = inet_addr("127.0.0.1");
	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));

#if defined _WIN32
	if (SOCKET_ERROR == bind(mSock, (struct sockaddr*)&name, name.sin_len))
#else
	if (0 != bind(mSock, (struct sockaddr*)&name, name.sin_len))
#endif
	{
		close(mSock);
		std::cout << "Failed to bind socket\n";
		mSock = -1;
		return;
	}
	
#if defined _WIN32
	if (SOCKET_ERROR == listen(mSock, 1))
#else
	if (0 != listen(mSock, 1))
#endif
	{
		close(mSock);
		mSock = -1;
		std::cout << "Failed to listen socket\n";
		return;
	}
}

CConnection* CServer::accept()
{
	struct sockaddr addr;
	socklen_t length = sizeof(sockaddr);
	int connectionSocket = ::accept(mSock, &addr, &length);

	if (connectionSocket != -1)
	{
		std::cout << "Succesfully connected to client\n";
		
		CConnection* connect = new CConnection(connectionSocket);
		mConnectionList.push_back(connect);
		return connect;
	}
	
	return NULL;
}

CServer::~CServer()
{
	if (mSock != -1)
	{
		::shutdown(mSock, 2);
#if defined _WIN32		
		::closesocket(mSock);
#else
		::close(mSock);
#endif
	}
}
//int startServer()
//{
//   // insert code here...
//   std::cout << "Server\n";
//
//	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (-1 == sock)
//	{
//		std::cout << "Failed to create socket\n";
//		return -1;
//	}
//
//	struct sockaddr_in name;
//	name.sin_len = sizeof(name);
//	name.sin_family = AF_INET;
//	name.sin_port = 5050;
//	name.sin_addr.s_addr = inet_addr("127.0.0.1");
//	::memset(&(name.sin_zero), 0, sizeof(name.sin_zero));
//	
//	if (0 != bind(sock, (struct sockaddr*)&name, name.sin_len))
//	{
//		close(sock);
//		std::cout << "Failed to bind socket\n";
//		return -1;
//	}
//	
//	if (0 != listen(sock, 1))
//	{
//		close(sock);
//		std::cout << "Failed to listen socket\n";
//		return -1;
//	}
//	
//	while (true)
//	{
//		struct sockaddr addr;
//		socklen_t length = sizeof(sockaddr);
//		int isOk = accept(sock, &addr, &length);
//		if (isOk != -1)
//		{
//			std::cout << "Succesfully connected to client\n";
//			handleCommandsForSocket(isOk);
//		}
//	}
//	return 0;
//}
//
//void handleCommandsForSocket(int sock)
//{
//	std::string command;
//	while (true)
//	{
//		char data[2] = {0};
//		ssize_t ln = recv(sock, data, 1, 0);
//		std::cout << data << std::endl;
//		if (std::string(data) == "\n")
//		{
//			//interpret(command);
//			command.clear();
//		}
//		else
//		{
//			command.append(data);
//		}
//	}
//}
