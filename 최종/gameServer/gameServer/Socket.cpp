#include "Socket.h"

Socket::Socket()
{
}

Socket::~Socket()
{
}

void Socket::socket2(char* buf, int pass, bool check)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 2;
	buf[1] = pass;
	buf[2] = (int)check;
	player = pass;
}

void Socket::socket3(char* buf)
{
	memset(buf, 0, sizeof(buf));
	int seed = (int)time(NULL);
	buf[0] = 3;
	buf[1] = seed;
}
