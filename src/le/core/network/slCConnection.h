#pragma once 

#include <le/core/config/slPrefix.h>
#if defined _WIN32
	#include "winsock2.h"
#endif

LE_NAMESPACE_START

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

LE_NAMESPACE_END