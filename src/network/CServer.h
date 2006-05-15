#pragma once

class CConnection
{
 public:
	CConnection(char* host, unsigned port)
	: mHost(host), mPort(port){}
	
	char* read(unsigned bytes){}
	void write(char* data, unsigned bytes){}

 private:
 	char* mHost;
 	unsigned mPort;	
};

class CServer
{
 public:
	CServer(unsigned port);
	
	void start();
	bool isStarted();
	
	unsigned connectoins();
	CConnection* connectionAtIndex(unsigned index);

	void disconnect(CConnection* connect);
	void disconnectAll();
 private:
 	char* mHost;
 	unsigned mPort;
};