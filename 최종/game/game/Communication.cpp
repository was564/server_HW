#include "Communication.h"



Communication::Communication()
	:retval(0), len(0)
{
	memset(buf, 0, sizeof(buf));
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		exit(1);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
}


Communication::~Communication()
{
	closesocket(sock);
	WSACleanup();
}

void Communication::err_quit(const char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void Communication::err_display(const char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int Communication::recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

void Communication::loginInput()
{
	cout << "id를 입력하세요 : ";
	cin >> id;
	cout << "Password를 입력하세요 : ";
	cin >> password;
}

void Communication::loginSend()
{
	buf[0] = 1; // 1 = login header
	buf[1] = strlen(id);
	strcpy(&buf[2], id);
	buf[4 + strlen(id)] = strlen(password);
	strcpy(&buf[5 + strlen(id)], password);
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

bool Communication::loginRecv()
{
	retval = recvn(sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	if (buf[0] == 1) {
		if (buf[1] == 0) {
			cout << "로그인에 실패하였습니다.";
			return false;
		}
		else if (buf[1] == 1) {
			cout << "로그인에 성공하였습니다.";
			return true;
		}
	}
	else {
		return false;
	}
	return false;
}

void Communication::gameSend()
{
}

void Communication::gameRecv()
{
}

void Communication::chatSend()
{
}

void Communication::chatRecv()
{
}
