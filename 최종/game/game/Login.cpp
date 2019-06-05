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
	cout << "id�� �Է��ϼ��� : ";
	cin >> id;
	cout << "Password�� �Է��ϼ��� : ";
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
			cout << "�α��ο� �����Ͽ����ϴ�.";
			return false;
		}
		else if (buf[1] == 1) {
			cout << "�α��ο� �����Ͽ����ϴ�.";
			return true;
		}
	}
	else {
		return false;
	}
	return false;
}
