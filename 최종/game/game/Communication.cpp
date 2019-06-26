﻿#include "Communication.h"



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

void Communication::loginInput(int n)
{
	if (n == 2) {
		cout << "id를 입력하세요 : ";
		cin >> id;
		cout << "Password를 입력하세요 : ";
		cin >> password;
	}
	else if (n == 1) {
		cout << "가입하신 id를 입력하세요 : ";
		cin >> id;
		cout << "가입하신 Password를 입력하세요 : ";
		cin >> password;
		cout << "회원가입이 완료되었습니다." << endl;
	}
}

void Communication::loginSend(int n)
{
	memset(buf, 0, sizeof(buf));
	if (n == 2) {
		socket1(buf, id, password);
	}
	else if (n == 1) {
		socket7(buf, id, password);
		cout << "이 계정으로 로그인합니다." << endl;
	}
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

bool Communication::loginRecv(int* pass)
{
	retval = recvn(sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	if ((int)buf[0] == 2) {
		if ((int)buf[2] == 0) {
			cout << "로그인에 실패하였습니다.";
			return false;
		}
		else if ((int)buf[2] == 1) {
			cout << "로그인에 성공하였습니다.";
			*pass = buf[1];
			return true;
		}
	}
	else {
		return false;
	}
	return false;
}

int Communication::gameStart()
{
	retval = recvn(sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	return buf[1];
}

void Communication::gameSendE(int pass, int a, int b, int x, int y)
{
	memset(buf, 0, sizeof(buf));
	socket4(buf, pass, a, b, x, y);
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

void Communication::gameSendP(int object, int a, int b)
{
	memset(buf, 0, sizeof(buf));
	socket5(buf, object, a, b);
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

void Communication::gameSend(int a, int b)
{
	memset(buf, 0, sizeof(buf));
	socket6(buf, a, b);
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}

void Communication::gameRecv(int player, GameObject* object[])
{
	memset(buf, 0, sizeof(buf));
	retval = recv(sock, buf, retval, 0);
	if (retval == SOCKET_ERROR) {
		err_display("recv()");
		exit(1);
	}
	if (buf[0] == 4) {
		gotoxy(object[player]->getPosition().x, object[player]->getPosition().y);
		printf("  ");
		gotoxy(object[buf[1] - 10]->getPosition().x, object[buf[1] - 10]->getPosition().y);
		printf("  ");
		object[player]->setPosition(buf[2], buf[3]);
		object[buf[1] - 10]->setPosition(buf[4], buf[5]);
		object[player]->addscore(10);
		object[player]->update();
		object[buf[1] - 10]->update();
	}
	else if (buf[0] == 5) {
		gotoxy(object[player]->getPosition().x, object[player]->getPosition().y);
		printf("  ");
		object[player]->setPosition(buf[2], buf[3]);
		object[buf[1] - 10]->damage();
		object[player]->addscore(20);
		object[player]->update();
		object[buf[1] - 10]->update();
	}
	else if (buf[0] == 6) {
		gotoxy(object[player]->getPosition().x, object[player]->getPosition().y);
		printf("  ");
		object[player]->setPosition(buf[1], buf[2]);
		object[player]->update();
	}
	else if (buf[0] == 8) {
		gotoxy(WIDTH + 3, 5);
		printf("                                                                                      ");
		printf("p%d : %s", player - 4, &buf[1]);
		gameRecv(player, object);
	}
}

void Communication::chatSend(char* chat)
{
	memset(buf, 0, sizeof(buf));
	socket8(buf, chat);
	retval = send(sock, buf, strlen(buf), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		exit(1);
	}
}