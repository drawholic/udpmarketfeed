#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>

class Client
{
	int sock;

	sockaddr_in* server_addr;
	char* buffer;
	socklen_t addrlen;

	void init()

public:
	Client();
	void run();
};


#endif