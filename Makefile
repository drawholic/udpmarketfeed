

all: client server


client: ring_buffer
	g++ -o client Client.cpp ring_buffer.o -I include -g

server: ring_buffer
	g++ -o server Server.cpp ring_buffer.o -I include -g

ring_buffer:
	g++ -c -o ring_buffer.o RingBuffer.cpp -I include -g 


clean:
	rm server client ring_buffer.o