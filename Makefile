

all: client server


client:
	g++ -o client Client.cpp -I include -g

server:
	g++ -o server Server.cpp -I include -g

clean:
	rm server client