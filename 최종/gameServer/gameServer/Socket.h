#pragma once
#include "Init.h"
#include "Error.h"
#include <time.h>

class Socket
{
	int player;
public:
	Socket();
	~Socket();

	void socket2(char* buf, int pass, bool check);
	void socket3(char* buf);
};