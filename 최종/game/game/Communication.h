#pragma once
#include "stdafx.h"

class Communication
{
public:
	Communication();
	~Communication();
	void err_quit(const char *msg);
	void err_display(const char *msg);
	int recvn(SOCKET s, char *buf, int len, int flags);
	virtual void sendn();
protected:
	int retval;
	char buf[BUFSIZE + 1];
	int len;
	SOCKET sock;
};

