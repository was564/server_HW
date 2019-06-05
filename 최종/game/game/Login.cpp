#include "Login.h"



Login::Login()
	:Communication()
{
}


Login::~Login()
{
}

void Login::input()
{
	cout << "id를 입력하세요 : ";
	cin >> id;
	cout << "Password를 입력하세요 : ";
	cin >> password;
}

void Login::sendn()
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

bool Login::recvn()
{
	retval = Communication::recvn(sock, buf, retval, 0);
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
