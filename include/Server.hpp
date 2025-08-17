#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
	bool running = true;
	int sock;
	int client_sock;

	sockaddr_in* server_addr;
	sockaddr_in* client_addr;

	socklen_t addrlen;
	char* buffer;

	void init_server();


public:
	Server();

	void run();


};

#endif