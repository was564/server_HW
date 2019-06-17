#pragma once
#include "Init.h"
#include "GameObject.h"

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

	void loginInput();
	// header, id length, id, pw length, pw
	void loginSend();
	// header, player, t/f
	bool loginRecv(int* pass);

	// header 2, seed
	int gameStart();

	// header 3, object, x, y, x, y
	void gameSendE(int pass, int a, int b, int x, int y);
	// header 4, object, x, y
	void gameSendP(int pass, int a, int b);
	// header 5, x, y
	void gameSend(int a, int b);

	//
	void gameRecv(int player, GameObject* object[]);

	void chatSend();
	void chatRecv();
};

