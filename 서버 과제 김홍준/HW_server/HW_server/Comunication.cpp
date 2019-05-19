#include "Comunication.h"

Comunication::Comunication()
{
	memset(buf, '\0', sizeof(buf));
	memset(data, '\0', sizeof(data));
	memset(temp, '\0', sizeof(temp));
}


Comunication::~Comunication()
{
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
}

void Comunication::Init(LPVOID arg)
{
	// Ŭ���̾�Ʈ ���� ���
	client_sock = (SOCKET)arg;
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (SOCKADDR*)& clientaddr, &addrlen);
}

bool Comunication::FirstRecv()
{
	// ������ �ޱ�
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		return false;
	}
	len = retval;
	// ���� ������ ���
	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port), buf);
	return true;
}

bool Comunication::FirstSend()
{
	// ������ ������
	strcpy(data, buf);
	_itoa(share, temp, 10);
	strcpy(&buf[retval], temp);
	retval = send(client_sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		return false;
	}

	printf("[TCP/%s:%d ������] %s, share = %s %d����Ʈ\n", inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port), data, &buf[len], retval);
	return true;
}

bool Comunication::SecondRecv()
{
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		return false;
	}

	buf[retval] = '\0';
	printf("share�� %s\n", buf);
	return true;
}

void Comunication::ChangeShare()
{
	EnterCriticalSection(initialization::GetSection());
	share = atoi(buf);
	LeaveCriticalSection(initialization::GetSection());
}

bool Comunication::Recv()
{
	// ������ �ޱ�
	retval = recv(client_sock, buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("recv()");
		return false;
	}
	else if (retval == 0)
		return false;

	// ���� ������ ���
	buf[retval] = '\0';
	printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port), buf);
	return true;
}

bool Comunication::Send()
{
	// ������ ������
	retval = send(client_sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		error::err_display("send()");
		return false;
	}
	return true;
}
