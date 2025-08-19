#include "RingBuffer.hpp"

RingBuffer::RingBuffer(unsigned size)
{
	buffer = new char[size];
	length = size;	
	toread_idx = 0;
	towrite_idx = 0;
};


void RingBuffer::towrite(char c)
{
	if(towrite_idx == length)
		towrite_idx = 0;
	
	buffer[towrite_idx++] = c;

};

char RingBuffer::toread()
{
	if(toread_idx == length)
		toread_idx = 0;
	
	return buffer[toread_idx++];
	
};