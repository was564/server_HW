#include "initialization.h"



void initialization::Accept()
{
	addrlen = sizeof(clientaddr);
	client_sock = accept(listen_sock, (SOCKADDR*)& clientaddr, &addrlen);
	if (client_sock == INVALID_SOCKET) {
		err_display("accept()");
		exit(1);
	}

	// ������ Ŭ���̾�Ʈ ���� ���
	printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	// ������ ����
	hThread = CreateThread(NULL, 0, ProcessClient,
		(LPVOID)client_sock, 0, NULL);
	if (hThread == NULL) { closesocket(client_sock); }
	else { CloseHandle(hThread); }
}

void initialization::Listen()
{
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) error::err_quit("listen()");
}

void initialization::Bind()
{
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)& serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) error::err_quit("bind()");
}

CRITICAL_SECTION* initialization::GetSection()
{
	return &hCriticalSection;
}

SOCKET initialization::GetClientSock()
{
	return client_sock;
}

SOCKET initialization::GetListenSock()
{
	return listen_sock;
}

SOCKADDR_IN initialization::GetClientaddr()
{
	return clientaddr;
}

SOCKADDR_IN initialization::GetServeraddr()
{
	return serveraddr;
}

initialization::initialization()
{
	InitializeCriticalSection(&hCriticalSection);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) error::err_quit("socket()");
}


initialization::~initialization()
{
	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
}
