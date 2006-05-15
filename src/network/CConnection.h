
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

	int mSocket;
};