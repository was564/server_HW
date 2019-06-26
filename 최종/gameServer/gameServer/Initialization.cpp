#include "Initialization.h"

void Initialization::Accept()
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

	ofstream logFile("log.txt", ios::app);
	logFile << "Ŭ���̾�Ʈ ����: IP �ּ�=" << inet_ntoa(clientaddr.sin_addr)
		<< ", ��Ʈ ��ȣ=" << ntohs(clientaddr.sin_port) << endl;

	cout << "Ŭ���̾�Ʈ ����: IP �ּ�=" << inet_ntoa(clientaddr.sin_addr)
		<< ", ��Ʈ ��ȣ=" << ntohs(clientaddr.sin_port) << endl;

	logFile.close();

	// ������ ����
	hThread = CreateThread(NULL, 0, ProcessClient,
		(LPVOID)client_sock, 0, NULL);
	if (hThread == NULL) { closesocket(client_sock); }
	else { CloseHandle(hThread); }
}

void Initialization::Listen()
{
	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) Error::err_quit("listen()");
}

void Initialization::Bind()
{
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)& serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) Error::err_quit("bind()");
}

CRITICAL_SECTION* Initialization::GetSection()
{
	return &hCriticalSection;
}

SOCKET Initialization::GetClientSock()
{
	return client_sock;
}

SOCKET Initialization::GetListenSock()
{
	return listen_sock;
}

SOCKADDR_IN Initialization::GetClientaddr()
{
	return clientaddr;
}

SOCKADDR_IN Initialization::GetServeraddr()
{
	return serveraddr;
}

Initialization::Initialization()
{
	InitializeCriticalSection(&hCriticalSection);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) Error::err_quit("socket()");
}


Initialization::~Initialization()
{
	// closesocket()
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
}
