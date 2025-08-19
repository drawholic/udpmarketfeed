#include "Server.hpp"
#include <cstdio>
#include <iostream>
#include <unistd.h>

const int buffer_length = 1024;

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
	client_sock = accept(sock, (sockaddr*)&client_addr, &addrlen);		
	
	if(client_sock == -1)	
	{
		perror("Failure reading a client");
		return -1;
	};
	return 0;
};

int Server::read_client()
{
	bytes_read = read(client_sock, buffer, buffer_length);

 	if(bytes_read == -1)
 	{
 		perror("Failure reading\n");
 		return -1;
 	};
 	buffer[bytes_read] = 0;
 
 	std::cout << "Received: " << buffer << std::endl;
 	return 0;
};

void Server::run()
{

	while(running){

	if(accept_client())
		continue;

 	if(read_client())
 		continue;

  	close(client_sock);

	};


};

void Server::init_server()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == -1)
	{
		perror("Failure creating socket");
		running = false;
		return;
	}
	
	server_addr = new sockaddr_in;

	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(80);
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