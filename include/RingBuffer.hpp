#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

class RingBuffer
{
	unsigned toread_idx;
	unsigned towrite_idx;
	unsigned length;
	char* buffer;

public:
	RingBuffer(unsigned);
	void towrite(char);
	char toread();

};

#endif