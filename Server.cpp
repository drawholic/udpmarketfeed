#include "Server.hpp"
#include <cstdio>
#include <iostream>
#include <unistd.h>

const int buffer_length = 1024;
const char* msg_to_clients = "Hello client";
int main(int argc, char const *argv[])
{
	Server s;
	s.run();

	return 0;
}

Server::Server()
{
	init_server();

	rb = new RingBuffer(20);

};

int Server::accept_client()
{
	client_sock = accept4(sock, (sockaddr*)&client_addr, &addrlen, SOCK_CLOEXEC | SOCK_NONBLOCK);		
	
	if(client_sock == -1)	
	{
		return -1;
	};
	clients.push_back(client_sock);
	return 0;
};

int Server::read_client()
{
	bytes_read = recv(client_sock, buffer, buffer_length, MSG_DONTWAIT);

 	if(bytes_read == -1)
 	{
 		return 0;
 	};

 	buffer[bytes_read] = 0;
 
 	std::cout << "Received: " << buffer << std::endl;
 	return 0;
};

void Server::run()
{

	while(running){

		usleep(1000000);
		accept_client();

	 	read_client();

	 	broadcast_clients();
	};


};

int Server::broadcast_clients()
{
	int bytes;
	for(auto i : clients)
	{
		bytes = send(i, msg_to_clients, strlen(msg_to_clients), 0);
		if(bytes == -1)
			perror("Failure sending");

	};
	return 0;
}

void Server::init_server()
{
	sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);

	if(sock == -1)
	{
		perror("Failure creating socket");
		running = false;
		return;
	}

	int reuse = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
	{
		perror("Failure setting socket option");
		running = false;
		return;
	};

	if(fcntl(sock, F_SETFL, O_NONBLOCK)  == -1){
		perror("Failure setting nonblock");
		running = false;
		return;
	};


	server_addr = new sockaddr_in;

	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(8080);
	server_addr->sin_addr.s_addr = INADDR_ANY;

	addrlen = sizeof(*server_addr);

	if(bind(sock, (sockaddr*)server_addr, addrlen) == -1)
	{
		perror("Failure to bind");
		running = false;
		return;
	}
	
	if(listen(sock, 10) == -1)
	{
		perror("Failure to set listen");
		running = false;
		return;
	};

	buffer = new char[buffer_length];
};