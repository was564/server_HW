#pragma once
#include "Communication.h"

class Login : public Communication
{
	char id[20];
	char password[20];

public:
	Login();
	~Login();

	void input();
	void sendn();
	bool recvn();
};

