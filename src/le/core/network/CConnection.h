#pragma once 

#if defined _WIN32
	#include "winsock2.h"
#endif

class CConnection
{
 public:
	void* read(unsigned length, int* realLength);
	int write(void* data, unsigned bytes);

 protected:
	CConnection(int socket);
	CConnection(){}
	~CConnection();

	friend class CServer;
#if defined _WIN32
	SOCKET mSocket;
#else
	int mSocket;
#endif
};