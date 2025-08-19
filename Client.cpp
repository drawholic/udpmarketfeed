#include "Client.hpp"
#include <cstdio>
#include <unistd.h>

const int buffer_length = 1024;

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

	buffer = "hello server";
	bytes = send(sock, buffer, buffer_length, 0);

	if(bytes == -1)
	{
		perror("Failure sending");
		return;
	};
	close(sock);

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
	server_addr->sin_port = htons(80);
	server_addr->sin_addr.s_addr = INADDR_ANY;

	addrlen = sizeof(sockaddr_in);

	buffer = new char[buffer_length];
};