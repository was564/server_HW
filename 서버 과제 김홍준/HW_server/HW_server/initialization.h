#pragma once
#include "header.h"
#include "error.h"

extern DWORD WINAPI ProcessClient(LPVOID arg);

class initialization : public error
{
	CRITICAL_SECTION hCriticalSection;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	HANDLE hThread;
	SOCKADDR_IN serveraddr;
	SOCKET listen_sock;
	int retval;
public:
	void Accept();
	void Listen();
	void Bind();
	CRITICAL_SECTION* GetSection();
	SOCKET GetClientSock();
	SOCKET GetListenSock();
	SOCKADDR_IN GetClientaddr();
	SOCKADDR_IN GetServeraddr();
	initialization();
	~initialization();
};

