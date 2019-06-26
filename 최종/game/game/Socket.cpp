#include "Socket.h"

Socket::Socket()
{
}

Socket::~Socket()
{
}

void Socket::socket1(char* buf, const char* id, const char* pw)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 1; // 1 = login header
	buf[1] = (int)strlen(id);
	strcpy(&buf[2], id);
	buf[2 + strlen(id)] = (int)strlen(pw);
	strcpy(&buf[3 + strlen(id)], pw);
}

void Socket::socket4(char* buf, int object, int p_x, int p_y, int e_x, int e_y)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 4;
	buf[1] = object;
	buf[2] = p_x;
	buf[3] = p_y;
	buf[4] = e_x;
	buf[5] = e_y;
}

void Socket::socket5(char* buf, int object, int p_x, int p_y)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 5;
	buf[1] = object;
	buf[2] = p_x;
	buf[3] = p_y;
}

void Socket::socket6(char* buf, int p_x, int p_y)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 6;
	buf[1] = p_x;
	buf[2] = p_y;
}

void Socket::socket7(char* buf, const char* id, const char* pw)
{
	memset(buf, 0, sizeof(buf));
	buf[0] = 7;
	buf[1] = (int)strlen(id);
	strcpy(&buf[2], id);
	buf[2 + strlen(id)] = (int)strlen(pw);
	strcpy(&buf[3 + strlen(id)], pw);
}
