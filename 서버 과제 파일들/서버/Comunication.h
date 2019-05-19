#pragma once
#include "header.h"
#include "error.h"
#include "initialization.h"

class Comunication : public initialization
{
	char temp[10];
	SOCKET client_sock;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	int len;
	char buf[BUFSIZE + 1];
	char data[BUFSIZE + 1];
public:
	void Init(LPVOID arg);
	bool FirstRecv();
	bool FirstSend();
	bool SecondRecv();
	void ChangeShare();
	bool Recv();
	bool Send();
	Comunication();
	~Comunication();
};

