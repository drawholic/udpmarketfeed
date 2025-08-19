#include "Client.hpp"
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <iostream>
const int buffer_length = 1024;

const char* text = "hello server";

int main(int argc, char const *argv[])
{
	Client c;

	c.run();
	return 0;
}

void Client::run()
{
	int bytes;

	if(connect(sock, (sockaddr*)server_addr, addrlen) == -1)
	{
		perror("Failure connecting to server");
		close(sock);
		return;
	};

	memcpy(buffer, text, strlen(text));


	bytes = send(sock, buffer, buffer_length, 0);

	if(bytes == -1)
	{
		perror("Failure sending");
		return;
	};
	while(true)
	{
		bytes = recv(sock, buffer, buffer_length, 0);
		if(bytes == -1)
			break;
		if(bytes == 0)
		{
			std::cout << "Server disconnected\n";
			break;
		}
		buffer[bytes] = 0;
		std::cout << "Received: " << buffer << std::endl;
	};
	// close(sock);

};

Client::Client()
{
	init();
};

void Client::init()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == -1)
	{
		perror("Failure creating a socket");
		return;
	};

	server_addr = new sockaddr_in;
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(8080);
	server_addr->sin_addr.s_addr = INADDR_ANY;

	addrlen = sizeof(sockaddr_in);

	buffer = new char[buffer_length];
};