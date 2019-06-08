#pragma once
#include "stdafx.h"

class Communication
{
	char id[20];
	char password[20];
	int retval;
	char buf[BUFSIZE + 1];
	int len;
	SOCKET sock;
public:
	Communication();
	~Communication();
	void err_quit(const char *msg);
	void err_display(const char *msg);
	int recvn(SOCKET s, char *buf, int len, int flags);

	// header, id length, id, pw length, pw
	void loginInput();
	void loginSend();
	// header, t/f
	bool loginRecv();

	void gameSend();
	void gameRecv();

	void chatSend();
	void chatRecv();
};

