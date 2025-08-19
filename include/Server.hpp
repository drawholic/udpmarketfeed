#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include "RingBuffer.hpp"
#include <cstring>
#include <vector>
#include <fcntl.h>

class Server
{

	RingBuffer* rb;

	bool running = true;
	std::vector<int> clients;
	int sock;
	int client_sock;

	sockaddr_in* server_addr;
	sockaddr_in* client_addr;

	socklen_t addrlen;
	char* buffer;

	int bytes_read;


	int accept_client();
	int read_client();
	void init_server();
	int broadcast_clients();

public:
	Server();

	void run();


};

#endif