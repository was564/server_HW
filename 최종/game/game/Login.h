#pragma once
#include "Communication.h"

class Login
{
	char id[20];
	char password[20];
public:
	Login();
	~Login();

	void input();
	void send();
	bool recv();
};

