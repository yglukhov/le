
#include "CConnection.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void* CConnection::read(unsigned length, int* realLength)
{
	if (mSocket != -1)
	{
		void* data = new char(length);
		*realLength = recv(mSocket, data, length, 0);
		
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
	if (mSocket != -1)
	{
		return send(mSocket, data, bytes, 0);
	}
	else
	{
		return -1;
	}
}

CConnection::CConnection(int socket) :
	mSocket(socket)
{
}

CConnection::~CConnection()
{
	if (mSocket != -1)
	{
		//::close(mSocket);
	}
}
