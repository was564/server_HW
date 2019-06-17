#pragma once
#include "Init.h"
#include <time.h>
#include <fstream>
#include <string>
#include "Error.h"
#include "Initialization.h"

static SOCKET play[2];

class Communication : public Initialization
{
	int pass;
	char temp[10];
	SOCKET client_sock;
	int retval;
	SOCKADDR_IN clientaddr;
	int addrlen;
	int len;
	char buf[BUFSIZE + 1];
	char data[BUFSIZE + 1];
	char id[20];
	char pw[20];
	bool login;

public:
	void init(LPVOID arg);
	// header 1, id length, id, pw length, pw
	void loginRecv();
	// header 1, player, t/f
	bool loginSend(int index);

	// header 2, seed
	void gameStart();

	// header 3, object, x, y, x, y
	// header 4, object, x, y
	// header 5, x, y
	void gameRecvNSend();

	void file_init();

	Communication();
	~Communication();
};

