#pragma once
#include "header.h"
#include "error.h"

class initialization : public error
{
	IN_ADDR addr;
	SOCKET sock;
	SOCKADDR_IN serveraddr;
public:
	IN_ADDR GetDefaultMyIP();
	IN_ADDR GetAddr();
	SOCKET GetSock();
	SOCKADDR_IN GetServeraddr();
	initialization();
	~initialization();
};

